use crate::if_dead_lock;
use crate::proc::Proc;

#[test]
fn test() {
    let mut available = [2, 1, 0, 0];
    let mut procs = [
        Proc::new(Some([0, 0, 1, 0]), Some([2, 0, 0, 1])),
        Proc::new(Some([2, 0, 0, 1]), Some([1, 0, 1, 0])),
        Proc::new(Some([0, 1, 2, 0]), Some([2, 1, 0, 0]))
    ];
    loop {
        let mut has_tagged = false;
        procs.iter_mut()
            .for_each(|p| {
                if p.fulfill_ret(&mut available) {
                    has_tagged = true;
                }
            });
        if !has_tagged {
            break
        }
    }
    assert!(!if_dead_lock(&procs));
}