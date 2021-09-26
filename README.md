
# My Simple Chess Project
## Information about the project
This project is something something that I got challenged to do by my younger brother. He wanted me to create a simple chess program so we could play against each other. After I had written the simple program, that just checks the rules of chess and lets you execute a move on the board, I wanted to create a bot that I could play against. I started creating a bot that compares every first-hand move it could do, and executes the best first-hand move. That was a very stupid bot, so I changed it to a mini-max bot with alpha-beta pruning. That bot was much better and could see up to 5 moves into the future.
## Creating and running games
To play the chess program, you will have to locate yourself in the `Binary-Program-Folder`, where all the binary/executable files is. If the game you want to play does not exists, you will have to compile it. To compile a program, you will type `make` followed by the program you want to compile. Then when the program is compiled, it should come up as an executable file in the same folder. Then you just run that program, and the chess-program will appear.
## How to play the different games
### How to move a chess piece
#### Move piece in graphical interface
When you are playing in the graphical interface, you move a piece by holding down the piece you want to move, and then let go of the piece at that square you want to move it to. The squares you can move a piece to, will be highlighted in a different color. If you want to get a hint of a move that the computer would do for you, you can hit the `H-key` on your keyboard. Then a move will be displayed on the board. If you just want the computer to execute that hint-move directly, you can hit the `G-key` on your computer.

When you want to quit the game in the graphical interface, you can hit the `Q-key` on your computer. Then the screen will indicate that you want to quit, and you will have to confirm the quit in the terminal. When you confirm the quit by typing in `stop`, the game will quit.
#### Move piece in debug console
If you for some reason plays the game in the debug game console, you will make a move by typing the square you want to move, and then the square you want to move to separated by a single space. That could look like `E2 E4`. That move would be **WHITE** moving its **E-Pawn** two squares forward. If you want the computer to give you a hint-move, you can type the word `hint`. If you just want the computer to execute the hint-move directly, you can type `help`. When you want to stop the game, you just have to type `stop` when its your turn to move. Then the program just stops and neither of you will win.
### multi-player-chess:
If you want to play against your friend who is right besides you, this game-mode is perfect. The game starts with **WHITE** doing her move, then the turn goes over to **BLACK** who does her move. The two teams keep moving their pieces that way, until one of the teams win, or it becomes a draw. You can also just quit the game, but then no one wins.
### single-player-chess:
If you don't have any friends like me, this game-mode is perfect for you. The game starts with you playing as **WHITE**. After you do your move, the turn goes over to the computer who is playing as **BLACK**. The reason why you plays as **WHITE** and the computer plays as **BLACK**, is just because that is how it is right now, this will may be optional later. You continue executing your moves, until either you have defeated the bot, or the bot has owned you.
