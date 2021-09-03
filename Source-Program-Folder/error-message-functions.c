
#include "../Header-Program-Folder/error-message-functions.h"

void create_board_error(char filename[])
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("CREATE BOARD ERROR");
	printf("The file namned [%s] cuased the error!\n", filename);
	display_error_message("The chess board could not be created!");
}

void setup_info_error(Board board)
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("SETUP INFO ERROR");
	display_chess_board(board);
	display_error_message("The board info could not be extracted!");
}

void file_pointer_error(char filename[])
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("FILE POINTER ERROR");
	printf("The file namned [%s] cuased the error!\n", filename);
	display_error_message("The file could not be opened [no file]!");
}

void file_values_error(char filename[])
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("FILE VALUES ERROR");
	printf("The file namned [%s] cuased the error!\n", filename);
	display_error_message("The file had invalid board values!");
}

void setup_variables_error()
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("SETUP VARIABLES ERROR");
	display_error_message("The game-variables could not be created!");
}

void chess_game_quitted()
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("CHESS GAME QUITTED");
	display_error_message("The chess-game quitted unexpectedly!");
}

void display_error_header(char header[])
{
	CLEAR_LINE; printf("[!] === %s === [!]\n", header);
}

void display_error_message(char message[])
{
	CLEAR_LINE; printf("[ERROR]: %s\n", message);
}