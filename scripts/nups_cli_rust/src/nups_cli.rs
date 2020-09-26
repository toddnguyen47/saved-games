use anyhow;
use std::fs::File;
use std::io::Read;

use crate::ups::Ups;

#[derive(Debug)]
pub struct NupsCli {
  gba_file_path_: String,
  ups_file_path_: String,
  full_output_path_: String,
}

impl NupsCli {
  pub fn new(gba_file_path: &str, ups_file_path: &str, full_output_path: &str) -> NupsCli {
    NupsCli {
      gba_file_path_: String::from(gba_file_path),
      ups_file_path_: String::from(ups_file_path),
      full_output_path_: String::from(full_output_path),
    }
  }

  pub fn execute(&self) {
    self
      .read_patch_check_valid_patch()
      .expect(&(format!("\nInvalid UPS File: '{}'\n", self.ups_file_path_)));
  }

  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // | PRIVATE FUNCTIONS
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  fn read_patch_check_valid_patch(&self) -> Result<(), anyhow::Error> {
    let mut ups_file = File::open(&(self.ups_file_path_))?;
    let mut buffer = Vec::<u8>::new();
    ups_file.read_to_end(&mut buffer)?;

    let mut ups = Ups::new();
    match ups.is_valid_patch(&buffer) {
      Ok(_) => (),
      Err(err) => {
        println!("{}", err);
        std::process::exit(1);
      }
    }

    Ok(())
  }
}
