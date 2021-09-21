
#include "../Header-Program-Folder/chess-engine-includer.h"

bool move_inside_board(Move move)
{
  bool startValid = point_inside_board(move.start);
  bool stopValid = point_inside_board(move.stop);

  return (startValid && stopValid);
}

bool number_inside_bounds(int number, int minimum, int maximum)
{
  return ( (number >= minimum) && (number <= maximum) );
}

bool point_inside_board(Point point)
{
  bool heightValid = number_inside_bounds(point.height, 0, BOARD_HEIGHT - 1);
  bool widthValid = number_inside_bounds(point.width, 0, BOARD_WIDTH - 1);

  return (heightValid && widthValid);
}

bool board_points_equal(Point first, Point second)
{
  bool heightEqual = (first.height == second.height);
  bool widthEqual = (first.width == second.width);

  return (heightEqual && widthEqual);
}

bool points_not_enemy(Board board, Point first, Point second)
{
  Team firstTeam = board_point_team(board, first);
  Team secondTeam = board_point_team(board, second);

  bool firstExists = piece_team_exists(firstTeam);
  bool secondExists = piece_team_exists(secondTeam);

  return (!firstExists || !secondExists || firstTeam == secondTeam);
}

bool board_pieces_equal(Piece first, Piece second)
{
  bool typeEqual = (first.type == second.type);
  bool teamEqual = (first.team == second.team);

  return (typeEqual && teamEqual);
}

bool pawn_becomes_queen(Point point, Team team)
{
	// If the point is not inside the board:
	if(!point_inside_board(point)) return false;

	if(!piece_team_exists(team)) return false;

	if(team == WHITE && point.height == 0) return true;
	if(team == BLACK && point.height == (BOARD_HEIGHT - 1)) return true;

	return false;
}

bool board_points_enemy(Board board, Point first, Point second)
{
  Team firstTeam = board_point_team(board, first);
  Team secondTeam = board_point_team(board, second);

  return board_pieces_enemy(firstTeam, secondTeam);
}

bool board_points_team(Board board, Point first, Point second)
{
  Team firstTeam = board_point_team(board, first);
  Team secondTeam = board_point_team(board, second);

  return board_pieces_team(firstTeam, secondTeam);
}

bool board_pieces_team(Team first, Team second)
{
  bool teamExists = piece_team_exists(first);

  return teamExists && (first == second);
}

bool board_pieces_enemy(Team first, Team second)
{
  bool teamExists = piece_team_exists(first);

  return teamExists && (first != second);
}

bool board_point_empty(Board board, Point point)
{
  Piece piece = board_point_piece(board, point);

  return board_piece_empty(piece);
}

bool board_piece_empty(Piece piece)
{
  bool teamEmpty = !piece_team_exists(piece.team);
  bool typeEmpty = !piece_type_exists(piece.type);

  return (teamEmpty || typeEmpty);
}

bool piece_team_exists(Team team)
{
  return (team == WHITE || team == BLACK);
}

bool piece_type_exists(Type type)
{
  for(Type current = PAWN; current <= KING; current += 1)
  {
    if(current == type) return true;
  }
  return false;
}

bool points_inside_board(Point first, Point second)
{
  bool firstValid = point_inside_board(first);
  bool secondValid = point_inside_board(second);

  return (firstValid && secondValid);
}
