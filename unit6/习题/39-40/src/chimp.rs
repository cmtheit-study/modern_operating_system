use rand::prelude::Distribution;
use rand::{random, Rng};
use rand::distributions::Standard;

pub enum Direction {
    GoLeft,
    GoRight
}

pub enum State {
    Waiting,
    Climbing(usize)
}

pub struct Chimp<const N: usize> {
    pub(crate) direction: Direction,
    pub(crate) state: State
}

impl<const N: usize> Chimp<N> {
    pub fn new(direction: Direction) -> Self {
        Self {
            direction,
            state: State::Waiting
        }
    }

    pub fn if_go_left(&self) -> bool {
        if let Direction::GoLeft = self.direction {
            true
        } else {
            false
        }
    }

    pub fn if_go_right(&self) -> bool {
        if let Direction::GoRight = self.direction {
            true
        } else {
            false
        }
    }

    pub fn if_waiting(&self) -> bool {
        if let State::Waiting = self.state {
            true
        } else {
            false
        }
    }

    pub fn if_climbing(&self) -> bool {
        if let State::Climbing(_) = self.state {
            true
        } else {
            false
        }
    }

    pub fn if_end_climbing(&self) -> bool {
        if let State::Climbing(0) = self.state {
            true
        } else {
            false
        }
    }

    pub fn continue_climb(&mut self) {
        if let State::Climbing(left) = &mut self.state {
            if *left > 0 {
                *left -= 1
            }
        }
    }

    pub fn begin_climb(&mut self) {
        if let State::Waiting = self.state {
            self.state = State::Climbing(N);
        }
    }

    pub fn get_left_climb_time(&self) -> usize {
        if let State::Climbing(left) = self.state {
            left
        } else {
            0
        }
    }
}

impl<const N: usize> Distribution<Chimp<N>> for Standard {
    fn sample<R: Rng + ?Sized>(&self, _: &mut R) -> Chimp<N> {
        Chimp::new(if random::<f32>() < 0.5 {
            Direction::GoLeft
        } else {
            Direction::GoRight
        })
    }
}
