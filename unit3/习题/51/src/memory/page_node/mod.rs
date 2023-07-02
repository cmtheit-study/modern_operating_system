use std::cmp::{Ordering, PartialOrd};

mod page_frame;

type Flags = u8;
type PageNumType = u32;

/**
    **页框节点，构成内存页框**
 可以通过 > 、< 、= 来比较两个 page_node 的大小
*/
pub struct PageNode {
    flags: Flags,
    page_num: PageNumType,      // 页面数量
    next: Option<Box<PageNode>>
}

pub const USED_BIT: u8 = (!0u8 >> 1);     // 该节点是否被进程使用

impl PageNode {
    pub fn new(page_num: PageNumType) -> Self {
        Self {
            flags: 0,
            page_num,
            next: None
        }
    }

    /**
    是否设置被进程使用位
    */
    pub fn if_set_used_bit(&self) -> bool {
        self.flags & USED_BIT != 0
    }

    /**
    设置被进程使用位
    */
    pub fn set_used_bit(&mut self) {
        self.flags &= USED_BIT;
    }

    /**
    设置 next 指向另一个节点
    */
    pub fn set_next(&mut self, other: Self) {
        self.next = Some(Box::new(other));
    }

    pub fn if_has_next(&self) -> bool {
        if let None = self.next {
            false
        } else {
            true
        }
    }

    pub fn get_page_num(&self) -> PageNumType {
        self.page_num
    }

    pub fn set_page_num(&mut self, new_page_num: PageNumType) {
        self.page_num = new_page_num;
    }
}

impl PartialEq<Self> for PageNode {
    fn eq(&self, other: &Self) -> bool {
        self.page_num.eq(&other.page_num)
    }
}

impl PartialOrd for PageNode {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        self.page_num.partial_cmp(&other.page_num)
    }
}

