use crate::crc32::Crc32;
use crate::ups::Ups;
use crate::NupsCli;
use std::sync::{Arc, Mutex};

pub struct Factory;

impl Factory {
  pub fn create_crc32() -> Crc32 {
    Crc32::new()
  }

  pub fn create_ups() -> Ups {
    Ups::new(Factory::create_crc32())
  }

  pub fn create_nups_cli(
    gba_file_path: &str,
    ups_file_path: &str,
    full_output_path: &str,
  ) -> NupsCli {
    NupsCli::new(
      gba_file_path,
      ups_file_path,
      full_output_path,
      Arc::new(Mutex::new(Factory::create_ups())),
    )
  }
}
