mod board;
mod lookup_table;

use board::{print_board, set_bit, BitBoard, square};
use lookup_table::LookupTable;

fn main() {
//    let square_distances: [[u8; 64];64];
//    let piece_attacks: [[board::BitBoard; 64]; 6];
    println!("Hello, world!");

    let mut board: BitBoard = 0;
    let sq1 = square("A", 3);
    let sq2 = square("b", 7);
    board = set_bit(board, sq1);
    board = set_bit(board, sq2);
    print_board(board);
    
    let lookup_table: LookupTable = LookupTable::new();
    println!("{}", lookup_table.distance[sq2][sq1])
}
