use anyhow;
use std::io::{Read, Write};
use std::path::Path;
use std::sync::{mpsc, Arc, Mutex};
use std::thread;
use std::{fs::File, path::PathBuf};

use crate::ups::Ups;

#[derive(Debug)]
pub struct NupsCli {
  gba_file_path_: String,
  ups_file_path_: String,
  full_output_path_: String,
  ups_mutex_: Arc<Mutex<Ups>>,
}

impl NupsCli {
  pub fn new(
    gba_file_path: &str,
    ups_file_path: &str,
    full_output_path: &str,
    ups: Arc<Mutex<Ups>>,
  ) -> NupsCli {
    NupsCli {
      gba_file_path_: String::from(gba_file_path),
      ups_file_path_: String::from(ups_file_path),
      full_output_path_: String::from(full_output_path),
      ups_mutex_: ups,
    }
  }

  /// Start to patch our clean ROM!
  /// Ref: https://stackoverflow.com/a/25463033
  pub fn execute(self: Arc<NupsCli>) {
    let mut handles = Vec::<thread::JoinHandle<()>>::new();
    let self2 = Arc::clone(&self);
    let handle = thread::spawn(move || {
      self2
        .read_patch_check_valid_patch()
        .expect(&(format!("\nInvalid UPS File: '{}'\n", self2.ups_file_path_)));
    });
    handles.push(handle);

    let self2 = Arc::clone(&self);
    let (tx, rx) = mpsc::channel();
    let handle = thread::spawn(move || {
      let gba_file = self2
        .read_gba_file()
        .expect(&(format!("\nInvalid GBA File: '{}'\n", self2.gba_file_path_)));
      tx.send(gba_file).unwrap();
    });
    handles.push(handle);

    let (tx_filename, rx_filename) = mpsc::channel::<PathBuf>();
    let self2 = Arc::clone(&self);
    let handle = thread::spawn(move || {
      tx_filename.send(self2.set_output_filename()).unwrap();
    });
    handles.push(handle);

    for handle in handles {
      handle.join().unwrap();
    }

    let gba_file = rx.recv().unwrap();
    let ups = self.ups_mutex_.lock().unwrap();
    match ups.is_file_valid_to_apply(&gba_file) {
      Ok(_) => {}
      Err(err) => panic!("{}", err),
    }

    let patched_gba_file = ups.apply_patch(&gba_file);
    let output_pathbuf = rx_filename.recv().unwrap();
    match self.output(&patched_gba_file, &output_pathbuf) {
      Ok(_) => {}
      Err(err) => panic!("{}", err),
    };
  }

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // | PRIVATE FUNCTIONS
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
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

  fn set_output_filename(&self) -> PathBuf {
    let path = Path::new(&self.gba_file_path_);
    let parent = path.parent().unwrap();
    let mut filename = String::from(path.file_stem().unwrap().to_str().unwrap());
    let extension = path.extension().unwrap().to_str().unwrap();

    if self.full_output_path_ == "" {
      filename.push_str("-patched");
    } else {
      filename = String::from(&self.full_output_path_)
    }
    filename.push_str(".");
    filename.push_str(extension);

    let mut pathbuf = PathBuf::new();
    pathbuf.push(parent);
    pathbuf.push(filename);
    pathbuf
  }
}
