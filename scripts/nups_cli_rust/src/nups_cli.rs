use anyhow;
use std::io::{Read, Write};
use std::path::Path;
use std::sync::mpsc::{Receiver, Sender};
use std::sync::{mpsc, Arc, Mutex};
use std::thread;
use std::thread::JoinHandle;
use std::{fs::File, path::PathBuf};

use crate::ups::Ups;

#[derive(Debug)]
pub struct NupsCli {
  gba_file_path_: String,
  ups_file_path_: String,
  full_output_path_: Option<String>,
  ups_mutex_: Arc<Mutex<Ups>>,
}

enum RxType {
  Gba(Vec<u8>),
  OutputFileName(PathBuf),
}

impl NupsCli {
  pub fn new(
    gba_file_path: &str,
    ups_file_path: &str,
    full_output_path: Option<String>,
    ups: Arc<Mutex<Ups>>,
  ) -> NupsCli {
    NupsCli {
      gba_file_path_: String::from(gba_file_path),
      ups_file_path_: String::from(ups_file_path),
      full_output_path_: full_output_path,
      ups_mutex_: ups,
    }
  }

  /// Start to patch our clean ROM!
  /// Ref: https://stackoverflow.com/a/25463033
  pub fn execute(self: &Arc<NupsCli>) {
    let (tx, rx) = mpsc::channel::<RxType>();
    self.check_validity(&tx);

    let (gba_file, output_pathbuf) = self.parse_mpsc_msg(&rx);
    let ups = self.ups_mutex_.lock().unwrap();
    self.check_gba_file_valid_to_apply_patch(&ups, &gba_file);
    self.patch_gba_file(&ups, &gba_file, &output_pathbuf);
  }

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // | PRIVATE FUNCTIONS
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  fn check_validity(self: &Arc<NupsCli>, tx: &Sender<RxType>) {
    let mut handles = Vec::<thread::JoinHandle<()>>::new();
    handles.push(self.get_handle_check_valid_patch());
    handles.push(self.get_handle_check_valid_gba_file(&tx));
    handles.push(self.get_handle_check_output_filename(&tx));
    for handle in handles {
      handle.join().unwrap();
    }
  }

  fn get_handle_check_valid_patch(self: &Arc<NupsCli>) -> JoinHandle<()> {
    let self2 = Arc::clone(&self);
    thread::spawn(move || {
      self2
        .read_patch_check_valid_patch()
        .expect(&(format!("\nInvalid UPS File: '{}'\n", self2.ups_file_path_)));
    })
  }

  fn get_handle_check_valid_gba_file(self: &Arc<NupsCli>, tx: &Sender<RxType>) -> JoinHandle<()> {
    let self2 = Arc::clone(&self);
    let tx1 = mpsc::Sender::clone(tx);
    thread::spawn(move || {
      let gba_file = self2
        .read_gba_file()
        .expect(&(format!("\nInvalid GBA File: '{}'\n", self2.gba_file_path_)));
      tx1.send(RxType::Gba(gba_file)).unwrap();
    })
  }

  fn get_handle_check_output_filename(self: &Arc<NupsCli>, tx: &Sender<RxType>) -> JoinHandle<()> {
    let self2 = Arc::clone(&self);
    let tx1 = mpsc::Sender::clone(&tx);
    thread::spawn(move || {
      tx1
        .send(RxType::OutputFileName(self2.get_output_filename()))
        .unwrap();
    })
  }

  fn check_gba_file_valid_to_apply_patch(self: &Arc<NupsCli>, ups: &Ups, gba_file: &[u8]) {
    match ups.is_file_valid_to_apply(gba_file) {
      Ok(_) => {}
      Err(err) => panic!("{}", err),
    };
  }

  fn patch_gba_file(self: &Arc<NupsCli>, ups: &Ups, gba_file: &[u8], output_pathbuf: &PathBuf) {
    let patched_gba_file = ups.apply_patch(gba_file);
    match self.output(&patched_gba_file, output_pathbuf) {
      Ok(_) => {}
      Err(err) => panic!("{}", err),
    };
  }

  fn read_patch_check_valid_patch(&self) -> Result<(), anyhow::Error> {
    let mut ups_file = File::open(&self.ups_file_path_)?;
    let mut buffer = Vec::<u8>::new();
    ups_file.read_to_end(&mut buffer)?;

    match self.ups_mutex_.lock().unwrap().is_valid_patch(&buffer) {
      Ok(_) => (),
      Err(err) => {
        println!("{}", err);
        std::process::exit(1);
      }
    }

    Ok(())
  }

  fn parse_mpsc_msg(&self, rx: &Receiver<RxType>) -> (Vec<u8>, PathBuf) {
    let mut output_pathbuf = PathBuf::new();
    let mut gba_file = Vec::<u8>::new();
    // We use `try_iter()` instead of `iter()` as all the messages should have been sent already.
    for msg in rx.try_iter() {
      match msg {
        RxType::Gba(file) => gba_file = file.to_vec(),
        RxType::OutputFileName(output_path) => output_pathbuf = output_path.to_path_buf(),
      }
    }
    (gba_file, output_pathbuf)
  }

  fn read_gba_file(&self) -> Result<Vec<u8>, anyhow::Error> {
    println!("Loading GBA file.");
    let mut gba_file = File::open(&self.gba_file_path_)?;
    let mut buffer = Vec::<u8>::new();
    gba_file.read_to_end(&mut buffer)?;
    println!("FINISHED: Loading GBA file");
    Ok(buffer)
  }

  fn output(&self, patched_gba_file: &[u8], output_path: &Path) -> Result<(), anyhow::Error> {
    println!("Writing patched file.");
    let mut file = File::create(output_path)?;
    file.write_all(patched_gba_file)?;
    println!(
      "FINISHED: Writing patched file to: \n'{}'\n",
      output_path.to_str().unwrap()
    );
    Ok(())
  }

  fn get_output_filename(&self) -> PathBuf {
    let path = Path::new(&self.gba_file_path_);
    let parent = path.parent().unwrap();
    let mut filename = String::from(path.file_stem().unwrap().to_str().unwrap());
    let extension = path.extension().unwrap().to_str().unwrap();

    match &self.full_output_path_ {
      Some(output) => filename = output.to_string(),
      None => filename.push_str("-patched"),
    }

    filename.push_str(".");
    filename.push_str(extension);

    let mut pathbuf = PathBuf::new();
    pathbuf.push(parent);
    pathbuf.push(filename);
    pathbuf
  }
}
