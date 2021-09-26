
#include "../Header-Program-Folder/chess-engine-includer.h"

// This function should only check one team, so that the draw gets right
bool game_still_running(Team* winner, Board board, Info info)
{
	Team team;
	Point king;

	// In one iteration of the loop, it checks one team
	for(int round = 0; round < 2; round = round + 1)
	{
		team = (round == 0) ? WHITE : BLACK;

		king = board_piece_point(board, (Piece) {KING, team});

		// If the king is not on the board, the other player winns.
		// Or do neither of them win?
		if(!point_inside_board(king))
		{
			*winner = piece_team_enemy(team);
			// *winner = NONE;
			return false;
		}

		if(check_mate_situation(board, info, team))
		{
			*winner = piece_team_enemy(team);
			return false;
		}
		if(check_draw_situation(board, info, team))
		{
			*winner = NONE;
			return false;
		}
	}
	return true;
}

bool team_pieces_movable(Board board, Info info, Team team)
{
	if(!piece_team_exists(team)) return false;

	Team currentTeam;
	Point point;

	for(int height = 0; height < BOARD_HEIGHT; height = height + 1)
	{
		for(int width = 0; width < BOARD_WIDTH; width = width + 1)
		{
			point = (Point) {height, width};
			currentTeam = board_point_team(board, point);

			if(currentTeam != team) continue;

			if(board_piece_movable(board, info, point)) return true;
		}
	}
	return false;
}

bool check_draw_situation(Board board, Info info, Team team)
{
	Point king = board_piece_point(board, (Piece) {KING, team});

	if(!point_inside_board(king)) return false;

	// If the teams king is in check, this function says that it cant be a draw,
	// even if there is "insufficient material" (little material)

	// If you want this function to directly say that it is a draw if there is
	// "insufficient material", you can move the "king_inside_check" function
	// after the "little_material_draw" function. That will check the
	// "insufficient material" first of all.

	if(king_inside_check(board, king)) return false;

	// This is a special case, where the game just becomes a draw:
	if(little_material_draw(board)) return true;

	if(team_pieces_movable(board, info, team)) return false;

	return true;
}

// A lone king
// a king and [bishop or knight]
bool little_material_draw(Board board)
{
	bool whiteEnough = team_enough_materials(board, WHITE);
	bool blackEnough = team_enough_materials(board, BLACK);

	return (!whiteEnough && !blackEnough);
}

//
bool team_enough_materials(Board board, Team team)
{
	// If the team is not WHITE or BLACK, they dont have enough materials
	if(!piece_team_exists(team)) return false;


	Point point;
	Piece piece;

	bool kingExists = false;

	int minors = 0;
	int majors = 0;

	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		for(int width = 0; width < BOARD_WIDTH; width += 1)
		{
			point = (Point) {height, width};
			piece = board_point_piece(board, point);


			if(piece.team != team) continue;


			if(piece.type == KING) kingExists = true;

			else if(piece.type == ROOK || piece.type == QUEEN || piece.type == PAWN) majors += 1;

			else if(piece.type == KNIGHT || piece.type == BISHOP) minors += 1;


			if(kingExists && (majors >= 1 || minors >= 2)) return true;
		}
	}
	return false;
}

bool check_mate_situation(Board board, Info info, Team team)
{
	Point king = board_piece_point(board, (Piece) {KING, team});

	// I think that you return true in this case
	// If the king does not exist, it must be checkmate of some kind?
	if(!point_inside_board(king)) return true;

	if(!king_inside_check(board, king)) return false;

	if(team_prevent_check(board, info, team)) return false;

	return true;
}
