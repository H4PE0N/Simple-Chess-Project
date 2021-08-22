
#ifndef PROGRAM
#define PROGRAM

#define FILENAME "starting.txt"

extern const char white_symbols[];
extern const char black_symbols[];

extern const char letters[];
extern const char numbers[];

bool extract_start_board(Board, char[]);

void parse_starting_file(Board, FILE*);

Board create_chess_board(void);

void display_chess_board(Board);

bool parse_chess_position(Point*, char[]);

bool board_piece_empty(Board, Point);

bool point_inside_bounds(int, int);

bool game_still_running(Board, Info);

Info create_game_info(void);

bool parse_chess_move(Move*, char[]);

bool input_string_move(char*);

#endif