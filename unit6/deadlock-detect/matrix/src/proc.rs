#[derive(Debug)]
pub struct Proc<const N: usize> {
    tagged: bool,
    allocated: [usize; N],
    requesting: [usize; N]
}

impl<const N: usize> Proc<N> {
    pub fn new(allocated: Option<[usize; N]>, requesting: Option<[usize; N]>) -> Self {
        Self {
            tagged: false,
            allocated: if let Some(a) = allocated {
                a
            } else {
                [0; N]
            },
            requesting: if let Some(r) = requesting {
                r
            } else {
                [0; N]
            }
        }
    }

    pub fn tag(&mut self) {
        self.tagged = true
    }

    pub fn if_fulfill(&self, available: &[usize; N]) -> bool {
        !self.tagged && self.requesting
            .iter()
            .enumerate()
            .all(|(i, v)| {
                *v <= available[i]
            })
    }

    pub fn if_tagged(&self) -> bool {
        self.tagged
    }

    pub fn ret(&mut self, available: &mut [usize; N]) {
        self.tag();
        available.iter_mut()
            .enumerate()
            .for_each(|(i, v)| {
                *v += self.allocated[i]
            })
    }

    pub fn fulfill_ret(&mut self, available: &mut [usize; N]) -> bool {
        if self.if_fulfill(available) {
            self.ret(available);
            true
        } else {
            false
        }
    }
}