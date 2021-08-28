
#include "../Header-Program-Folder/chess-bot-algorithms.h"

// setsCheck	takeEnemy	!getsTaken	exposed
// !setsCheck	takeEnemy	!getsTaken	exposed
// setsCheck	!takeEnemy	!getsTaken	exposed
// !setsCheck	!takeEnemy	!getsTaken	exposed
// setsCheck	takeEnemy	getsTaken	exposed
// !setsCheck	takeEnemy	getsTaken	exposed
// setsCheck	!takeEnemy	getsTaken	exposed
// !setsCheck	!takeEnemy	getsTaken	exposed

// setsCheck	takeEnemy	!getsTaken	!exposed
// !setsCheck	takeEnemy	!getsTaken	!exposed
// setsCheck	!takeEnemy	!getsTaken	!exposed
// !setsCheck	!takeEnemy	!getsTaken	!exposed
// setsCheck	takeEnemy	getsTaken	!exposed
// !setsCheck	takeEnemy	getsTaken	!exposed
// setsCheck	!takeEnemy	getsTaken	!exposed
// !setsCheck	!takeEnemy	getsTaken	!exposed

// 1. Exposed
// 2. GetsTaken
// 3. TakeEnemy
// 4. SetsCheck

// ==============================================

// Vary good moves:
// setsCheck	takeEnemy	!getsTaken	exposed
// setsCheck	takeEnemy	!getsTaken	!exposed
// !setsCheck	takeEnemy	!getsTaken	exposed
// !setsCheck	takeEnemy	!getsTaken	!exposed

// Checking moves:
// setsCheck	!takeEnemy	!getsTaken	exposed
// setsCheck	!takeEnemy	!getsTaken	!exposed

// Fleeing move:
// !setsCheck	!takeEnemy	!getsTaken	exposed

// Just meaningless move:
// !setsCheck	!takeEnemy	!getsTaken	!exposed

// Trades:
// setsCheck	takeEnemy	getsTaken	exposed
// !setsCheck	takeEnemy	getsTaken	exposed
// setsCheck	takeEnemy	getsTaken	!exposed
// !setsCheck	takeEnemy	getsTaken	!exposed

// desperate bad move:
// setsCheck	!takeEnemy	getsTaken	exposed
// !setsCheck	!takeEnemy	getsTaken	exposed

// Suicide move:
// setsCheck	!takeEnemy	getsTaken	!exposed
// !setsCheck	!takeEnemy	getsTaken	!exposed

// 1. GetsTaken
// 2. TakeEnemy
// 3. SetsCheck
// 4. Exposed

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

// ===== ELIAS ALGORITHM ======================

// setsCheck	takeEnemy	!getsTaken	exposed
// !setsCheck	takeEnemy	!getsTaken	exposed
// setsCheck	!takeEnemy	!getsTaken	exposed
// !setsCheck	!takeEnemy	!getsTaken	exposed
// setsCheck	takeEnemy	!getsTaken	!exposed
// !setsCheck	takeEnemy	!getsTaken	!exposed
// setsCheck	!takeEnemy	!getsTaken	!exposed
// !setsCheck	!takeEnemy	!getsTaken	!exposed
// setsCheck	takeEnemy	getsTaken	exposed
// !setsCheck	takeEnemy	getsTaken	exposed
// setsCheck	!takeEnemy	getsTaken	exposed
// !setsCheck	!takeEnemy	getsTaken	exposed
// setsCheck	takeEnemy	getsTaken	!exposed
// !setsCheck	takeEnemy	getsTaken	!exposed
// setsCheck	!takeEnemy	getsTaken	!exposed
// !setsCheck	!takeEnemy	getsTaken	!exposed

// 1. 
// 2.
// 3. 
// 4. 

// ====== ANDREAS ALGORITHM =========================

// setsCheck	takeEnemy	!getsTaken	exposed
// !setsCheck	takeEnemy	!getsTaken	exposed
// setsCheck	takeEnemy	!getsTaken	!exposed
// !setsCheck	takeEnemy	!getsTaken	!exposed
// setsCheck	takeEnemy	getsTaken	exposed
// !setsCheck	takeEnemy	getsTaken	exposed
// setsCheck	takeEnemy	getsTaken	!exposed
// !setsCheck	takeEnemy	getsTaken	!exposed
// setsCheck	!takeEnemy	!getsTaken	exposed
// !setsCheck	!takeEnemy	!getsTaken	exposed
// setsCheck	!takeEnemy	!getsTaken	!exposed
// !setsCheck	!takeEnemy	!getsTaken	!exposed
// setsCheck	!takeEnemy	getsTaken	exposed
// !setsCheck	!takeEnemy	getsTaken	exposed
// setsCheck	!takeEnemy	getsTaken	!exposed
// !setsCheck	!takeEnemy	getsTaken	!exposed

