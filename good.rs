fn main() {
    let x = Box::new(42);
    let r = &x;

    println!("{}", r); // The last use of r happens first.
    drop(x);          // Safe: r is not used after this point.
}
