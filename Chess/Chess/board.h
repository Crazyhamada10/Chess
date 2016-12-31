#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

FILE * pointergenral;
char chess[8][8];
char input[6];
int counter;
char dead[36];
int w, flag1, check, flag2, save_flag;
int unrdo_counter;

void Starting();
void new_game();
void game();
void how_to_play ();
void first_board_structure();
void Printing_board();
void change_board_structure();
void change_board_structure_for_load (char inputafterload[11]);
void checkmate_board ();
void genralsave ();
void save();
void load_outside();
void load_inside();
void first_board_structure_undo();
void undo();
void redo();
int test();
void colour_it (char color[11]);
void delay();
void load_logo();

#endif // BOARD_H_INCLUDED
