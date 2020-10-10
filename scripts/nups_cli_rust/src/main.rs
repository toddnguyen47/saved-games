// Ref: Similarities Between RefCell<T>/Rc<T> and Mutex<T>/Arc<T>
// Ref: https://doc.rust-lang.org/1.30.0/book/2018-edition/ch16-03-shared-state.html
use std::sync::Arc;
use structopt::StructOpt;

// Ref: https://stackoverflow.com/a/48071730/6323360
mod nups_cli;
use nups_cli::NupsCli;

mod byte_conversion;
mod crc32;
mod factory;
use factory::Factory;
mod ups;

#[derive(StructOpt, Debug)]
#[structopt(name = "NupsCliRust", about = "NUPS CLI written in Rust!")]
struct Cli {
  /// UPS file path
  #[structopt(long = "--ups")]
  ups_file: String,
  /// GBA file path
  #[structopt(long = "--gba")]
  gba_file: String,
  /// Optional output file name
  #[structopt(long = "--output")]
  output_filename: Option<String>,
}

fn main() {
  let args = Cli::from_args();

  let output_filename = args.output_filename;
  use std::time::Instant;
  let start = Instant::now();
  let nups_cli_obj = Arc::new(Factory::create_nups_cli(
    &args.gba_file,
    &args.ups_file,
    output_filename,
  ));
  nups_cli_obj.execute();
  let elapsed = start.elapsed().as_millis();

  println!("Elapsed Time: {:.4} seconds", elapsed as f64 / 1000f64);
}
