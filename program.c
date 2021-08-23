
#include "header.h"

const char white_symbols[] = {'.', 'p', 'r', 'n', 'b', 'q', 'k'};
const char black_symbols[] = {'.', 'P', 'R', 'N', 'B', 'Q', 'K'};

const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
const char numbers[] = {'1', '2', '3', '4', '5', '6', '7', '8'};

int main(int argAmount, char* arguments[])
{
	char* filename;
	if(argAmount > 1)
	{
		filename = arguments[1];
	}
	else
	{
		filename = "standard-board.txt";
	}

	Board board = create_chess_board();
	if(!extract_start_board(board, filename))
	{
		printf("Could not load board!\n");
		free(board); return false;
	}

	Info info;
	if(!create_game_info(&info, board))
	{
		printf("Could not create info!\n");
		free(board); return false;
	}

	while(game_still_running(board, info))
	{
		display_chess_board(board);
		printf("Current \t: (%s)\n", (info.current == WHITE) ? "WHITE" : "BLACK");
		printf("WhiteRKS\t: (%d-%d)\n", info.whiteRKS.left, info.whiteRKS.right);
		printf("BlackRKS\t: (%d-%d)\n", info.blackRKS.left, info.blackRKS.right);
		printf("TURNS   \t: (%d)\n", info.turns);

		char string[20];
		
		if(!input_string_move(string)) break;

		if(!strcmp(string, "stop")) break;

		printf("Move: [%s]\n", string);

		Move move;

		if(!parse_chess_move(&move, string)) continue;

		if(move_chess_piece(board, move, &info))
		{
			info.current = (info.current == WHITE) ? BLACK : WHITE;
			info.turns += 1;
		}
		else
		{
			continue;
		}
	}
	
	display_chess_board(board);

	display_chess_values(board);

	free(board);
	return false;
}

bool input_string_move(char* string)
{
	printf("INPUT POSITION: ");
	if(!scanf("%[^\n]%*c", string)) return false;

	if(strlen(string) == 0) return false;

	return true;
}

bool parse_chess_move(Move* move, char string[])
{
	char seperator[] = " ";
	char* start = strtok(string, seperator);
	char* stop = strtok(NULL, seperator);

	if(start == NULL || stop == NULL) return false;

	if(!parse_chess_position(&move->start, start)) return false;
	if(!parse_chess_position(&move->stop, stop)) return false;

	return true;
}

bool create_game_info(Info* info, Board board)
{
	info->current = WHITE;
	info->whiteRKS = (RKSwitch) {true, true};
	info->blackRKS = (RKSwitch) {true, true};

	if(!find_board_piece(&info->bKing, board, KING, BLACK)) return false;
	if(!find_board_piece(&info->wKing, board, KING, WHITE)) return false;

	info->turns = 0;
	return true;
}

bool find_board_piece(Point* point, Board board, Type type, Color color)
{
	Piece finding = {type, color};
	for(int height = 0; height < 8; height = height + 1)
	{
		for(int width = 0; width < 8; width = width + 1)
		{
			Piece current = board[height][width];

			if(board_piece_equal(finding, current))
			{
				point->height = height;
				point->width = width;
				return true;
			}
		}
	}
	return false;
}

bool game_still_running(Board board, Info info)
{
	for(int round = 0; round < 2; round = round + 1)
	{
		Color color = (round == 0) ? WHITE : BLACK;
		Point point = (color == WHITE) ? info.wKing : info.bKing;
		
		if(check_mate_situation(board, point, color)) return false;
		if(check_draw_situation(board, point, color)) return false;
	}

	return true;
}

bool allocate_board_piece(Board board, Point point, Type type, Color color)
{
	if(!point_inside_bounds(point.height, point.width)) return false;

	board[point.height][point.width].type = type;
	board[point.height][point.width].color = color;

	return true;
}

bool point_inside_bounds(int height, int width)
{
	return (height >= 0 && height < 8) && (width >= 0 && width < 8);
}

bool board_piece_empty(Board board, Point point)
{
	return (board[point.height][point.width].type == EMPTY);
}

bool parse_chess_position(Point* point, char string[])
{
	if(strlen(string) < 2 || strlen(string) > 2) return false;

	int width = -1;

	for(int index = 0; index < 8; index = index + 1)
	{
		char letter = string[0];
		if(letter == letters[index]) 
		{
			width = index; 
			break;
		}
	}

	if(width == -1) return false;

	char number = string[1];

	if(number < '1' || number > '8') return false;

	int height = number - '1';

	point->height = height;
	point->width = width;

	return true;
}

void display_chess_board(Board board)
{
	printf("  A B C D E F G H\n");
	for(int height = 0; height < 8; height = height + 1)
	{
		printf("%d ", height + 1);
		for(int width = 0; width < 8; width = width + 1)
		{
			Type type = board[height][width].type;
			Color color = board[height][width].color;

			char symbol = (color == WHITE) ? white_symbols[type] : black_symbols[type];

			printf("%c ", symbol);
		}
		printf("\n");
	}
}

void display_chess_values(Board board)
{
	for(int height = 0; height < 8; height = height + 1)
	{
		for(int width = 0; width < 8; width = width + 1)
		{
			Type type = board[height][width].type;
			Color color = board[height][width].color;

			printf("%d%d", type, color);
		}
		printf("\n");
	}
}

Board create_chess_board(void)
{
	Board board = malloc(sizeof(Piece*) * 8);
	for(int index = 0; index < 8; index = index + 1)
	{
		board[index] = malloc(sizeof(Piece) * 8);
	}
	return board;
}

void parse_starting_file(Board board, FILE* filePoint)
{
	char lineBuffer[32];
	int height = 0;

	while(fgets(lineBuffer, 32, filePoint) != NULL)
	{
		for(int index = 0; index < 8; index += 1)
		{
			Type type = lineBuffer[(index * 2) + 0] - '0';
			Color color = lineBuffer[(index * 2) + 1] - '0';

			board[height][index].type = type;
			board[height][index].color = color;
		}
		height = height + 1;
	}
}

bool extract_start_board(Board board, char filename[])
{
	FILE* filePoint = fopen(filename, "r");
	if(filePoint == NULL)
	{
		fclose(filePoint);
		return false;
	}

	parse_starting_file(board, filePoint);

	fclose(filePoint); 
	return true;
}

