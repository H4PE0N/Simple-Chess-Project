
#include "../Header-Program-Folder/global-include-header.h"

void create_board_error(char filename[])
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("CREATE BOARD ERROR");
	CLEAR_LINE; printf("THE FILE NAMED [%s] CUASED THE ERROR!\n", filename);
	display_error_message("THE CHESS BOARD COULD NOT BE CREATED!");
}

void setup_info_error(Board board)
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("SETUP INFO ERROR");
	display_chess_board(board);
	display_error_message("THE BOARD INFO COULD NOT BE EXTRACTED!");
}

void file_pointer_error(char filename[])
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("FILE POINTER ERROR");
	CLEAR_LINE; printf("THE FILE NAMED [%s] CUASED THE ERROR!\n", filename);
	display_error_message("THE FILE COULD NOT BE OPENED [NO FILE]!");
}

void file_values_error(char filename[])
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("FILE VALUES ERROR");
	CLEAR_LINE; printf("THE FILE NAMED [%s] CUASED THE ERROR!\n", filename);
	display_error_message("THE FILE HAD INVALID BOARD VALUES!");
}

void setup_variables_error()
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("SETUP VARIABLES ERROR");
	display_error_message("THE GAME-VARIABLES COULD NOT BE CREATED!");
}

void chess_game_quitted()
{
	CLEAR_LINE; printf("\n"); 
	display_error_header("CHESS GAME QUITTED");
	display_error_message("THE CHESS GAME QUITTED UNEXPECTEDLY!");
}

void display_error_header(char header[])
{
	CLEAR_LINE; printf("[!] === %s === [!]\n", header);
}

void display_error_message(char message[])
{
	CLEAR_LINE; printf("[ERROR]: %s\n", message);
}