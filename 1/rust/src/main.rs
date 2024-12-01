use std::fs::File;
use std::io::{self, BufRead, BufReader};

fn main() {
    let file_path = "data.txt";
    let (a,b) = parse(file_path).unwrap();
    let diff = calc_diff(a,b);
    print!("Diff: {:?}\n", diff);
}


fn calc_diff(mut col1: Vec<i32>, mut col2: Vec<i32>) -> i32{
    let mut diff = 0;
    col1.sort();
    col2.sort();

    for i in 0..col1.len(){
        diff += (col1[i] - col2[i]).abs();
    }
    diff
}

fn parse(file_path: &str) -> Result<(Vec<i32>,Vec<i32>), io::Error> {
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
                panic!("Invalid input. NaN")
            }
        }
    }
    Ok((col1,col2))
}
