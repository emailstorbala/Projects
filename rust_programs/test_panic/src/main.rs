fn main() {
    let temp = "Chennai";
    let tmp_chr: char = temp.chars().nth(100).unwrap();

    println!("tmp_chr is {}", tmp_chr);
}
