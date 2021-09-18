
#ifndef INTERFACE_INPUT_PROGRAM_H
#define INTERFACE_INPUT_PROGRAM_H


// void render_chess_board(Render*);

// bool render_board_piece(Render*, Piece, Point);

// Surface* extract_piece_image(Piece);

// bool extract_piece_filename(char*, Piece);

// bool render_full_board(Render*, Board);

#define SAVE_FILE	"../Source-Program-Folder/Game-Program-Folder/Data-Program-Folder/saved-chess-board.txt"
#define STD_FILE	"../Source-Program-Folder/Game-Program-Folder/Data-Program-Folder/default-chess-board.txt"
#define PIECE_FOLDER "../Source-Program-Folder/Game-Program-Folder/Piece-Image-Folder"

#define SCREEN_HEIGHT	800
#define SCREEN_WIDTH	800

#define SQUARE_HEIGHT SCREEN_HEIGHT / B_HEIGHT
#define SQUARE_WIDTH SCREEN_WIDTH / B_WIDTH

void display_chess_board(Board);

void display_chess_info(Info);

bool input_current_move(char*);

bool input_string_variable(char*);

bool parse_chess_move(Move*, Board, Info, char[]);

bool default_move_parser(Move*, Board, Info, char[]);

bool help_move_parser(Move*, Board, Info, char[]);

bool hint_move_parser(Move*, Board, Info, char[]);

bool save_move_parser(Move*, Board, Info, char[]);

bool parse_chess_position(Point*, char[]);

void display_game_round(Board, Info);

int string_letter_index(char[], int, char);

void display_chess_result(Board, Team);

void display_board_symbol(int, int, Piece);

void extract_file_name(char*, char*[], int);

#endif
