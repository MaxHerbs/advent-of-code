use std::fs::File;
use std::io::{self, BufRead, BufReader};

fn main() {
    let file_path = "data.txt";
    let diff = calc_diff(file_path).unwrap();
    print!("{:?}\n", diff);
}


fn calc_diff(file_path: &str) -> Result<i32, io::Error> {
    let file = File::open(file_path)?;
    print!("File open\n");
    let reader = BufReader::new(file);


    let mut col1: Vec<i32> = Vec::new();
    let mut col2: Vec<i32> = Vec::new();

    for line in reader.lines() {
        let line = line?;
        let columns: Vec<&str> = line.split_whitespace().collect();

        if columns.len() >= 2 {
            if let (Ok(val1), Ok(val2)) = (columns[0].parse::<i32>(), columns[1].parse::<i32>()) {
                col1.push(val1);
                col2.push(val2);
            } else {
                eprintln!("Warning: Failed to parse columns in line: {}\n", line);
            }
        }
    }

    col1.sort();
    col2.sort();

    let mut diff = 0;
    let num_lines = col1.len();
    for i in 0..num_lines {
        diff += (col1[i] - col2[i]).abs()
    }

    Ok(diff)
}
