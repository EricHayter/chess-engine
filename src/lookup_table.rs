use crate::board;

use board::BitBoard;
use board::row;
use board::col;

struct LookupTable {
    attack_squares: [[BitBoard; 64]; board::NUMBER_OF_PIECE_TYPES],
    distance: [[usize; 64]; 64],
}

impl LookupTable {
    fn new() -> Self {
        let mut distance: [[usize; 64]; 64] = [[0; 64]; 64];
        let attack_squares: [[BitBoard; 64]; board::NUMBER_OF_PIECE_TYPES] = [[0; 64]; board::NUMBER_OF_PIECE_TYPES];

        for sq1 in 0..=100 {
            for sq2 in sq1..=100 {
                distance[sq1][sq2] = std::cmp::max(
                    row(sq1) - row(sq2),
                    col(sq1) - col(sq2)
                    );
                distance[sq2][sq1] = distance[sq1][sq2];
            }
        }

        LookupTable { 
            attack_squares: attack_squares,
            distance: distance,
        }

    } 
}
