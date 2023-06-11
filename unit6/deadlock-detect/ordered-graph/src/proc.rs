use crate::res::Res;
use std::hash::{Hash, Hasher};
use crate::{HasId, Side};

type Id = i32;

pub struct Proc<'a, T> {       // 代表一个进程
    id: Id,
    owned: Vec<Side<'a, Res<'a, T>>>
}

impl<'a, T> Proc<'a, T> {
    pub fn new() -> Self {
        static mut ID: Id = 0;
        unsafe {
            ID += 1;
            Self {
                id: ID,
                owned: vec![]
            }
        }
    }

    pub fn own(&'a mut self, res: &'a Res<'a, T>) {
        self.owned.push(res);
    }

    pub(crate) fn release(&'a mut self, res: &'a Res<'a, T>) {
        let mut remove_idx: i32 = -1;
        for r_idx in 0..self.owned.len() {
            if self.owned[r_idx].get_id() == res.get_id() {
                remove_idx = r_idx as i32;
                break;
            }
        }
        if remove_idx >= 0 {
            self.owned.remove(remove_idx as usize);
        }
    }

    pub(crate) fn if_own_res(&'a self, rid: <Res<'a, T> as HasId>::IdType) -> bool {
        self.owned.iter().any(|r| {
            r.get_id() == rid
        })
    }

    pub(crate) fn detect_circle(&'a self,
                                proc_detected: &mut Vec<&Proc<'a, T>>,
                                res_detected: &mut Vec<&Res<'a, T>>) -> bool {
        return if proc_detected.iter().any(|p| {
            p.get_id() == self.id
        }) {
            true
        } else {
            proc_detected.push(self);
            self.owned
                .iter()
                .any(|r| {
                    r.detect_circle(proc_detected, res_detected)
                })
        }
    }
}

impl<T> Hash for Proc<'_, T> {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state)
    }
}

impl<'a, T> HasId for Proc<'a, T> {
    type IdType = Id;

    fn get_id(&self) -> Self::IdType {
        self.id
    }
}