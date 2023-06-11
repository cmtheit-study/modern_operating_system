use crate::proc::Proc;

#[cfg(test)]
mod test;

mod proc;

pub fn if_dead_lock<const N: usize>(procs: &[Proc<N>]) ->bool {
    procs.iter()
        .any(|p| {
            !p.if_tagged()
        })
}