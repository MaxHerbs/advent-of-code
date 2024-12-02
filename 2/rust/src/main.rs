use std::fs::File;
use std::io::{BufRead, BufReader};

fn main() {
    let val = parse_and_count("data.txt");
    println!("Number of safe reports: {}", val);
}

fn parse_and_count(file_name: &str) -> i32 {
    let mut passed_reports = 0;

    let file = File::open(file_name).expect("File not found");
    let reader = BufReader::new(file);

    for line in reader.lines() {
        let vals: Vec<i32> = line
            .unwrap()
            .split(" ")
            .map(|x| x.parse::<i32>().unwrap())
            .collect();
        println!("{:?}", vals);

        let passed = search(&vals);
        if passed {
            passed_reports += 1;
        } else {
            for exclude in 0..vals.len() {
                let filtered: Vec<_> = vals
                    .iter()
                    .enumerate()
                    .filter(|&(i, _)| i != exclude)
                    .map(|(_, &val)| val)
                    .collect();

                let passed = search(&filtered);
                if passed {
                    passed_reports += 1;
                    break;
                }
            }
        }
    }
    passed_reports
}

fn search(vals: &[i32]) -> bool {
    let direction: i32;
    if *vals.last().unwrap() > vals[0] {
        direction = 1;
    } else if vals[1] < vals[0] {
        direction = -1;
    } else {
        return false;
    }

    let mut prev_val = vals[0];
    for (_, &val) in vals[1..].iter().enumerate() {
        if (val - prev_val) * direction <= 0 {
            return false;
        }
        if (val - prev_val).abs() > 3 {
            return false;
        }
        prev_val = val;
    }
    println!("Passed");
    true
}
