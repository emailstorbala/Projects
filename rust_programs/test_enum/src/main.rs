enum Objects {
    ROCK = 1,
    PAPER,
    SCISSORS
}

fn main() {
    println!("Rock value is {}", Objects::ROCK as i8);
    println!("Paper value is {}", Objects::PAPER as i8);
    println!("Scissors value is {}", Objects::SCISSORS as i8);

    for obj in [Objects::ROCK, Objects::PAPER, Objects::SCISSORS] {
        match obj {
            Objects::ROCK => println!("I am rock!"),
            Objects::PAPER => println!("I am paper!"),
            Objects::SCISSORS => println!("I am scissors!"),
        }
    }
}
