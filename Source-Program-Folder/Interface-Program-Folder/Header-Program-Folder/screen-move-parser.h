
#ifndef SCREEN_MOVE_PARSER_H
#define SCREEN_MOVE_PARSER_H

extern const Color hintColor;

bool input_screen_move(Move*, Window*, Renderer*, Board, Info);

bool screen_move_parser(Move*, Window*, Renderer*, Board, Info, Event);

bool screen_help_parser(Move*, Window*, Renderer*, Board, Info);

bool screen_hint_parser(Move*, Window*, Renderer*, Board, Info);

bool screen_default_parser(Move*, Window*, Renderer*, Board, Info, Event);

#endif
