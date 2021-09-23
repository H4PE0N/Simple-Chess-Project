
#ifndef SCREEN_HELP_FUNCTIONS_H
#define SCREEN_HELP_FUNCTIONS_H

extern const char* typeStrings[];
extern const char* teamStrings[];

bool extract_piece_image(Surface**, Piece);

bool extract_piece_filename(char*, Piece);

void free_screen_variables(Window*, Renderer*, Surface*);

bool create_screen_window(Window**, char[]);

bool create_window_surface(Surface**, Window*);

bool create_surface_renderer(Renderer**, Surface*);

bool create_surface_texture(Texture**, Renderer*, Surface*);

#endif
