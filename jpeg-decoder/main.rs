extern crate jpeg_decoder as jpeg;

use std::env;
use std::fs::File;
use std::io::Read;
use std::path::Path;
use std::process;

fn read_file<P: AsRef<Path>>(path: P) -> Vec<u8> {
    let mut file = File::open(path).unwrap();
    let mut buffer = vec![];
    file.read_to_end(&mut buffer).unwrap();
    buffer
}

fn main() {
    let data = read_file(env::args().nth(1).unwrap());
    let iterations = usize::from_str_radix(&env::args().nth(2).unwrap(), 10).unwrap();
    let mut failed = false;

    for _ in 0 .. iterations {
        let result = jpeg::Decoder::new(&data[..]).decode();
        failed = failed || result.is_err();
    }

    if failed {
        process::exit(1);
    }
}
