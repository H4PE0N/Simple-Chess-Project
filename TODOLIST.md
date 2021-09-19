
change the board design (SDL graphics)

https://www.youtube.com/watch?v=kwQk5A26cis&t=246s


start using FEN board.

implement passant rule


change every curr.. to current and so on..

rename moveable to movable


make the execute functions return a bool value. If they cant execute, it should return false;


maybe: In the beginning of [prevent, movable, possible]

change the matrix value for the rook. He should want to castle


check the bool values of the functions. I think that the bool values returned is wrong in some cases

when checking if the point or the move is inside the board, it should return the bad value.


the turn indicator should only increase every second play (white and black) -> turn ++


pointer to those variables that is going to get changed (array int* -> int** );

Create Check-Indicator
