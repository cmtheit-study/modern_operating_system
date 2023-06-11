use crate::proc::{Proc};
use crate::res::Res;
use std::collections::HashMap;
use std::hash::{Hash};

mod res;
mod proc;
#[cfg(test)]
mod test;

type Side<'a, T> = &'a T;

pub trait HasId: Hash {
    type IdType: Hash + Copy + Eq;
    fn get_id(&self) -> Self::IdType;
}

type Data = i32;

pub struct Runtime<'a> {
    proc: HashMap<<Proc<'a, Data> as HasId>::IdType, Proc<'a, Data>>,
    res:  HashMap<<Res<'a, Data> as HasId>::IdType, Res<'a, Data>>
}

pub type ReqResResult = Result<i32, ReqErrCode>;
#[derive(Debug, PartialOrd, PartialEq, Eq)]
pub enum ReqErrCode {
    ProcNotFound,
    ResNotFound,
    DeadLockDetected,
    ResOccupied,
    ProcHasRes
}

pub type ReleaseResResult = Result<i32, ReleaseResErrCode>;
#[derive(Debug, PartialOrd, PartialEq, Eq)]
pub enum ReleaseResErrCode {
    ProcNotFound,
    ResNotFound,
    ProcNotOwnRes,
    ResNotOwned
}

impl<'a> Runtime<'a> {
    pub fn new() -> Self {
        Self {
            proc: HashMap::new(),
            res: HashMap::new()
        }
    }

    pub fn add_proc(&mut self) -> <Proc<'a, Data> as HasId>::IdType {
        let new_proc = Proc::new();
        let new_proc_id = new_proc.get_id();
        self.proc.insert(new_proc_id, new_proc);
        new_proc_id
    }

    pub fn add_res(&mut self, data: i32) -> <Res<'a, Data> as HasId>::IdType {
        let new_res = Res::new(data);
        let new_res_id = new_res.get_id();
        self.res.insert(new_res_id, new_res);
        new_res_id
    }

    pub unsafe fn request_res(
        me: * mut Self,
        pid: <Proc<'_, Data> as HasId>::IdType,
        rid: <Res<'_, Data> as HasId>::IdType
    ) -> ReqResResult {
        return if let Some(p) = (*me).proc.get_mut(&pid) {
            if let Some(r) = (*me).res.get_mut(&rid) {
                if let Some((_, owner)) = (*me).proc.iter().find(|(_, p)| {
                    p.if_own_res(rid)
                }) {
                    if owner.get_id() == p.get_id() {
                        Err(ReqErrCode::ProcHasRes)
                    } else {
                        r.request(p);
                        let mut p_d = vec![];
                        let mut r_d = vec![];
                        if p.detect_circle(&mut p_d, &mut r_d) {
                            Err(ReqErrCode::DeadLockDetected)
                        } else {
                            Err(ReqErrCode::ResOccupied)
                        }
                    }
                } else {
                    p.own(r);
                    let mut p_d = vec![];
                    let mut r_d = vec![];
                    if r.detect_circle(&mut p_d, &mut r_d) {
                        Err(ReqErrCode::DeadLockDetected)
                    } else {
                        Ok(0)
                    }
                }
            } else {
                Err(ReqErrCode::ResNotFound)
            }
        } else {
            Err(ReqErrCode::ProcNotFound)
        }
    }

    pub unsafe fn release_res(
        me: * mut Self,
        pid: <Proc<'_, Data> as HasId>::IdType,
        rid: <Res<'_, Data> as HasId>::IdType
    ) -> ReleaseResResult {
        return if let Some(p) = (*me).proc.get_mut(&pid) {
            if let Some(r) = (*me).res.get_mut(&rid) {
                if let Some((_, owner)) = (*me).proc.iter_mut().find(|(_, p)| {
                    p.if_own_res(rid)
                }) {
                    if owner.get_id() == p.get_id() {
                        owner.release(r);
                        if let Some((_, rp)) = (*me).proc.iter_mut().find(|(pid, _)| {
                            r.if_requested(**pid)
                        }) {
                            rp.own(r);
                        }
                        Ok(0)
                    } else {
                        Err(ReleaseResErrCode::ProcNotOwnRes)
                    }
                } else {
                    Err(ReleaseResErrCode::ResNotOwned)
                }
            } else {
                Err(ReleaseResErrCode::ResNotFound)
            }
        } else {
            Err(ReleaseResErrCode::ProcNotFound)
        }
    }

    pub unsafe fn request_report(
        me: * mut Self,
        pid: <Proc<'_, Data> as HasId>::IdType,
        rid: <Res<'_, Data> as HasId>::IdType,
    ) -> ReqResResult {
        let res = Self::request_res(me, pid, rid);
        match &res {
            Ok(_) => {
                println!("进程 {} 对资源 {} 的请求成功", pid, rid);
            }
            Err(code) => {
                match *code {
                    ReqErrCode::ProcNotFound => {
                        print!("进程不存在");
                    }
                    ReqErrCode::ResNotFound => {
                        print!("资源不存在");
                    }
                    ReqErrCode::DeadLockDetected => {
                        print!("检测到死锁");
                    }
                    ReqErrCode::ProcHasRes => {
                        print!("进程已经持有资源");
                    }
                    ReqErrCode::ResOccupied => {
                        print!("资源已被占用");
                    }
                }
                println!("，{} 对资源 {} 的请求失败", pid, rid);
            }
        }
        res
    }

    pub unsafe fn release_report(
        me: * mut Self,
        pid: <Proc<'_, Data> as HasId>::IdType,
        rid: <Res<'_, Data> as HasId>::IdType,
    ) -> ReleaseResResult {
        let res = Self::release_res(me, pid, rid);
        match &res {
            Ok(_) => {
                println!("进程 {} 对资源 {} 释放成功", pid, rid);
            }
            Err(code) => {
                match code {
                    ReleaseResErrCode::ProcNotFound => {
                        print!("进程不存在");
                    }
                    ReleaseResErrCode::ResNotFound => {
                        print!("资源不存在")
                    }
                    ReleaseResErrCode::ProcNotOwnRes => {
                        print!("进程不持有资源")
                    }
                    ReleaseResErrCode::ResNotOwned => {
                        print!("资源未被持有")
                    }
                }
                println!("，进程 {} 对资源 {} 释放失败", pid, rid);
            }
        }
        res
    }
}