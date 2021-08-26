
#include "../Header-Program-Folder/chess-computer-program.h"

bool computer_chess_move(Board board, Info* info, Color color)
{
	Move move = {(Point) {-1, -1}, (Point) {-1, -1}};

	if(!find_computer_move(&move, board, info, color)) return false;

	Piece piece = board_point_piece(board, move.start);
	Point* king = (color == WHITE) ? &info->wKing : &info->bKing;

	if(piece.type == KING) *king = move.stop;

	if(!move_chess_piece(board, move, info)) return false;

	return true;
}

bool simulate_enemy_check(Board board, Point start, Point stop)
{
	Color s_color = board_point_color(board, start);

	if(s_color == NONE) return false;

	Color color = (s_color == WHITE) ? BLACK : WHITE;

	Board copy = copy_chess_board(board);
	move_board_piece(copy, start, stop);

	if(!king_check_situation(copy, stop, color))
	{ 
		free(copy); return true; 
	}

	free(copy); return false;
}

bool find_computer_move(Move* move, Board board, Info* info, Color color)
{
	Move* moves = all_possible_moves(board, info, color);
	int amount = moves_array_amount(moves);

	if(amount == 0) { free(moves); return false; }

	printf("[%d] random moves generated!\n", amount);

	int random = create_random_number(0, amount - 1);

	BestMove bestMove = create_bestMove_data(board, moves[random]);
	Move current;

	for(int index = 0; index < amount; index += 1)
	{
		current = moves[index];
		update_best_move(&bestMove, board, current);
	}

	*move = bestMove.move; free(moves); return true;
}

BestMove create_bestMove_data(Board board, Move move)
{
	Point c_start = move.start, c_stop = move.stop;

	bool setsCheck = simulate_enemy_check(board, c_start, c_stop);
	bool takeEnemy = board_points_enemy(board, c_start, c_stop);
	bool getsTaken = piece_can_get_taken(board, c_start, c_stop);

	return (BestMove) {move, setsCheck, takeEnemy, getsTaken};
}

void update_best_move(BestMove* bestMove, Board board, Move move)
{
	BestMove current = create_bestMove_data(board, move);

	if(current_move_better(board, *bestMove, current)) *bestMove = current;
}

bool piece_can_get_taken(Board board, Point start, Point stop)
{
	// This function should return if the piece can 
	// get taken at the spot that its moving to

	// This is super risky! Edit this function!
	return !simulate_check_move(board, start, stop);
}

// setsCheck	takeEnemy	!getsTaken
// !setsCheck	takeEnemy	!getsTaken
// setsCheck	!takeEnemy	!getsTaken
// !setsCheck	!takeEnemy	!getsTaken

// setsCheck	takeEnemy	getsTaken
// !setsCheck	takeEnemy	getsTaken
// setsCheck	!takeEnemy	getsTaken
// !setsCheck	!takeEnemy	getsTaken

// ==================================

// setsCheck	takeEnemy	!getsTaken	exposed
// !setsCheck	takeEnemy	!getsTaken	exposed
// setsCheck	!takeEnemy	!getsTaken	exposed
// !setsCheck	!takeEnemy	!getsTaken	exposed
// setsCheck	takeEnemy	getsTaken	exposed
// !setsCheck	takeEnemy	getsTaken	exposed
// setsCheck	!takeEnemy	getsTaken	exposed
// !setsCheck	!takeEnemy	getsTaken	exposed

// setsCheck	takeEnemy	!getsTaken	!exposed
// !setsCheck	takeEnemy	!getsTaken	!exposed
// setsCheck	!takeEnemy	!getsTaken	!exposed
// !setsCheck	!takeEnemy	!getsTaken	!exposed
// setsCheck	takeEnemy	getsTaken	!exposed
// !setsCheck	takeEnemy	getsTaken	!exposed
// setsCheck	!takeEnemy	getsTaken	!exposed
// !setsCheck	!takeEnemy	getsTaken	!exposed

bool current_move_better(Board board, BestMove bestMove, BestMove current)
{
	Type currType = board_point_type(board, current.move.stop);
	Type bestType = board_point_type(board, bestMove.move.stop);

	// Not get taken and best do get taken
	if(!current.getsTaken && bestMove.getsTaken) return true;
	
	// Not get taken and get enemy and best dont get enemy
	else if(!current.getsTaken && current.takeEnemy && !bestMove.takeEnemy) return true;
	
	// not get taken and take enemy and sets check and best dont sets check
	else if(!current.getsTaken && current.takeEnemy && current.setsCheck && !bestMove.setsCheck) return true;
	
	// not get taken and dont take enemy but sets check and best dont sets check
	else if(!current.getsTaken && !current.takeEnemy && current.setsCheck && !bestMove.setsCheck) return true;
	
	// if get taken and take enemy and best dont take enemy
	else if(current.getsTaken && current.takeEnemy && !bestMove.takeEnemy) return true;
	
	// it get taken and take enemy and sets check and best dont sets check
	else if(current.getsTaken && current.takeEnemy && current.setsCheck && !bestMove.setsCheck) return true;

	// it get taken and dont take enemy but sets check and best dont
	else if(current.getsTaken && !current.takeEnemy && current.setsCheck && !bestMove.setsCheck) return true;
	
	else if(currType > bestType) return true;

	return false;
}

Move* all_possible_moves(Board board, Info* info, Color color)
{
	Move* moves = create_moves_array(1024);
	Move* adding;

	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			Point point = {height, width};
			Color currColor = board_point_color(board, point);
			if(currColor != color) continue;

			adding = create_moves_array(40);

			if(!piece_possible_moves(adding, board, info, point)) continue;

			append_moves_array(moves, adding);

			free(adding);
		}
	}
	return moves;
}

void append_moves_array(Move* moves, Move* adding)
{
	int amount = moves_array_amount(moves);
	int addAmount = moves_array_amount(adding);

	for(int index = 0; index < addAmount; index += 1)
	{
		moves[amount + index] = adding[index];
	}
}

int moves_array_amount(Move* moves)
{
	int amount = 0;
	while(points_inside_board(moves[amount].start, moves[amount].stop))
	{
		amount += 1;
	}
	return amount;
}

Move* create_moves_array(int amount)
{
	Move* moves = malloc(sizeof(Move) * amount);
	Point start, stop;
	for(int index = 0; index < amount; index += 1)
	{
		start = (Point) {-1, -1}, stop = (Point) {-1, -1};
		moves[index] = (Move) {start, stop};
	}
	return moves;
}

bool piece_possible_moves(Move* moves, Board board, Info* info, Point start)
{
	Point stop; Move currMove; int amount = 0;
	for(int height = 0; height < B_HEIGHT; height += 1)
	{
		for(int width = 0; width < B_WIDTH; width += 1)
		{
			stop = (Point) {height, width};
			currMove = (Move) {start, stop};

			if(!piece_move_acceptable(board, currMove, info)) continue;
			if(!move_prevent_check(board, currMove, info)) continue;

			moves[amount] = currMove; 
			amount += 1;
		}
	}
	return (amount != 0);
}
