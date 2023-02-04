use std::time::Instant;
use std::{fs, u32};

fn get_compartment_details(file_contents: &str) -> Vec<Vec<String>> {
    let mut compartment_details: Vec<Vec<String>> = Vec::new();

    let mut tmp_grp: Vec<String> = Vec::new();

    for chunk_rec in file_contents.split('\n') {
        if !chunk_rec.is_empty() {
            tmp_grp.push(chunk_rec.clone().to_string());
            if tmp_grp.len() == 3 {
                compartment_details.push(tmp_grp.clone());
                tmp_grp.clear();
            }
        }
    }

    compartment_details
}

fn get_item_priority(item: char) -> u32 {
    let priority: u32;
    if item as u32 >= 65 && item as u32 <= 90 {
        // Capital letter case
        priority = item as u32 - 65 + 27;
    } else if item as u32 >= 97 && item as u32 <= 122 {
        // lower letter case should come here
        priority = item as u32 - 96;
    } else {
        panic!("Invalid item '{}' in input file!", item);
    }

    priority
}

fn main() {
    let start_time = Instant::now();
    let contents = fs::read_to_string("inp_file.txt").expect("Unable to load the file!");

    let compartment_details = get_compartment_details(&contents);
    let mut total_common_chars: String = String::from("");
    let mut total_priority: u32 = 0;

    for comps in compartment_details {
        let comp1: String = comps.iter().nth(0).unwrap().to_string();
        let comp2: String = comps.iter().nth(1).unwrap().to_string();
        let comp3: String = comps.iter().nth(2).unwrap().to_string();

        // println!("comp_grp is -> {:?}", comp_grp);
        let mut common_chars: String = String::from("");
        for item in comp1.chars() {
            if !common_chars.contains(item) && comp2.contains(item) {
                if comp3.contains(item) {
                    common_chars.push(item);
                }
            }
        }
        total_common_chars += &common_chars;
    }

    for item in total_common_chars.chars() {
        total_priority += get_item_priority(item);
    }

    println!("Total priority is {}", total_priority);

    let duration = start_time.elapsed();
    println!("Total time taken -> {:?} ", duration);
}
