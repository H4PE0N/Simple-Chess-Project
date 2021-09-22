
#include "../Header-Program-Folder/chess-engine-includer.h"

void allocate_board_piece(Board board, Point point, Piece piece)
{
  board[point.height][point.width] = piece;
}

Piece board_point_piece(Board board, Point point)
{
  return board[point.height][point.width];
}

bool extract_castle_points(Point* castleRook, Point* castleKing, Point rook, Point king, Team team)
{
	if(!team_castle_valid(rook, king, team)) return false;

	if(rook.width == 0)
	{
		*castleRook = (Point) {rook.height, king.width - 1};
		*castleKing = (Point) {king.height, king.width - 2};

		return true;
	}

	if(rook.width == (BOARD_WIDTH - 1))
	{
		*castleRook = (Point) {rook.height, king.width + 1};
		*castleKing = (Point) {king.height, king.width + 2};

		return true;
	}

	return false;
}

void copy_board_variable(Board board, Board copying)
{
  Point point;
  Piece piece;

  for(int height = 0; height < BOARD_HEIGHT; height += 1)
  {
    for(int width = 0; width < BOARD_WIDTH; width += 1)
    {
      point = (Point) {height, width};

      piece = board_point_piece(copying, point);

      allocate_board_piece(board, point, piece);
    }
  }
}

Type board_point_type(Board board, Point point)
{
  return board_point_piece(board, point).type;
}

Team board_point_team(Board board, Point point)
{
  return board_point_piece(board, point).team;
}

Point board_piece_point(Board board, Piece piece)
{
  Point point = EMPTY_POINT;
  Point* points = create_point_array(64);

  if(board_piece_points(points, board, piece))
  {
    point = points[0];
  }

  free(points);

  return point;
}

bool board_piece_points(Point* points, Board board, Piece piece)
{
	Piece currentPiece;
  Point currentPoint;

  int index = 0;

	for(int height = 0; height < BOARD_HEIGHT; height = height + 1)
	{
		for(int width = 0; width < BOARD_WIDTH; width = width + 1)
		{
      currentPoint = (Point) {height, width};
			currentPiece = board_point_piece(board, currentPoint);

			if(!board_pieces_equal(piece, currentPiece)) continue;

			points[index] = currentPoint;
			index += 1;
		}
	}
	return (index > 0);
}

void update_castle_value(Castle* castle, Side side, bool value)
{
	if(side == LEFT) castle->queen = value;

  if(side == RIGHT) castle->king = value;
}

void update_castles_value(Castles* castles, Team team, Side side, bool value)
{
	if(team == WHITE) update_castle_value(&castles->white, side, value);

	if(team == BLACK) update_castle_value(&castles->black, side, value);
}

bool board_castles_value(Castles castles, Team team, Side side)
{
  if(team == WHITE) return board_castle_value(castles.white, side);

  if(team == BLACK) return board_castle_value(castles.black, side);

  return false;
}

bool board_castle_value(Castle castle, Side side)
{
  if(side == LEFT) return castle.queen;

  if(side == RIGHT) return castle.king;

  return false;
}

void update_castles_values(Castles* castles, Team team, Castle castle)
{
  if(team == WHITE) castles->white = castle;

  if(team == BLACK) castles->black = castle;
}

void remove_board_piece(Board board, Point point)
{
	board[point.height][point.width] = EMPTY_PIECE;
}

void move_board_piece(Board board, Point start, Point stop)
{
	remove_board_piece(board, stop);
	switch_chess_pieces(board, start, stop);
}

void switch_chess_pieces(Board board, Point first, Point second)
{
	Piece firPiece = board_point_piece(board, first);
	Piece secPiece = board_point_piece(board, second);

	allocate_board_piece(board, first, secPiece);
	allocate_board_piece(board, second, firPiece);
}

Board copy_chess_board(Board board)
{
	Board boardCopy = malloc(sizeof(Piece*) * BOARD_HEIGHT);
	for(int height = 0; height < BOARD_HEIGHT; height = height + 1)
	{
		boardCopy[height] = malloc(sizeof(Piece) * BOARD_WIDTH);
		for(int width = 0; width < BOARD_WIDTH; width = width + 1)
		{
			boardCopy[height][width] = board[height][width];
		}
	}
	return boardCopy;
}

Point passant_remove_point(Point passant, Team team)
{
	int height = passant.height, width = passant.width;

	if(team == WHITE) return (Point) {height - 1, width};
	if(team == BLACK) return (Point) {height + 1, width};

	return EMPTY_POINT;
}

Point pawn_passant_point(Point pawn, Team team)
{
  int height = pawn.height, width = pawn.width;

	if(team == WHITE) return (Point) {height + 1, width};
	if(team == BLACK) return (Point) {height - 1, width};

	return EMPTY_POINT;
}

void free_chess_board(Board board)
{
	for(int height = 0; height < BOARD_HEIGHT; height += 1)
	{
		free(board[height]);
	}
	free(board);
}

Team piece_team_enemy(Team team)
{
  if(!piece_team_exists(team)) return NONE;

  return (team == WHITE) ? BLACK : WHITE;
}
