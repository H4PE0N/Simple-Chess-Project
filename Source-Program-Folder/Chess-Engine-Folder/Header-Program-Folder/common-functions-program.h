
#ifndef COMMON_FUNCTIONS_PROGRAM_H
#define COMMON_FUNCTIONS_PROGRAM_H

extern const char letters[];
extern const char numbers[];

bool chess_team_string(char*, Team);

int point_array_amount(Point[]);

Point* create_point_array(int);

int string_letter_index(char[], int, char);

char convert_char_upper(char);

void convert_string_upper(char*, int);

bool board_point_string(char*, Point);

bool chess_move_string(char*, Move);

int moves_array_amount(Move[]);

void append_moves_array(Move*, Move[]);

void clear_moves_array(Move*);

void switch_array_moves(Move*, int, int);

Move* create_moves_array(int);

#endif
