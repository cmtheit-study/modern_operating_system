use crate::{Addr, AddrSize};
mod page_node;

pub struct Memory {

}

pub type ReadResult = Result<(), ReadErrCode>;
pub enum ReadErrCode {
    AddressNotAllocated,        // 要访问的地址没有被分配
    BufferSizeTooSmall
}

pub type AllocResult = Result<Vec<Addr>, AllocErrCode>;
pub enum AllocErrCode {

}

impl Memory {
    pub fn alloc(size: AddrSize) -> AllocResult {
        todo!();
        Ok(vec![])
    }

    pub fn get(addr: Addr, buf: &[u8], size: AddrSize) -> ReadResult {
        if let None = buf.get(size - 1) {
            Err(ReadErrCode::BufferSizeTooSmall)
        } else {
            todo!();
            Ok(())
        }
    }
}