mod board;
mod lookup_table;

use board::{print_board, set_bit, BitBoard};

fn main() {
//    let square_distances: [[u8; 64];64];
//    let piece_attacks: [[board::BitBoard; 64]; 6];
    println!("Hello, world!");

    let mut board: BitBoard = 0;
    board = set_bit(board, 32);
    print_board(board);
}
