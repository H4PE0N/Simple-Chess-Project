
#ifndef ENGINE_HELP_FUNCTIONS_H
#define ENGINE_HELP_FUNCTIONS_H

int point_array_amount(Point[]);

Point* create_point_array(int);

int moves_array_amount(Move[]);

void append_moves_array(Move*, Move[]);

void clear_moves_array(Move*);

void switch_array_moves(Move*, int, int);

Move* create_moves_array(int);

#endif
