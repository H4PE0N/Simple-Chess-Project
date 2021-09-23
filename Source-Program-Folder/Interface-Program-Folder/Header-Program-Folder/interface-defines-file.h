
#ifndef INTERFACE_DEFINES_FILE_H
#define INTERFACE_DEFINES_FILE_H

extern const char blackSymbols[];
extern const char whiteSymbols[];

extern const char boardNumbers[];
extern const char boardLetters[];

#define PIECE_FOLDER "../Source-Program-Folder/Interface-Program-Folder/Piece-Image-Folder"

#define SAVE_FILE	"../Source-Program-Folder/Game-Program-Folder/Data-Program-Folder/saved-chess-board.txt"
#define STD_FILE	"../Source-Program-Folder/Game-Program-Folder/Data-Program-Folder/default-chess-board.txt"

#define SCREEN_HEIGHT	800
#define SCREEN_WIDTH	800

#define SQUARE_HEIGHT (SCREEN_HEIGHT / BOARD_HEIGHT)
#define SQUARE_WIDTH (SCREEN_WIDTH / BOARD_WIDTH)

#define CLEAR_LINE printf("\033[2K")

#define MOVE_UP_LINES(lines) printf("\033[%dA", lines)

#define MOVE_UP_BOARD MOVE_UP_LINES(19)

#define MOVE_UP_INFO MOVE_UP_LINES(3)

#define MOVE_UP_INPUT MOVE_UP_LINES(1)

#endif
