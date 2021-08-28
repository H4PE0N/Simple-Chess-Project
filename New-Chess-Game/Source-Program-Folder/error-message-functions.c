
#include "../Header-Program-Folder/error-message-functions.h"

void create_board_error(char filename[])
{
	printf("\n[!] === CREATE BOARD ERROR === [!]\n");
	printf("The file namned [%s] cuased the error!\n", filename);
	display_error_message("The chess board could not be created!");
}

void setup_info_error(Board board)
{
	printf("\n[!] === SETUP INFO ERROR === [!]\n");
	display_chess_board(board);
	display_error_message("The board info could not be extracted!");
}

void file_pointer_error(char filename[])
{
	printf("\n[!] === FILE POINTER ERROR === [!]\n");
	printf("The file namned [%s] cuased the error!\n", filename);
	display_error_message("The file could not be opened [no file]!");
}

void file_values_error(char filename[])
{
	printf("\n[!] === FILE VALUES ERROR === [!]\n");
	printf("The file namned [%s] cuased the error!\n", filename);
	display_error_message("The file had invalid board values!");
}

void setup_variables_error()
{
	printf("\n[!] === SETUP VARIABLES ERROR === [!]\n");
	display_error_message("The game-variables could not be created!");
}

void chess_game_quitted()
{
	printf("\n[!] === CHESS GAME QUITTED === [!]\n");
	display_error_message("The chess-game quitted unexpectedly!");
}

void display_error_message(char message[])
{
	printf("[ERROR]: %s\n", message);
}