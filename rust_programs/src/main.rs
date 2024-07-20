//use std::fmt;

// #[derive(Debug)]
// struct MyError {
//     details: String
// }
//
// impl MyError {
//     fn new(msg: &str) -> MyError {
//         MyError{details: msg.to_string()}
//     }
// }
//
// impl fmt::Display for MyError {
//     fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
//         write!(f,"{}",self.details)
//     }
// }

fn get_element_index(mylist: Vec<&str>, elem: &str) -> Result<usize, String> {
    if mylist.contains(&elem) {
        Ok(mylist.iter().position(|&r| r == elem).unwrap())
    } else {
        let err_msg = format!("Input list doesn't contain the given element '{elem}'");
        Err(err_msg)
    }
}

fn main() {
    let mylist: Vec<&str> = vec!["Apple", "Orange", "Grapes"];
    //let res: Result<usize, String> = get_element_index(mylist, "Apple");
    let res: Result<usize, String> = get_element_index(mylist, "Banana");

    match res {
        Ok(idx) => println!("Index: {idx}"),
        Err(my_error) => println!("Error: {my_error}"),
    }
}
