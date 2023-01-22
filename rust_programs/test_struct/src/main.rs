
struct Student {
    name: String,
    age: i32,
    class: i32,
}

fn main() {
    let stud1 = Student {
        name: "Hariganesh B".to_string(),
        age: 9,
        class: 4,
    };

    println!("Hi {}!, How are you doing?", stud1.name);

    let stud2 = Student {
        name: "Sheshadri".to_string(),
        age: stud1.age,
        class: stud1.class,
    };
    println!("Hi {}!, How are you doing?", stud2.name);
}
