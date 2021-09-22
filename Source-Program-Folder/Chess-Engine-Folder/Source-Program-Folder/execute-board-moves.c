
#include "../Header-Program-Folder/chess-engine-includer.h"

bool execute_piece_move(Board board, Move move, Info* info)
{
	if(!move_inside_board(move)) return false;

	switch(board_point_type(board, move.start))
	{
		case(EMPTY): return false;

		case(PAWN): return execute_pawn_move(board, move, info);

		case(ROOK): return execute_rook_move(board, move, info);

		case(KNIGHT): return execute_knight_move(board, move, info);

		case(BISHOP): return execute_bishop_move(board, move, info);

		case(QUEEN): return execute_queen_move(board, move, info);

		case(KING): return execute_king_move(board, move, info);

		default: return false;
	}
	return false;
}

bool execute_pawn_move(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);
	if(!piece_team_exists(team)) return false;

	if(board_points_equal(stop, info->passant))
	{
		Team enemy = piece_team_enemy(team);
		Point removePoint = passant_remove_point(info->passant, enemy);

		if(!point_inside_board(removePoint)) return false;

		move_board_piece(board, start, stop);
		remove_board_piece(board, removePoint);
	}
	else
	{
		move_board_piece(board, start, stop);
	}

	if(start.width == stop.width && abs(start.height - stop.height) == 2)
	{
		Point passantPoint = pawn_passant_point(stop, team);
		if(!point_inside_board(passantPoint)) return false;

		info->passant = passantPoint;
	}
	else
	{
		info->passant = EMPTY_POINT;
	}

	if(pawn_becomes_queen(stop, team))
	{
		allocate_board_piece(board, stop, (Piece) {QUEEN, team});
	}

	return true;
}

bool execute_rook_move(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);
	if(!piece_team_exists(team)) return false;

	// This executes the castle
	if(team_castle_valid(start, stop, team))
	{
		Point castleRook, castleKing;
		if(!extract_castle_points(&castleRook, &castleKing, start, stop, team)) return false;

		move_board_piece(board, stop, castleKing);
		move_board_piece(board, start, castleRook);

		update_castles_values(&info->castles, team, EMPTY_CASTLE);
	}
	else if(board_points_equal(stop, info->passant))
	{
		Team enemy = piece_team_enemy(team);
		Point removePoint = passant_remove_point(info->passant, enemy);

		if(!point_inside_board(removePoint)) return false;

		move_board_piece(board, start, stop);
		remove_board_piece(board, removePoint);
	}
	else
	{
		Side side = rook_starting_side(start.width);

		move_board_piece(board, start, stop);

		update_castles_value(&info->castles, team, side, false);
	}

	info->passant = EMPTY_POINT;

	return true;
}

bool execute_knight_move(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);
	if(!piece_team_exists(team)) return false;

	if(board_points_equal(stop, info->passant))
	{
		Team enemy = piece_team_enemy(team);
		Point removePoint = passant_remove_point(info->passant, enemy);

		if(!point_inside_board(removePoint)) return false;

		move_board_piece(board, start, stop);
		remove_board_piece(board, removePoint);
	}
	else
	{
		move_board_piece(board, start, stop);
	}

	info->passant = EMPTY_POINT;

	return true;
}

bool execute_bishop_move(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);
	if(!piece_team_exists(team)) return false;

	if(board_points_equal(stop, info->passant))
	{
		Team enemy = piece_team_enemy(team);
		Point removePoint = passant_remove_point(info->passant, enemy);

		if(!point_inside_board(removePoint)) return false;

		move_board_piece(board, start, stop);
		remove_board_piece(board, removePoint);
	}
	else
	{
		move_board_piece(board, start, stop);
	}

	info->passant = EMPTY_POINT;

	return true;
}

bool execute_queen_move(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);
	if(!piece_team_exists(team)) return false;

	if(board_points_equal(stop, info->passant))
	{
		Team enemy = piece_team_enemy(team);
		Point removePoint = passant_remove_point(info->passant, enemy);

		if(!point_inside_board(removePoint)) return false;

		move_board_piece(board, start, stop);
		remove_board_piece(board, removePoint);
	}
	else
	{
		move_board_piece(board, start, stop);
	}

	info->passant = EMPTY_POINT;

	return true;
}

bool execute_king_move(Board board, Move move, Info* info)
{
	// If the move is not in the board:
	if(!move_inside_board(move)) return false;

	Point start = move.start, stop = move.stop;

	Team team = board_point_team(board, start);
	if(!piece_team_exists(team)) return false;

	if(board_points_equal(stop, info->passant))
	{
		Team enemy = piece_team_enemy(team);
		Point removePoint = passant_remove_point(info->passant, enemy);

		if(!point_inside_board(removePoint)) return false;

		move_board_piece(board, start, stop);
		remove_board_piece(board, removePoint);
	}
	else
	{
		move_board_piece(board, start, stop);
	}

	update_castles_values(&info->castles, team, EMPTY_CASTLE);

	info->passant = EMPTY_POINT;

	return true;
}
