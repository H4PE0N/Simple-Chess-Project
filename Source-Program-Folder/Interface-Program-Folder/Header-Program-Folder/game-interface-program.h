
#ifndef INTERFACE_INPUT_PROGRAM_H
#define INTERFACE_INPUT_PROGRAM_H

void render_chess_board(Render*);

bool render_board_piece(Render*, Piece, Point);

Surface* extract_piece_image(Piece);

bool extract_piece_filename(char*, Piece);

bool render_full_board(Render*, Board);

#endif
