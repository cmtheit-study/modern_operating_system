use std::cell::RefCell;
use lazy_static::lazy_static;
use crate::{Data, HasId, ReqErrCode, ReqResResult, Runtime};
use crate::proc::Proc;
use crate::res::Res;


#[test]
pub fn cond_d<'a>() {
    let mut rt: Runtime = Runtime::new();
    unsafe {
        let a = rt.add_proc();
        let b = rt.add_proc();
        let c = rt.add_proc();
        let r = rt.add_res(0);
        let s = rt.add_res(1);
        let t = rt.add_res(2);
        println!("进程：");
        println!("a: {}", a);
        println!("b: {}", b);
        println!("c: {}", c);
        println!("资源：");
        println!("r: {}", r);
        println!("s: {}", s);
        println!("t: {}", t);
        Runtime::request_report(&mut rt as *mut Runtime, a, r).unwrap();
        Runtime::request_report(&mut rt as *mut Runtime, b, s).unwrap();
        Runtime::request_report(&mut rt as *mut Runtime, c, t).unwrap();
        assert_eq!(Runtime::request_report(&mut rt as *mut Runtime, a, s).unwrap_err(), ReqErrCode::ResOccupied);
        assert_eq!(Runtime::request_report(&mut rt as *mut Runtime, b, t).unwrap_err(), ReqErrCode::ResOccupied);
        assert_eq!(Runtime::request_report(&mut rt as *mut Runtime, c, r).unwrap_err(), ReqErrCode::DeadLockDetected);
    }
}