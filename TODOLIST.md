
change the board design

"int" and "char" is uninitialized values? By some reason

implement B_LEFT and B_RIGHT

pointer to those variables that is going to get changed (array int* -> int** );

change "move_board_piece" to "execute_..."


"update kings point", move that somewhere else

make good controls in functions (out-of-bounds ... etc)


make every function more efficient
- instead of 8x8 brute force; make it efficient


Create Check-Indicator

Old:
Checked 2863 moves out of 13733! Pruned 536 Ones 13134
total heap usage: 5,727,593 allocs, 5,727,593 frees, 382,402,360 bytes allocated

New:
Checked 2930 moves out of 13733! Pruned 533 Ones 13134
total heap usage: 5,606,262 allocs, 5,606,262 frees, 375,351,416 bytes allocated
