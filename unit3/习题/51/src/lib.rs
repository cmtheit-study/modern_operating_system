#[cfg(test)]
mod test;

mod page;
mod memory;
mod proc;

type Addr = u32;    // 32 位系统
type AddrSize = u32;

pub use memory::Memory;