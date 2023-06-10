use std::hash::{Hash, Hasher};
use crate::proc::Proc;
use crate::{HasId, Side};

type Id = i32;

pub struct Res<'a, T> {     // 表示一个资源节点
    id: Id,
    pub data: T,                    // 资源数据
    requested: Vec<Side<'a, Proc<'a, T>>>   // 请求该资源的进程（入边）
}

impl<'a, T> Res<'a, T> {
    pub fn new(data: T) -> Self {
        static mut ID: Id = 0;
        unsafe {
            ID += 1;
            Self {
                id: ID,
                data,
                requested: vec![]
            }
        }
    }

    pub fn request(&'a mut self, proc: &'a Proc<'a, T>) {
        self.requested.push(proc);
    }

     pub(crate) fn detect_circle(&'a self,
                                proc_detected: &mut Vec<&Proc<'a, T>>,
                                res_detected: &mut Vec<&Res<'a, T>>) -> bool {
         return if res_detected.iter().any(|r| {
            r.get_id() == self.id
        }) {
            true
        } else {
             res_detected.push(self);
             self.requested
                .iter()
                .any(|p| {
                    p.detect_circle(proc_detected, res_detected)
                })
        }
     }
}

impl<T> Hash for Res<'_, T> {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

impl<'a, T> HasId for Res<'a, T> {
    type IdType = Id;

    fn get_id(&self) -> Self::IdType {
        self.id
    }
}