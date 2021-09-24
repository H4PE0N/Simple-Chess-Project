
patch version:

possible, movable and prevent functions are most the same. Don't have repeating code!

possible moves could check if the info.current matches the piece that is moving.

check the error handling



start using FEN board.

fix draw function: If only two kings remain -> draw

change the matrix value for the rook. He should want to castle

when checking if the point or the move is inside the board, it should return the bad value.

the turn indicator should only increase every second play (white and black) -> turn ++
