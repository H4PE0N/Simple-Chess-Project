
#ifndef GAME_HELP_FUNCTIONS_H
#define GAME_HELP_FUNCTIONS_H

bool display_game_result(Board, Team);

bool console_computer_handler(Board, Info*);

bool console_user_handler(Board, Info*);

bool screen_user_handler(Board, Info*, Window*, Renderer*);

bool screen_computer_handler(Board, Info*, Window*, Renderer*);

#endif
