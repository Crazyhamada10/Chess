#ifndef VS_COMPUTER_H_INCLUDED
#define VS_COMPUTER_H_INCLUDED

int availble_moves [1024][4];
int values[1024];
int place_change;
int change ;

void ai_new_game ();
void ai_Get_Input();
int ai_pawns(int x,int y,int x2,int y2);
int ai_pawns_promotion (int x1,int y1,int x2,int y2);
void ai_game ();
void making_decision();
int pawns_check_ai(int x,int y,int x2,int y2);
void giving_values ();
void taking_decision();
void printing();
void change_board_structure_ai(int place);
void ai_redo();
void ai_undo();
void mine_max ();
int check_myenemy();
#endif // VS_COMPUTER_H_INCLUDED
