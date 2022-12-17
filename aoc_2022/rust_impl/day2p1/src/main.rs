extern crate lazy_static;

use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;
use lazy_static::lazy_static;
use std::collections::HashMap;

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn read_input_file(inp: String) -> Vec<String> {
    let mut res = Vec::new();

    if let Ok(lines) = read_lines(inp) {
        for line in lines {
            if let Ok(ip) = line {
                let pairs = ip.split(" ").collect();
                res.push(pairs);
            }
        }
    }

    return res;
}

const ROCK: i32     = 1;
const PAPER: i32    = 2;
const SCISSORS: i32 = 3;

const WIN_BONUS: i32 = 6;
const DRAW_BONUS: i32 = 3;
const LOSE_BONUS: i32 = 0;

lazy_static! {
    static ref OPPONENT: HashMap<char, i32> = {
        let mut map = HashMap::new();
        map.insert('A', ROCK);
        map.insert('B', PAPER);
        map.insert('C', SCISSORS);
        map
    };
    static ref MINE: HashMap<char, i32> = {
        let mut map = HashMap::new();
        map.insert('X', ROCK);
        map.insert('Y', PAPER);
        map.insert('Z', SCISSORS);
        map
    };
}


fn get_score(opp: char, mine: char) -> i32 {
    let mut res: i32 = 0;
    let &opp_val = OPPONENT.get(&opp).unwrap();
    let &my_val = MINE.get(&mine).unwrap();

    if opp_val == my_val {
        // Draw case
        res += opp_val + DRAW_BONUS;
    } else if (opp_val == ROCK && my_val == SCISSORS) ||
              (opp_val == SCISSORS && my_val == PAPER) ||
              (opp_val == PAPER && my_val == ROCK) {
        // Losing case
        res += my_val + LOSE_BONUS;
    } else {
        // Winning case
        res += my_val + WIN_BONUS;
    }

    return res;
}

fn main() {
    let inp = String::from("inp_file.txt");
    let ctx = read_input_file(inp);

    let mut tot_score: i32 = 0;
    for pair in ctx {
        let chrs: Vec<char> = pair.chars().collect();
        let opp_item: char = chrs[0];
        let my_item: char = chrs[1];

        tot_score += get_score(opp_item, my_item);
    }
    println!("Total score is {}", tot_score);
}