// 1. 
// 2.
// 3. 
// 4.

bool default_bot_algorithm(Board board, MoveInfo bestMove, MoveInfo current)
{
	// If one move, makes check mate, the bot will take that move
	if(bestMove.checkMate) return false;
	if(current.checkMate) return true;

	// In first hand, the bot wants to make check to you
	if(!current.setsCheck && bestMove.setsCheck) return false;
	if(current.setsCheck && !bestMove.setsCheck) return true;

	// The bot will choose a move that are exposed before a move that isn't exposed
	if(!current.exposed && bestMove.exposed) return false;
	if(current.exposed && !bestMove.exposed) return true;

	// This makes that the piece should not get taken
	// If you want the bot to go "suicide mode" edit this out
	if(current.getsTaken && !bestMove.getsTaken) return false;
	if(!current.getsTaken && bestMove.getsTaken) return true;
	
	// This makes the enemy want to take the move that takes out an enemy
	if(!current.takeEnemy && bestMove.takeEnemy) return false;
	if(current.takeEnemy && !bestMove.takeEnemy) return true;

	// The greater enemy it can take, the better:
	if(current.enemy < bestMove.enemy) return false;
	if(current.enemy > bestMove.enemy) return true;

	return false;
}

bool defensive_bot_algorithm(Board board, MoveInfo bestMove, MoveInfo current)
{
	// If one move, makes check mate, the bot will take that move
	if(current.checkMate) return true;
	if(bestMove.checkMate) return false;

	// It prioritises if the piece is exposed to begin with
	if(current.type != PAWN && current.exposed && !current.getsTaken && !bestMove.exposed) return true;
	if(!current.exposed && bestMove.exposed) return false;

	// It prioritises if the piece dont get taken after move
	if(!current.getsTaken && bestMove.getsTaken) return true;
	if(current.getsTaken && !bestMove.getsTaken) return false;

	// It prioritises if the piece take another piece
	if(current.takeEnemy && !bestMove.takeEnemy) return true;
	if(!current.takeEnemy && bestMove.takeEnemy) return false;

	// It prioritises if the trade is better
	bool cGoodTrade = current.type <= current.enemy;
	bool bGoodTrade = bestMove.type <= bestMove.enemy;

	if(current.takeEnemy && cGoodTrade && !bGoodTrade) return true;
	if(current.takeEnemy && !cGoodTrade && bGoodTrade) return false;

	// It prioritises if the move makes check to the other team
	if(current.setsCheck && !bestMove.setsCheck) return true;
	if(!current.setsCheck && bestMove.setsCheck) return false;

	// The greater enemy that it gets killed, the better.
	if(current.enemy > bestMove.enemy) return true;

	return false;
}

bool offensive_bot_algorithm(Board board, MoveInfo bestMove, MoveInfo current)
{
	// If one move, makes check mate, the bot will take that move
	if(current.checkMate) return true;
	if(bestMove.checkMate) return false;

	// It prioritises if the piece is exposed to begin with
	if(current.type != PAWN && current.exposed && !current.getsTaken && !bestMove.exposed) return true;
	if(!current.exposed && bestMove.exposed) return false;

	// It prioritises if the trade is better
	bool cGoodTrade = (current.enemy <= current.type);
	bool bGoodTrade = (bestMove.enemy <= bestMove.type);

	int cTradeValue = (current.enemy - current.type);
	int bTradeValue = (bestMove.enemy - bestMove.type);
	bool betterTrade = (cTradeValue > bTradeValue);

	if(current.takeEnemy && !current.getsTaken && betterTrade) return true;
	if(current.takeEnemy && current.getsTaken && cGoodTrade && betterTrade) return true;
	if(current.takeEnemy && bGoodTrade && bTradeValue > cTradeValue) return false;

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

bool smart_bot_algorithm1(Board board, MoveInfo bestMove, MoveInfo current)
{
	// If one move, makes check mate, the bot will take that move
	if(current.checkMate) return true;
	if(bestMove.checkMate) return false;

	// It prioritises if the piece is exposed to begin with
	if(current.type != PAWN && current.exposed && !current.getsTaken && !bestMove.exposed) return true;
	if(!current.exposed && bestMove.exposed) return false;

	
	int cTradeValue = current.takeEnemy ? (current.type - current.enemy) : 8; 
	int bTradeValue = bestMove.takeEnemy ? (bestMove.type - bestMove.enemy) : 8;

	// The lowest value is the best trade.
	bool betterTrade = (cTradeValue < bTradeValue);

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