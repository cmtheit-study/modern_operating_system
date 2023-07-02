type Flags = u8;

pub(crate) struct Page {    // 页表项
    flags: Flags,

}

const R_BIT: Flags  = 1 << (Flags::BITS - 1);
const M_BITS: Flags = R_BIT >> 1;
const V_BITS: Flags = M_BITS >> 1;

impl Page {


    pub fn if_r_set(&self) -> bool{
        self.flags & R_BIT != 0
    }

    pub fn if_m_set(&self) -> bool {
        self.flags & M_BITS != 0
    }

    pub fn if_v_set(&self) -> bool {
        self.flags & V_BITS != 0
    }

    pub fn r_set(&mut self) {
        self.flags |= R_BIT;
    }

    pub fn m_set(&mut self) {
        self.flags |= M_BITS;
    }

    pub fn v_set(&mut self) {
        self.flags |= V_BITS;
    }
}