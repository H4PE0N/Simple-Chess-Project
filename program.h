
#ifndef PROGRAM
#define PROGRAM

extern const char white_symbols[];
extern const char black_symbols[];

extern const char letters[];
extern const char numbers[];

bool extract_start_board(Board, char[]);

void parse_starting_file(Board, FILE*);

Board create_chess_board(void);

void display_chess_board(Board);

void display_chess_values(Board);

bool parse_chess_position(Point*, char[]);

bool board_piece_empty(Board, Point);

bool point_inside_bounds(int, int);

bool game_still_running(Board, Info);

bool create_game_info(Info*, Board);

bool find_board_piece(Point*, Board, Type, Color);

bool parse_chess_move(Move*, char[]);

bool input_string_move(char*);

bool allocate_board_piece(Board, Point, Type, Color);

#endif