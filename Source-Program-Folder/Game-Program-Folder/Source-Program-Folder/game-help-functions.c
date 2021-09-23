
#include "../Header-Program-Folder/game-files-includer.h"

bool display_game_result(Board board, Team winner)
{
	if(!display_chess_board(board)) return false;

	if(!piece_team_exists(winner))
	{
		char teamString[20] = "\0";
		if(!chess_team_string(teamString, winner)) return false;

		CLEAR_LINE; printf("[!] THE WINNER IS [%s]!\n", teamString);
	}
	else
	{
		CLEAR_LINE; printf("[!] THE GAME ENDED WITH A DRAW!\n");
	}
	return true;
}
