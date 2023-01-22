fn main() {
    let num: i32 = 18;
    let voting_age: i32 = 18;
    match num.cmp(&voting_age) {
        std::cmp::Ordering::Less => println!("Not yet voting age"),
        std::cmp::Ordering::Greater => println!("You are in voting age"),
        std::cmp::Ordering::Equal => println!("You just reached voting age"),
    }
}
