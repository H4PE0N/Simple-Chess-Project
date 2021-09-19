
#ifndef MOVE_PARSER_FUNCTIONS_H
#define MOVE_PARSER_FUNCTIONS_H

bool input_current_move(char*);

bool input_string_variable(char*);

bool parse_chess_move(Move*, Board, Info, char[]);

bool default_move_parser(Move*, Board, Info, char[]);

bool help_move_parser(Move*, Board, Info, char[]);

bool hint_move_parser(Move*, Board, Info, char[]);

bool save_move_parser(Move*, Board, Info, char[]);

bool parse_chess_position(Point*, char[]);

void extract_file_name(char*, char*[], int);

#endif
