
change the board design (SDL graphics)

https://www.youtube.com/watch?v=kwQk5A26cis&t=246s


start using FEN board.



patch version:

possible, movable and prevent functions are most the same. Don't have repeating code!

add move to game move list in the execute functions

check the error handling




when board are passed in functions, pass pointer to board when it is changed


change the matrix value for the rook. He should want to castle


when checking if the point or the move is inside the board, it should return the bad value.


the turn indicator should only increase every second play (white and black) -> turn ++


pointer to those variables that is going to get changed (array int* -> int** );


Create Check-Indicator
