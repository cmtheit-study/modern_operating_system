use std::sync::{Mutex, Condvar, Arc};
use std::thread;
use std::thread::sleep;
use std::time::Duration;
use rand;
use rand::random;

type PeopleNum = usize;   // 人数

// 人的集合
enum PeopleType {
    Boy(PeopleNum),
    Girl(PeopleNum),
    Non
}

struct ShowerRoom {
    peoples: PeopleType,    // 浴室里的人
    cvar_boy: Condvar,      // 等待有男生
    cvar_girl: Condvar,     // 等待有女生
    has_boy: Mutex<bool>,   // 是否有男生
    has_girl: Mutex<bool>,  // 是否有女生
}

impl ShowerRoom {
    fn new() -> Self {
        Self {
            peoples: PeopleType::Non,
            cvar_boy: Condvar::new(),
            cvar_girl: Condvar::new(),
            has_boy: Mutex::new(false),
            has_girl: Mutex::new(false),
        }
    }

    fn man_wants_to_enter(mutex: &Mutex<Self>) {
        let mut me = mutex.lock().unwrap();
        let mut has_girl = me.has_girl.lock().unwrap();
        while *has_girl {   // 一直等到没有女生
            has_girl = me.cvar_boy.wait(has_girl).unwrap();
        }
        drop(has_girl);
        match me.peoples {
            PeopleType::Boy(ref mut num) => {
                *num += 1;
                me.cvar_boy.notify_one();
            }
            PeopleType::Non => {
                me.peoples = PeopleType::Boy(1);
                *me.has_boy.lock().unwrap() = true;
                me.cvar_boy.notify_one();
            }
            PeopleType::Girl(_) => {
                panic!("Should not be girl.");
            }
        }
    }

    fn women_wants_to_enter(mutex: &Mutex<Self>) {
        let mut me = mutex.lock().unwrap();
        let mut has_boy = me.has_boy.lock().unwrap();
        while *has_boy {   // 一直等到没有女生
            has_boy = me.cvar_girl.wait(has_boy).unwrap();
        }
        drop(has_boy);
        match me.peoples {
            PeopleType::Boy(_) => {
                panic!("Should not be boy.");
            }
            PeopleType::Non => {
                me.peoples = PeopleType::Girl(1);
                *me.has_girl.lock().unwrap() = true;
                me.cvar_girl.notify_one();
            }
            PeopleType::Girl(ref mut num) => {
                *num += 1;
                me.cvar_girl.notify_one();
            }
        }
    }

    fn man_leaves(mutex: &Mutex<Self>) {
        let mut me = mutex.lock().unwrap();
        if let PeopleType::Boy(ref mut num) = me.peoples {
            *num -= 1;
            if *num == 0 {
                *me.has_boy.lock().unwrap() = false;
                me.peoples = PeopleType::Non;
                me.cvar_girl.notify_one();
            }
        }
    }

    fn woman_leaves(mutex: &Mutex<Self>) {
        let mut me = mutex.lock().unwrap();
        if let PeopleType::Girl(ref mut num) = me.peoples {
            *num -= 1;
            if *num == 0 {
                *me.has_girl.lock().unwrap() = false;
                me.peoples = PeopleType::Non;
                me.cvar_boy.notify_one();
            }
        }
    }

    fn report(mutex: &Mutex<Self>) {
        let me = mutex.lock().unwrap();
        match me.peoples {
            PeopleType::Boy(num) => {
                println!("man：\x1b[35m{}\x1b[0m", num);
            }
            PeopleType::Non => {
                println!("\x1b[33mnone\x1b[0m");
            }
            PeopleType::Girl(num) => {
                println!("woman: \x1b[32m{}\x1b[0m", num);
            }
        }
    }
}

fn gen_sleep_time() -> Duration {
    Duration::new(0, random::<u32>() % 500000000 + 500000000)
}

fn sleep_random() {
    sleep(gen_sleep_time());
}

fn main() {
    let shower_room = Arc::new(Mutex::new(ShowerRoom::new()));
    let mut handles = vec![];
    for _ in 1..10 {
        let clone = Arc::clone(&shower_room);
        handles.push(thread::spawn(move || {
            sleep(gen_sleep_time());
            ShowerRoom::man_wants_to_enter(&clone);
            ShowerRoom::report(&clone);
            sleep_random();
            ShowerRoom::man_leaves(&clone);
            ShowerRoom::report(&clone);
            sleep_random();
            ShowerRoom::woman_leaves(&clone);
            ShowerRoom::report(&clone);
            sleep_random();
            ShowerRoom::women_wants_to_enter(&clone);
            ShowerRoom::report(&clone);
        }));
    }
    handles.into_iter()
        .for_each(|handle| {
        handle.join().unwrap();
    })
}
