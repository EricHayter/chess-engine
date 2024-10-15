pub type BitBoard = u64;
pub type Square = usize;

pub fn row(square: Square) -> usize {
    square / 8
}

pub fn col(square: Square) -> usize {
    square % 8
}

pub fn shift(square: Square, direction: Direction) -> Square {
    match direction {
        Direction::North => square - 8,
        Direction::NorthEast => square - 7,
        Direction::East => square + 1,
        Direction::SouthEast => square + 9,
        Direction::South => square + 8,
        Direction::SouthWest => square + 7,
        Direction::West => square - 1,
        Direction::NorthWest => square - 9,
    }
}

pub fn print_board(board: BitBoard) {
    let mut square: u64 = 1;
    for row in 0..=7 {
        print!("{}   ", 8-row);
        for _ in 0..=7 {
            if (square & board) > 0 {
                print!("1 ");
            } else {
                print!("0 ");
            }
            square <<= 1;
        }
        print!("\n");
    }
    println!();
    println!("    a b c d e f g h\n");
    println!("Board: {}", board);
}

pub fn set_bit(bb: BitBoard, square: Square) -> BitBoard {
    1 << square as u8 | bb
}

pub fn reset_bit(bb: BitBoard, square: Square) -> BitBoard {
    !(1 << square as u8) | bb
}

pub const NUMBER_OF_PIECE_TYPES: usize = 6;
pub enum PieceType {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
}

pub enum Direction {
    North,
    NorthEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NorthWest,
}

/* Board representation:
 * A8, B8, C8, D8, E8, F8, G8, H8,
 * A7, B7, C7, D7, E7, F7, G7, H7,
 * A6, B6, C6, D6, E6, F6, G6, H6,
 * A5, B5, C5, D5, E5, F5, G5, H5,
 * A4, B4, C4, D4, E4, F4, G4, H4,
 * A3, B3, C3, D3, E3, F3, G3, H3,
 * A2, B2, C2, D2, E2, F2, G2, H2,
 * A1, B1, C1, D1, E1, F1, G1, H1,
 *
 * By convention I will store the top left square, A8, in the LSB of a 64 bit 
 * int and H1 will be stored in the MSB of the 64 bit int.
 */


