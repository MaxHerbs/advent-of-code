use regex::Regex;
use std::fs::{self};

const REGEX_PATTERN: &str = r"mul\(\d+,\d+\)";
const FILE_NAME: &str = "data.txt";
fn main() {
    let file_content = file_to_string(FILE_NAME);
    let sum = sum_active(&file_content);
    println!("Sum: {}", sum);
}

fn file_to_string(file_name: &str) -> String {
    let mut file_content = fs::read_to_string(file_name).expect("Error reading file");
    file_content = str::replace(&file_content, "\n", "");
    file_content
}

fn sum_vaid(content: &str) -> i32 {
    let mut sum = 0;
    let re = Regex::new(REGEX_PATTERN).unwrap();
    for express in re.find_iter(content) {
        let mul = express.as_str();
        let inner = mul[4..mul.len() - 1].to_string();
        let nums: Vec<&str> = inner.split(",").collect();
        sum += nums[0].parse::<i32>().unwrap() * nums[1].parse::<i32>().unwrap();
    }
    sum
}

fn sum_active(content: &str) -> i32 {
    let mut sum = 0;
    let parts = content.split("do()");
    for section in parts {
        let indx = section.find("don't()");
        if indx.is_none() {
            sum += sum_vaid(section);
        } else {
            let active_section = &section[..indx.unwrap()];
            sum += sum_vaid(active_section);
        }
    }
    sum
}
