
#include "../Header-Program-Folder/chess-engine-includer.h"

bool piece_move_acceptable(Board board, Move move, Info info)
{
	if(!move_inside_board(move)) return false;

	switch(board_point_type(board, move.start))
	{
		case(EMPTY): return false;

		case(PAWN): return pawn_move_acceptable(board, move, info);

		case(ROOK): return rook_move_acceptable(board, move, info);

		case(KNIGHT): return knight_move_acceptable(board, move, info);

		case(BISHOP): return bishop_move_acceptable(board, move, info);

		case(QUEEN): return queen_move_acceptable(board, move, info);

		case(KING): return king_move_acceptable(board, move, info);

		default: return false;
	}
	return false;
}

bool pawn_acceptable_handler(Board board, Move move, Info info)
{
  return pawn_move_acceptable(board, move, info);
}

bool rook_acceptable_handler(Board board, Move move, Info info)
{
  if(!move_inside_board(move)) return false;

  Team team = board_point_team(board, move.start);
  if(!piece_team_exists(team)) return false;

  Piece stopPiece = board_point_piece(board, move.stop);

  // If the stop is the team king, then it is castles:
  if(board_pieces_equal(stopPiece, (Piece) {KING, team}))
  {
    return team_castle_acceptable(board, move, info);
  }
  else return rook_move_acceptable(board, move, info);
}

bool knight_acceptable_handler(Board board, Move move, Info info)
{
  return knight_move_acceptable(board, move, info);
}

bool bishop_acceptable_handler(Board board, Move move, Info info)
{
  return bishop_move_acceptable(board, move, info);
}

bool queen_acceptable_handler(Board board, Move move, Info info)
{
  return queen_move_acceptable(board, move, info);
}

bool king_acceptable_handler(Board board, Move move, Info info)
{
  return king_move_acceptable(board, move, info);
}

bool straight_acceptable_handler(Board board, Move move, Info info)
{
  return straight_move_acceptable(board, move, info);
}

bool diagonal_acceptable_handler(Board board, Move move, Info info)
{
  return diagonal_move_acceptable(board, move, info);
}
