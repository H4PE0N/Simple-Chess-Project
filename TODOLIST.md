
change the board design (SDL graphics)

https://www.youtube.com/watch?v=kwQk5A26cis&t=246s


start using FEN board.

implement passant rule




1. Remove all "check_after_castling" and "check_after....", and instead use "move_prevent_check"
  1. Merge the different piece execute function into each other.
    - copy the different code in the execute castle function and paste it in the execute rook function with a if statement infront to signal that its different in the castle case

  2. Now you should be able to remove the "check_after_castling" and "check_after...." functions, because the only difference between those and the move_prevent_check functions, is that the move_prevent_check functions can execute every piece move

2. Merge the different piece acceptable functions into each other.
  - copy the different code in the accept castle function and paste it in the accept rook function with a if statement infront to signal that its different in the castle case

3. Implement the passant rule, by implenting a if statement in the accept and in the execute functions to do a little different operation if the passant rule is implide.






Look on New-Handler, and change the execute functions so that they can execute both normal and (castle) operations (example)

Remove all "check_after_castling" and "check...". Instead use only "move_prevent_check", and make it so that the piece_exeucte functions execute all different operations


rename moveable to movable

implement type check in valid functions (type == PAWN)

change the matrix value for the rook. He should want to castle


check the bool values of the functions. I think that the bool values returned is wrong in some cases

when checking if the point or the move is inside the board, it should return the bad value.


the turn indicator should only increase every second play (white and black) -> turn ++


pointer to those variables that is going to get changed (array int* -> int** );

Create Check-Indicator
