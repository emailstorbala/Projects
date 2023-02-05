use std::thread;
use std::time;

fn main() {
    let handle: thread::JoinHandle<()> = thread::spawn(|| {
        for num in 1..100 {
            println!("I am inside thread, index: {}", num);
            thread::sleep(time::Duration::from_micros(1));
        }
    });
    for num in 1..100 {
        println!("I am outside thread, index: {}", num);
        thread::sleep(time::Duration::from_micros(1));
    }
    handle.join().unwrap(); 
}
