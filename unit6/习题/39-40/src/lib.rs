mod chimp;

use std::collections::VecDeque;
use rand::random;
use crate::chimp::{Chimp, State};
use colorized::*;
use conv::*;

pub struct Rope<const N: usize> {
    chimps: VecDeque<Chimp<N>>
}

#[derive(Ord, PartialOrd, Eq, PartialEq)]
pub enum Direction {
    HasLeft,
    HasRight,
    DoNotHas
}

impl<const N: usize> Rope<N> {
    pub fn new() -> Self {
        Self {
            chimps: VecDeque::new()
        }
    }

    pub fn add_chimp(&mut self) {
        self.chimps.push_back(random());
    }

    fn get_direction(&self) -> Direction {
        if let Some(chimp) = self.chimps.front() {
            match chimp.state {
                State::Waiting => {
                    Direction::DoNotHas
                }
                State::Climbing(_) => {
                    match chimp.direction {
                        chimp::Direction::GoLeft => {
                            Direction::HasLeft
                        }
                        chimp::Direction::GoRight => {
                            Direction::HasRight
                        }
                    }
                }
            }
        } else {
            Direction::DoNotHas
        }
    }

    pub fn next(&mut self) {
        if random::<f64>() < 1.0 / f64::value_from(N / 2 + 1).unwrap() {
            self.add_chimp();
        }
        let mut idx: usize = 0;
        match self.get_direction() {
            Direction::DoNotHas => {
                if let Some(chimp) = self.chimps.get_mut(idx) {
                    if chimp.if_waiting() {
                        chimp.begin_climb()
                    }
                }
            }
            direction => {
                loop {
                    if let Some(chimp) = self.chimps.get_mut(idx) {
                        if chimp.if_climbing() {
                             chimp.continue_climb();
                            if chimp.if_end_climbing() {
                                self.chimps.remove(idx);
                                break
                            }
                        } else {
                            match direction {
                                Direction::HasLeft => {
                                    if chimp.if_go_left() {
                                        chimp.begin_climb()
                                    }
                                }
                                Direction::HasRight => {
                                    if chimp.if_go_right() {
                                        chimp.begin_climb()
                                    }
                                }
                                Direction::DoNotHas => {}
                            }
                            break
                        }
                    } else {
                        break
                    }
                    idx += 1;
                }
            }
        }
    }

    pub fn report(&self) {
        match self.get_direction() {
            Direction::HasLeft => {
                print!("<-");
            }
            Direction::HasRight => {
                print!("->")
            }
            Direction::DoNotHas => {
                print!("==")
            }
        }
        print!(" ");
        for chimp in &self.chimps {
            if chimp.if_climbing() {
                print!("{} ", chimp.get_left_climb_time().to_string().color(Colors::GreenFg))
            } else {
                print!("{} ", chimp.get_left_climb_time().to_string().color(Colors::BrightBlackFg))
            }
        }
        println!();
    }
}