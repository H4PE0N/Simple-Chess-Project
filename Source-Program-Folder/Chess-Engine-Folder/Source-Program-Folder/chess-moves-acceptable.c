
#include "../Header-Program-Folder/chess-engine-includer.h"

bool piece_move_acceptable(Board board, Move move, Info info)
{
	switch(board_point_type(board, move.start))
	{
		case(EMPTY): return false;

		case(PAWN): return pawn_move_acceptable(board, move, info);

		case(ROOK): return rook_move_acceptable(board, move, info);

		case(KNIGHT): return knight_move_acceptable(board, move, info);

		case(BISHOP): return bishop_move_acceptable(board, move, info);

		case(QUEEN): return queen_move_acceptable(board, move, info);

		case(KING): return king_move_acceptable(board, move, info);
	}
	return false;
}

bool queen_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_queen_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool pawn_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_point_type(board, stop) == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_pawn_valid(board, start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	// These controls are vary specific, and should be done last
	if(start.width == stop.width) // Going straight
	{
		if(!board_point_empty(board, stop)) return false;
	}
	else if(points_not_enemy(board, start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool rook_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	// These controls are more specific, and should be done later
	if(!moving_rook_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	// This is a special case, and will skip the following controls
	if(team_castle_acceptable(board, move, info)) return true;

	// These controls are more specific, and should be done later
	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool bishop_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_bishop_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool king_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_king_valid(start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool diagonal_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_diagonal_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool straight_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	// These controls are more specific, and should be done later
	if(!moving_straight_valid(start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	// This is a special case, and will skip the following controls
	if(team_castle_acceptable(board, move, info)) return true;

	// These controls are more specific, and should be done later
	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool knight_move_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	// These controls is the most obvious, and should be done first
	if(!points_inside_board(start, stop)) return false;

	if(board_point_empty(board, start)) return false;

	if(board_points_team(board, start, stop)) return false;

	if(board_point_type(board, stop) == KING) return false;

	// These controls are more specific, and should be done later
	if(!moving_knight_valid(start, stop)) return false;

	if(!move_prevent_check(board, move, info)) return false;

	return true;
}

bool castle_bool_valid(Point start, Info info, Team team)
{
	Castle castle = {false, false};

	if(team == WHITE) castle = info.whiteRKS;
	if(team == BLACK) castle = info.blackRKS;

	return (start.width == 0) ? castle.queen : castle.king;
}

bool team_castle_acceptable(Board board, Move move, Info info)
{
	Point start = move.start, stop = move.stop;

	if(!points_inside_board(start, stop)) return false;

	Team team = board_point_team(board, start);

	Point king = board_piece_point(board, (Piece) {KING, team});
	if(!point_inside_board(king)) return false;

	// This is a special case, you cant switch if the king is in check
	if(king_inside_check(board, king)) return false;

	// This checks if the rook and the king is on the right place
	if(!team_castle_valid(board, start, stop)) return false;

	if(!clear_moving_path(board, start, stop)) return false;

	// This checks that the operation is clear to go (true)
	if(!castle_bool_valid(start, info, team)) return false;

	if(check_after_castling(board, move, info)) return false;

	return true;
}

bool check_after_castling(Board board, Move move, Info info)
{
	if(!move_inside_board(move)) return false;

	Team team = board_point_team(board, move.start);

	Board boardCopy = copy_chess_board(board);
	Info infoDummy = info;

	execute_team_castle(boardCopy, move, &infoDummy);

	Point king = board_piece_point(boardCopy, (Piece) {KING, team});

	// If the king cant be found after the switch, it must have been taken
	if(!point_inside_board(king)) return true;

	// If the king is inside check, it is "check_after_castling" (true)
	if(king_inside_check(boardCopy, king))
	{
		free_chess_board(boardCopy); return true;
	}

	free_chess_board(boardCopy); return false;
}

bool clear_moving_path(Board board, Point start, Point stop)
{
	int heightOffset = (stop.height - start.height);
	int widthOffset = (stop.width - start.width);

	// If the knight is moving, he dont need a clear moving path
	if(moving_knight_valid(start, stop)) return true;

	int steps = (abs(heightOffset) > abs(widthOffset)) ? abs(heightOffset) : abs(widthOffset);

	int heightAdder = (heightOffset == 0) ? 0 : (heightOffset / abs(heightOffset));
	int widthAdder = (widthOffset == 0) ? 0 : (widthOffset / abs(widthOffset));

	int height, width;

	Point point;

	for(int index = 1; index < steps; index = index + 1)
	{
		height = start.height + (index * heightAdder);
		width = start.width + (index * widthAdder);

		point = (Point) {height, width};

		if(!board_point_empty(board, point)) return false;
		// Was board_point_clear
	}
	return true;
}
