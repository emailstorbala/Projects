extern crate lazy_static;

use lazy_static::lazy_static;
use std::collections::HashMap;
use std::{fs, char};
use std::time::Instant;

const ROCK: i32 = 1;
const PAPER: i32 = 2;
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
    } else if (opp_val == ROCK && my_val == SCISSORS)
        || (opp_val == SCISSORS && my_val == PAPER)
        || (opp_val == PAPER && my_val == ROCK) {
        // Losing case
        res += my_val + LOSE_BONUS;
    } else {
        // Winning case
        res += my_val + WIN_BONUS;
    }

    return res;
}

fn main() {
    let start_time = Instant::now();
    let contents = fs::read_to_string("inp_file.txt").expect("Unable to load the file!");
    let mut ctx = Vec::new();

    for rec in contents.split('\n') {
        if !rec.is_empty() {
            let pair: (char, char) = (rec.chars().nth(0).unwrap(), rec.chars().nth(2).unwrap());
            ctx.push(pair);
        }
    }

    let mut tot_score: i32 = 0;
    for pair in ctx {
        tot_score += get_score(pair.0, pair.1);
    }
    println!("Total score is {}", tot_score);
    let duration = start_time.elapsed();
    println!("Total time taken -> {:?} ", duration);
}
