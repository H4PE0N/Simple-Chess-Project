
#include "../Header-Program-Folder/chess-engine-includer.h"

void display_found_move(Move move, int value, time_t time)
{
	char moveString[20]; chess_move_string(moveString, move);

	printf("\033[2K");

	printf("[!] BEST MOVE: [%s] VALUE: [%d] TIME: [%ds]\n", moveString, value, (int) time);
}
