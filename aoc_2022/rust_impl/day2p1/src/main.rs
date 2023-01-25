use std::{fs, char};
use std::time::Instant;

const ROCK: i32 = 1;
const PAPER: i32 = 2;
const SCISSORS: i32 = 3;

const WIN_BONUS: i32 = 6;
const DRAW_BONUS: i32 = 3;
const LOSE_BONUS: i32 = 0;

fn item_value(item: char) -> i32 {
    match item {
        'A' | 'X' => ROCK,
        'B' | 'Y' => PAPER,
        'C' | 'Z' => SCISSORS,
        _ => panic!("Invalid item sent"),
    }
}

fn get_score(opp: char, mine: char) -> i32 {
    let mut res: i32 = 0;
    let opp_val = item_value(opp);
    let my_val = item_value(mine);

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
