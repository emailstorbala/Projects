use std::collections::HashMap;

fn main() {
    let mut my_map = HashMap::new();

    my_map.insert("Name", "Balamurugan R");
    my_map.insert("Age", "32");
    my_map.insert("Address", "Chennai");

    for (l_key, l_val) in my_map {
        println!("l_key, l_val -> ({}, {})", l_key, l_val);
    }
}
