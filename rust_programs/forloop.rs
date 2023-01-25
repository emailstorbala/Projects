
fn main() {
    println!("Numbers divisible by 3 between 1 and 100:");
    print!("\t");
    for num in 1..=102 {
        if num % 3 == 0 {
            print!("{} ", num);
        }
    }
    println!();
}
