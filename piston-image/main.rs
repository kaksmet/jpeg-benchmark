extern crate image;

use std::env;
use std::fs::File;
use std::io::Read;
use std::path::Path;
use std::process;

fn read_file<P: AsRef<Path>>(path: P) -> Vec<u8> {
    let mut file = File::open(path).unwrap();
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).unwrap();

    buffer
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let data = read_file(&args[1]);
    let iterations = usize::from_str_radix(&args[2], 10).unwrap();
    let mut failure = false;

    for _ in 0 .. iterations {
        let result = image::load_from_memory_with_format(&data, image::ImageFormat::JPEG);
        failure = failure || result.is_err();
    }

    if failure {
        process::exit(1);
    }
}
