fn main() {
    let tmp : Vec<i64> = (0..=100).collect();

    let first = &tmp[1..=10];
    let second = &tmp[11..=20];
    let third = &tmp[21..=100];

    print!("first -> ");
    for m in first.iter() {
        print!("{:?} ", m);
    }
    println!();

    print!("second-> ");
    for m in second.iter() {
        print!("{:?} ", m);
    }
    println!();

    print!("third-> ");
    for m in third.iter() {
        print!("{:?} ", m);
    }
    println!();
}
