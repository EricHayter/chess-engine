use std::thread::current;

use crate::board;

use board::{BitBoard, Square, Direction, row, col};

pub struct LookupTable {
    pub attack_squares: [[BitBoard; 64]; board::NUMBER_OF_PIECE_TYPES],
    pub distance: [[usize; 64]; 64],
}

impl LookupTable {
    pub fn new() -> Self {
        let mut distance: [[usize; 64]; 64] = [[0; 64]; 64];
        let attack_squares: [[BitBoard; 64]; board::NUMBER_OF_PIECE_TYPES] = [[0; 64]; board::NUMBER_OF_PIECE_TYPES];

        for sq1 in 0..=63 {
            for sq2 in sq1..=63 {
                distance[sq1][sq2] = std::cmp::max(
                    row(sq1).abs_diff(row(sq2)),
                    col(sq1).abs_diff(col(sq2))
                    );
                distance[sq2][sq1] = distance[sq1][sq2];
            }
        }

        LookupTable { 
            attack_squares,
            distance: distance,
        }
    } 

    fn rook_attacks(square: Square, dir: Direction) {
        let mut current_square: Square = square;
        let mut next_square: Square = square;
        while current_square < 64 && distance[current_square][next_square] <= 2
    }
}
