use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn read_input_file(inp: String) -> Vec<i64> {
    let mut res = Vec::new();
    let mut tmp = 0;

    if let Ok(lines) = read_lines(inp) {
        for line in lines {
            if let Ok(ip) = line {
                if ip.is_empty() {
                    res.push(tmp);
                    tmp = 0;
                } else {
                    tmp += ip.parse::<i64>().unwrap();
                }
            }
        }
        res.push(tmp);
    }

    return res;
}

fn get_max_of(vec: Vec<i64>) -> i64 {
    let mut max: i64 = 0;
    for num in vec {
        if max >= num {
            continue
        } else {
            max = num;
        }
    }

    return max;
}

fn main() {
    let inp = String::from("inp_file.txt");
    let ctx = read_input_file(inp);
    let max = get_max_of(ctx);
    println!("num is {}", max);
}
