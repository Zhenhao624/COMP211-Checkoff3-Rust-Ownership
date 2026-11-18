fn main() {
    let x = Box::new(42);
    let r = &x;

    drop(x);          // ERROR: tries to move/drop x while r is still needed.
    println!("{}", r); // r would be used after the owner was dropped.
}
