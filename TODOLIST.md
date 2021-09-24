
change the board design (SDL graphics)

https://www.youtube.com/watch?v=kwQk5A26cis&t=246s


start using FEN board.



patch version:

possible, movable and prevent functions are most the same. Don't have repeating code!

possible moves could check if the info.current matches the piece that is moving.

check the error handling



console funtions rename!


change the matrix value for the rook. He should want to castle


when checking if the point or the move is inside the board, it should return the bad value.


the turn indicator should only increase every second play (white and black) -> turn ++


pointer to those variables that is going to get changed (array int* -> int** );
