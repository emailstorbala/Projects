fn main() {
    // Print text to the console
    let greet = "How are you?";
    let valid_voting_age = 18;
    let mut ys: [i64; 500] = [0; 500];
    println!("Hello World! {}", greet);
    println!("Is your age >= {}?", valid_voting_age);
    ys[0] = 10;
    println!("ys[0] >= {}", ys[0]);
    println!("ys[1] >= {}", ys[1]);
}
