fn main() {
    let item: char = 'X';

    match item {
        'A' | 'X' => println!("Item matched!"),
        _ => println!("Item not matched!")
    }
}
