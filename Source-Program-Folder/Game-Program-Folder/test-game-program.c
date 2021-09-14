
#include "../Header-Program-Folder/global-include-header.h"

int main(int argAmount, char* arguments[])
{
	srand(time(NULL));

	char filename[200]; extract_file_name(filename, arguments, argAmount);

	Board board; Info info;

	if(!setup_game_variables(&board, &info, filename))
	{
		setup_variables_error();

		free_chess_board(board);

		return false;
	}

	test_game_program(board, info);

	free_chess_board(board);

	return false;
}

void test_game_program(Board board, Info info)
{
	display_game_round(board, info);
}