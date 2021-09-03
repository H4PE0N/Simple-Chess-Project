
#include "../Header-Program-Folder/chess-bot-algorithms.h"

// ===== HAMPUS ALGORITHM ======================

// Uno-Reverse:

// setsCheck	takeEnemy	!getsTaken	exposed
// !setsCheck	takeEnemy	!getsTaken	exposed

// You are dumb!:

// setsCheck	takeEnemy	!getsTaken	!exposed
// !setsCheck	takeEnemy	!getsTaken	!exposed

// Peek-a-boo!:

// setsCheck	!takeEnemy	!getsTaken	exposed
// !setsCheck	!takeEnemy	!getsTaken	exposed

// Meaningless:

// setsCheck	!takeEnemy	!getsTaken	!exposed
// !setsCheck	!takeEnemy	!getsTaken	!exposed

// ---------------------------------------------

// if(getsTaken && takeEnemy): and...
// if(current.type <= current.enemy && (current.enemy > bestMove.enemy || current.type < bestMove.enemy)):

// Good trades: (highest enemy || lower type && type <= enemy)

// setsCheck	takeEnemy	getsTaken	exposed
// !setsCheck	takeEnemy	getsTaken	exposed

// Desperete Trades: (highest enemy || lower type && type <= enemy)

// setsCheck	takeEnemy	getsTaken	!exposed
// !setsCheck	takeEnemy	getsTaken	!exposed

// ---------------------------------------------

// Desperete suicide:

// setsCheck	!takeEnemy	getsTaken	exposed
// !setsCheck	!takeEnemy	getsTaken	exposed

// Suicide:

// setsCheck	!takeEnemy	getsTaken	!exposed
// !setsCheck	!takeEnemy	getsTaken	!exposed

// 1. !GetsTaken
// 2. Exposed
// 3. TakeEnemy
// 4. SetCheck

// if(!current.getsTaken && bestMove.getsTaken) return true;
// if(current.getsTaken && !bestMove.getsTaken) return false;

// Either	(current.getsTaken)
// Or     	(!current.getsTaken)

// if(current.takeEnemy && !bestMove.takeEnemy) return true;
// if(!current.takeEnemy && bestMove.takeEnemy) return false;

// Either 	(!current.getsTaken && current.takeEnemy)
// Or 		(!current.getsTaken && !current.takeEnemy)

// Either 	(current.getsTaken && current.takeEnemy)
// Or 		(current.getsTaken && !current.takeEnemy)

// bool cGoodTrade = current.type <= current.enemy;
// bool bGoodTrade = bestMove.type <= bestMove.enemy;

// if(current.takeEnemy && cGoodTrade && !bGoodTrade) return true;
// if(current.takeEnemy && !cGoodTrade && bGoodTrade) return false;

// if(current.exposed && !bestMove.exposed) return true;
// if(!current.exposed && bestMove.exposed) return false;

// Either	(!current.getsTaken && current.takeEnemy && current.exposed)
// Or		(!current.getsTaken && current.takeEnemy && !current.exposed)

// Either	(!current.getsTaken && !current.takeEnemy && current.exposed)
// Or 		(!current.getsTaken && !current.takeEnemy && !current.exposed)

// Either	(current.getsTaken && current.takeEnemy && current.exposed)
// Or		(current.getsTaken && current.takeEnemy && !current.exposed)

// Either	(current.getsTaken && !current.takeEnemy && current.exposed)
// Or 		(current.getsTaken && !current.takeEnemy && !current.exposed)

// if(current.setsCheck && !bestMove.setsCheck) return true;
// if(!current.setsCheck && bestMove.setsCheck) return false;

// if(current.enemy > bestMove.enemy) return true;

// return false;

bool default_bot_algorithm(Board board, MoveInfo bestMove, MoveInfo current)
{
	Color color = board_point_color(board, current.move.start);

	// If one move, makes check mate, the bot will take that move
	if(current.checkMate) return true;
	if(bestMove.checkMate) return false;

	// It prioritises if the piece is exposed to begin with
	if(current.type != PAWN && current.exposed && !current.getsTaken && !bestMove.exposed) return true;
	if(!current.exposed && bestMove.exposed) return false;

	//================================================================
	int currHeight = current.move.start.height;
	int bestHeight = bestMove.move.start.height;

	int currHeightLeft = (color == WHITE) ? currHeight : (7 - currHeight);
	int bestHeightLeft = (color == WHITE) ? bestHeight : (7 - bestHeight);

	int pawnRushLeft= 3;

	bool currPawnRush = (current.type == PAWN) && (currHeightLeft <= pawnRushLeft);
	bool bestPawnRush = (bestMove.type == PAWN) && (bestHeightLeft <= pawnRushLeft);

	if(currPawnRush && !bestPawnRush) return true;
	if(!currPawnRush && bestPawnRush) return false;
	//================================================================

	int cTradeValue = current.takeEnemy ? (current.type - current.enemy) : 8; 
	int bTradeValue = bestMove.takeEnemy ? (bestMove.type - bestMove.enemy) : 8;

	// The lowest value is the best trade.
	bool betterTrade = (cTradeValue < bTradeValue);

	if(current.type == QUEEN && current.getsTaken && current.enemy != QUEEN) return false;

	// If the piece is safe after it has taken an enemy, 
	// the only thing that matters, is the enemy rank
	if(!current.getsTaken && betterTrade) return true;

	// If the piece can be taken after it has taken an enemy,
	// The trade must be with a higher or equal piece
	if(current.getsTaken && cTradeValue <= 0 && betterTrade) return true;

	// If the trade value of the best move is better, then it remains that way
	if(bTradeValue < cTradeValue) return false;
	
	// It prioritises if the piece dont get taken after move
	if(!current.getsTaken && bestMove.getsTaken) return true;
	if(current.getsTaken && !bestMove.getsTaken) return false;

	// It prioritises if the move makes check to the other team
	if(current.setsCheck && !bestMove.setsCheck) return true;
	if(!current.setsCheck && bestMove.setsCheck) return false;

	// The greater enemy that it gets killed, the better.
	if(current.enemy > bestMove.enemy) return true;
	//if(current.type < bestMove.type) return true;

	return false;
}