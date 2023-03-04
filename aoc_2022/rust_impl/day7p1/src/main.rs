use clap::Parser;
use std::collections::HashMap;
use std::fs;
use std::time::Instant;

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    #[arg(short, long)]
    file_name: String,
    exp_size: i64
}

struct File {
    name: String,
    size: i64
}

struct Directory {
    name: String,
    size: i64,
    files: Vec<File>,
    dirs: Vec<String>
}

fn get_directory_size(dir: &str, dir_dtls_map: &HashMap<String, Vec<String>>) -> i64 {
    let mut dir_size: i64 = 0;
    let dir_dtls: Vec<String> = dir_dtls_map.get(dir).unwrap().to_vec();

    for item in dir_dtls {
        if item.starts_with("dir ") {
            // Directory case
            let tmp_dir: String = item.split(' ').nth(1).unwrap().to_owned().to_string();
            dir_size += get_directory_size(&tmp_dir, dir_dtls_map);
        } else {
            // File case
            let file_size: i64 = item.split(' ').nth(0).unwrap().parse::<i64>().unwrap();
            dir_size += file_size;
        }
    }

    dir_size
}

impl Directory {
    fn file_directory_struct(&mut self, dir: &str, dir_dtls_map: HashMap<String, Vec<String>>) -> Directory {
        let dir_dtls: Vec<String> = dir_dtls_map.get(dir).unwrap().to_vec();
        let mut dirs: Vec<String> = Vec::new();
        let mut files: Vec<File> = Vec::new();

        for item in dir_dtls {
            if item.starts_with("dir ") {
                // Directory case
                let tmp_dir: String = item.split(' ').nth(1).unwrap().to_owned().to_string();
                dirs.push(tmp_dir);
            } else {
                // File case
                let file_size: i64 = item.split(' ').nth(0).unwrap().parse::<i64>().unwrap();
                let file_name: String = item.split(' ').nth(1).unwrap().to_owned().to_string();
                let file: File = File {
                    name: file_name,
                    size: file_size
                };
                files.push(file);
            }
        }

        Directory {
            name: dir.to_string(),
            size: get_directory_size(dir, &dir_dtls_map),
            files: files,
            dirs: dirs
        }
    }
}

fn read_contents(content: &str) -> HashMap<String, Vec<String>> {
    let mut parent_dir: String = "".to_string();

    let mut dir_dtls: Vec<String> = Vec::new();
    let mut dir_dtls_map: HashMap<String, Vec<String>> = HashMap::new();
    let mut dir_list: Vec<String> = Vec::new();

    for line in content.split('\n') {
        if line.is_empty() {
            break;
        }

        if line.starts_with('$') {
            // This is a command
            if line.starts_with("$ cd ") {
                // println!("cd_cmd is {line}");
                if !dir_dtls.is_empty() {
                    dir_dtls_map.insert(parent_dir, dir_dtls.to_owned());
                }
                dir_dtls.clear();

                // Change directory
                parent_dir = line.split(' ').nth(2).unwrap().to_string();
                if parent_dir == ".." {
                    parent_dir = dir_list.pop().unwrap();
                } else {
                    dir_list.push(parent_dir.clone());
                }
            }
            continue;
        }

        // println!("list content line is {line}");
        dir_dtls.push(line.to_owned().to_string());
    }

    if !dir_dtls.is_empty() {
        dir_dtls_map.insert(parent_dir, dir_dtls.to_owned());
    }

    dir_dtls_map
}

fn get_dirs_to_match_expected(dir_dtls_map: &HashMap<String, Vec<String>>, exp_size: i64) -> i64 {
    let mut total_size_of_matching_dirs: i64 = 0;
    for (dir_name, _) in dir_dtls_map {
        let dir_size: i64 = get_directory_size(&dir_name, &dir_dtls_map);
        if dir_name != "/" && dir_size <= exp_size {
            println!("{dir_name} : {dir_size}");
            total_size_of_matching_dirs += dir_size;
        }
    }
    
    total_size_of_matching_dirs
}

fn main() {
    let args = Args::parse();
    let start_time = Instant::now();
    let content = fs::read_to_string(&args.file_name).expect("Unable to load the file!");
    let exp_size = args.exp_size;
    let dir_dtls_map: HashMap<String, Vec<String>> = read_contents(&content);

    let result: i64 = get_dirs_to_match_expected(&dir_dtls_map, exp_size);
    println!("Result is {result}");

    let duration = start_time.elapsed();
    println!("Total time taken -> {:?} ", duration);
}
