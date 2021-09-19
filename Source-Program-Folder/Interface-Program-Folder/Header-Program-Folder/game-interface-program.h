
#ifndef INTERFACE_INPUT_PROGRAM_H
#define INTERFACE_INPUT_PROGRAM_H


// void render_chess_board(Render*);

// bool render_board_piece(Render*, Piece, Point);

// Surface* extract_piece_image(Piece);

// bool extract_piece_filename(char*, Piece);

// bool render_full_board(Render*, Board);

extern const char* blackSymbols[];
extern const char* whiteSymbols[];

#define DIS_LETS "  | A | B | C | D | E | F | G | H |"
#define DIS_ROW "--+---+---+---+---+---+---+---+---+--"

void display_chess_board(Board);

void display_chess_info(Info);

void display_game_round(Board, Info);

void display_chess_result(Board, Team);

void display_board_symbol(int, int, Piece);

#endif
