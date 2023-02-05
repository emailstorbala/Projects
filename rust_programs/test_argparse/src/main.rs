use clap::Parser;

/// Simple program to greet a person
#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// Name of the person to greet
    #[arg(short, long)]
    name: String,

    /// Number of times to greet
    #[arg(short, long, default_value_t = 1)]
    age: u8,

    #[arg(short, long)]
    address: String,
}

fn main() {
   let args = Args::parse();

    println!("Hello {}, age {}! How is your place {}?", args.name, args.age, args.address);
}
