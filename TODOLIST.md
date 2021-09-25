
check the error handling



patch version:

computer program: best_possible_move -> init "best move" should be last move in move array

fix draw function: If only two kings remain -> draw

fix "en passant": only a pawn can capture an "en passant"





when checking if the point or the move is inside the board, it should return the bad value.

remove some error messages, only the necessary error messages should exists.

the code should be more hard-coded. BOARD_HEIGHT is fine, but not so loose code in general...

fix the errors that can occur in the screen display functions



possible, movable and prevent functions are most the same. Don't have repeating code!

possible moves could check if the info.current matches the piece that is moving.



change the castle move. The king should move two steps to the rook instead

the turn indicator should only increase every second play (white and black) -> turn ++

change the order of the pieces to [EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING]



start using FEN board.
