struct MyStruct<'a> {
    value: &'a mut i32
}

trait HasId {
    type Id;
}

impl<'a> MyStruct<'a> {
    fn add_one(&mut self) -> <Self as HasId>::Id {
        *self.value += 1;
        10
    }
}

impl HasId for MyStruct<'_>{
    type Id = i32;
}

fn add_one(a: &mut i32) -> i32 {
    *a += 1;
    10
}

fn main() {
    let mut v = 10;
    let mut m = MyStruct {
        value: &mut v
    };
    let a = MyStruct::add_one(&mut m);
    let b = MyStruct::add_one(&mut m);
    MyStruct::add_one(&mut m);
    MyStruct::add_one(&mut m);
    println!("{}", m.value);
}
