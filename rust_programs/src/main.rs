fn main() {
    let loc = "H W C";
    let my_vec: Vec<char> = loc
        .split(' ')
        .map(|chunk| -> char { chunk.chars().nth(0).unwrap() })
        .collect();
    println!("my_vec elements are {}:{}", my_vec[0], my_vec[1]);
}
