
#ifndef GAME_HELP_FUNCTIONS_H
#define GAME_HELP_FUNCTIONS_H

bool display_console_result(Board, Team);

bool console_computer_handler(Board, Info*);

bool console_user_handler(Board, Info*);

bool screen_user_handler(Board, Info*, Window*, Renderer*);

bool screen_computer_handler(Board, Info*, Window*, Renderer*);

bool render_screen_result(Renderer*, Board, Team);

#endif
