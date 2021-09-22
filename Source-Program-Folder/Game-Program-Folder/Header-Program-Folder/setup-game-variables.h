
#ifndef SETUP_GAME_VARIABLES_H
#define SETUP_GAME_VARIABLES_H

bool extract_file_line(Board, char[], int);

bool extract_file_value(Piece*, char[], int);

bool allocate_file_values(Board, FILE*);

bool create_chess_board(Board, char[]);

bool setup_game_info(Info*, Board);

Castle extract_castle_values(Board, Team);

Castles extract_castles_values(Board);

bool setup_game_variables(Board, Info*, char[]);

// bool setup_display_variables(Window**, Render**, Surface**, char[]);

#endif
