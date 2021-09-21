
#include "../Header-Program-Folder/chess-engine-includer.h"

bool execute_piece_move(Board board, Move move, Info* info)
{
	if(!move_inside_board(move)) return false;

	switch(board_point_type(board, move.start))
	{
		case(EMPTY): return false;

		case(PAWN): return pawn_execute_handler(board, move, info);

		case(ROOK): return rook_execute_handler(board, move, info);

		case(KNIGHT): return knight_execute_handler(board, move, info);

		case(BISHOP): return bishop_execute_handler(board, move, info);

		case(QUEEN): return queen_execute_handler(board, move, info);

		case(KING): return king_execute_handler(board, move, info);

		default: return false;
	}
	return false;
}

bool pawn_execute_handler(Board board, Move move, Info* info)
{
  return execute_pawn_move(board, move, info);
}

bool rook_execute_handler(Board board, Move move, Info* info)
{
  if(!move_inside_board(move)) return false;

  Team team = board_point_team(board, move.start);
  if(!piece_team_exists(team)) return false;

  Piece stopPiece = board_point_piece(board, move.stop);

  // If the stop is the team king, then it is castles:
  if(board_pieces_equal(stopPiece, (Piece) {KING, team}))
  {
    return execute_team_castle(board, move, info);
  }
  else return execute_pawn_move(board, move, info);
}

bool bishop_execute_handler(Board board, Move move, Info* info)
{
  return execute_bishop_move(board, move, info);
}

bool knight_execute_handler(Board board, Move move, Info* info)
{
  return execute_knight_move(board, move, info);
}

bool queen_execute_handler(Board board, Move move, Info* info)
{
  return execute_queen_move(board, move, info);
}

bool king_execute_handler(Board board, Move move, Info* info)
{
  return execute_king_move(board, move, info);
}
