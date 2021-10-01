
#ifndef CONSOLE_MOVE_PARSER_H
#define CONSOLE_MOVE_PARSER_H

bool input_console_move(Move*, Board, Info);

bool input_string_move(char*);

bool parse_move_string(Move*, Board, Info, char[]);

bool default_move_parser(Move*, Board, Info, char[]);

bool help_move_parser(Move*, Board, Info);

bool hint_move_parser(Move*, Board, Info);

bool parse_board_point(Point*, char[]);

#endif
