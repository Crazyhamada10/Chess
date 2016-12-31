#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED

int knights(int x,int y);
int bishops(int x,int y,int y1,int x1);
int rooks(int x,int y,int y1,int x1);
int queen(int x,int y,int y1,int x1);
int king(int x,int y);
int pawns(int x,int y,int x2,int y2);
int check_myself ();
int checkmate ();
int probability_of_movement ();
int change_board_structure_for_checkmate(int x1,int y1,int x2,int y2);
int pawns_check(int x,int y,int x2,int y2);
int rooks_check (int x, int y,int y1,int x1);
int bishops_check (int x,int y,int y1,int x1);
int queen_check (int x,int y,int y1,int x1);




#endif // MOVEMENT_H_INCLUDED
