use bitset_core::BitSet;

type AgingType = [u8; 4];

pub struct PageFrame {
    aging: AgingType
}

impl PageFrame {
    pub fn new() -> Self {
        Self {
            aging: AgingType::default()
        }
    }
}