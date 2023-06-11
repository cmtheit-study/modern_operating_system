use q39::Rope;

fn main() {
    let mut rope = Rope::<10>::new();
    for _ in 0..20000 {
        rope.next();
        rope.report()
    }
}