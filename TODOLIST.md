
2.0.2

break out the loop-code in the best_possible_move and the board_depth_value function.

computer program: best_possible_move -> init "best move" should be last move in move array



2.0.3
remove some error messages, only the necessary error messages should exists.

fix the errors that can occur in the screen display functions



2.0.4
the code should be more hard-coded. BOARD_HEIGHT is fine, but not so loose code in general...

when checking if the point or the move is inside the board, it should return the bad value.

the variables can be defined inside of a loop. The code will look better that way.



2.1.0
possible, movable and prevent functions are most the same. Don't have repeating code!

possible moves could check if the info.current matches the piece that is moving.

change the order of the pieces to [EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING]



2.2.0
change the castle move. The king should move two steps to the rook instead

the turn indicator should only increase every second play (white and black) -> turn ++



2.3.0
implement the "counter" (50-move rule).

implement "three fold repetition". If the same moves repeat three times, its a draw



0.X.0
start using FEN board.
