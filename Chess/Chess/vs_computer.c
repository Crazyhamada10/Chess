#include <stdio.h>
#include <math.h>
#include "board.h"
#include "movement.h"
#include "vs_computer.h"

void ai_new_game()
{
    first_board_structure();
    counter = 1;
    w = 0;
    ai_game();

}

void ai_game()
{
    while (flag1 == 0)
    {
        if (counter != 1)
        {
            int mate1 = checkmate();
            int mate2 = probability_of_movement();
            if (mate2 == 1 && mate1 == 1)
            {
                printf("\n\t\t\t\t\t\*\* CHECKMATE \*\*\n");
                printf("\n\t\t\t\t\t\*\* YOU LOSE \*\*\n");
                flag1 = 1;
            }
            else if (mate2 == 1 && mate1 == 0)
            {
                printf("\n\t\t\t\t\t\*\* STALEMATE \*\*\n");
                flag1 = 1;
            }
            else if (mate1 == 1)
            {
                colour_it("red");
                printf("\nyou are checked\n");
                colour_it("white");
            }
        }
        if (flag1 == 0)
        {
            ai_Get_Input();
            if (flag1 != 1)
            {
                change_board_structure();
                if (flag2 != 1)
                {
                    change = 0;
                    place_change =0;
                    system ("cls");
                    counter++;
                    making_decision ();
                    giving_values ();
                    mine_max();
                    taking_decision ();
                    input[0] = availble_moves[place_change][0]+65;
                    input[1] = 8-availble_moves[place_change][1]+48;
                    input[2] = availble_moves[place_change][2]+65;
                    input[3] = 8-availble_moves[place_change][3]+48;
                    if (change == 1)
                        input[4] = 'Q';
                    genralsave();
                    Printing_board();
                    if (place_change != -1)
                    {
                        //printing();
                        printf("COMPUTER MOVE: %c%i%c%i\n",availble_moves[place_change][0]+65,8-availble_moves[place_change][1],availble_moves[place_change][2]+65,8-availble_moves[place_change][3]);
                        counter++;
                    }
                    else
                    {
                        int check_king = checkmate();
                        if (check_king  == 1)
                        {
                            printf("\n\t\t\t\t\t\*\* CHECKMATE \*\*\n");
                            printf("\n\t\t\t\t\t\*\* YOU WINS \*\*\n");
                            flag1 = 1;
                        }
                        else
                        {
                            printf("\n\t\t\t\t\t\*\* STALEMATE \*\*\n");
                            flag1 = 1;
                        }
                    }
                }
            }
        }
    }
    printf("\n\t\t\t\t\t\*\* Game Ended \*\*\n");
}

void ai_Get_Input()
{
    printf("Your move: ");
    int flag = 0,i = -1;
    do
    {
        for (int j =0;j<=i;j++)
            input[j] = '\0';
        if (i!= -1)
            printf("Retry : ");
        i =-1;
        fflush(stdin);
        while (input [i] != '\n')
        {
            i++;
            scanf("%c", &input[i]);
        }
        if ((input[0] == 'S' || input[0] == 'L' || input[0] == 'U' || input[0] == 'R' || input[0] == 'Q') && input[1] == '\n')
        {
            flag = 1;
            i = -1;
            switch (input[0])
            {
            case 'S':
                save();
                break;
            case 'L':
                load_inside();
                break;
            case 'U':
                ai_undo();
                break;
            case 'R':
                ai_redo();
                break;
            case 'Q':
                flag1 = 1;
                flag = 0;
                break;
            }
            if (input[0] != 'Q')
                    printf("Your move: ");
        }
        else if (input[0] < 'A' || input[0] > 'H' || input[2] < 'A' || input[2] > 'H' || input[1] < '1' || input[1] > '8' || input[3] < '1' || input[3] > '8')
        {
            printf("Invalid Input\n");
            flag = 1;
        }
        else if ((input[4] == 'r' || input[4] == 'n' || input[4] == 'b' || input[4] == 'q') && input[5] == '\n')
        {
            //Promotion
            int x1 = input[0] - 'A';
            int x2 = input[2] - 'A';
            int y1 = input[1] - '1';
            int y2 = input[3] - '1';
            flag = ai_pawns_promotion(x1,y1,x2,y2);
            if (flag == 1)
                flag = 0;
            else
                flag = 1;
        }
        else if (input[4] != '\n')
        {
            printf("Invalid Input\n");
            flag = 1;
        }
        else
        {
            int x1 = input[0] - 'A';
            int x2 = input[2] - 'A';
            int y1 = input[1] - '1';
            int y2 = input[3] - '1';
            int x = x2 - x1;
            int y = y1 - y2;
            /*player1*/
            /*check inside square*/
            if (chess[x1][7-y1] !=  'k' && chess[x1][7-y1] !=  'q' && chess[x1][7-y1] !=  'r' && chess[x1][7-y1] !=  'p' && chess[x1][7-y1] !=  'b' && chess[x1][7-y1] !=  'n')
            {
                printf("Invalid move: There is nothing in the square or its not your piece\n");
                flag = 1;
            }
            /*check to the new square*/
            else if (chess[x2][7-y2] == 'k' || chess[x2][7-y2] == 'q' || chess[x2][7-y2] == 'r' || chess[x2][7-y2] == 'p' || chess[x2][7-y2] == 'b' || chess[x2][7-y2] == 'n')
            {
                printf("Invalid move: You want to put two of your pieces in the same square\n");
                flag = 1;
            }
            else
            {
                /*make if and check about check mate before moving*/
                switch (chess[x1][7-y1])
                {
                case 'k':
                        flag = king(x,y);
                        break;
                case 'q':
                        flag = queen(x,y,y1,x1);
                        break;
                case 'b':
                        flag = bishops(x,y,y1,x1);
                        break;
                case 'n':
                        flag = knights(x,y);
                        break;
                case 'r':
                        flag = rooks(x,y,y1,x1);
                        break;
                case 'p':
                        flag = ai_pawns(x,y,x2,y2);
                        break;
                }
                if (flag == 1)
                    flag = 0;
                else
                {
                    flag = 1;
                    printf("Invalid move\n");
                }
            }
        }
    }
    while (flag == 1);
}

int ai_pawns(int x,int y,int x2,int y2)
{
        if (y == -2 && x == 0 && input[1] == '2' && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-') && (chess[x2][8-y2] == '.' || chess[x2][8-y2] == '-'))
            return 1;
        else if (y == -1 && x == 0 && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-'))
        {
            int y1 = input[1] - '1';
            if (y1 == 6 && y2 == 7)
            {
                printf("You don't enter promotion piece\n");
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else if (y == -1 && abs(x) == 1 && chess[x2][7-y2] != '.' && chess[x2][7-y2] != '-')
        {
            int y1 = input[1] - '1';
            if (y1 == 6 && y2 == 7)
            {
                 colour_it("red");
                printf("You don't enter promotion piece\n");
                colour_it("white");
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
            return 0;
}

int ai_pawns_promotion (int x1,int y1,int x2,int y2)
{
    int x = x2-x1;
    int y = y1-y2;
    if (chess[x1][7-y1] == 'p' && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-') && x == 0 && y == -1 && y1 == 6 && y2 == 7)
        return 1;
    else if (chess[x1][7-y1] == 'p' && chess[x2][7-y2] != '.' && chess[x2][7-y2] != '-' && abs(x) == 1 && y == -1 && y1 == 6 && y2 == 7)
        return 1;
    else
        return 0;
}

void making_decision ()
{
    int flag_check = 0;
    int exist = 0;
    int x2,y2;
    int x1,y1;
    int v =0;
    for (int a =0;a<1024;a++)
    {
        for (int b=0;b<4;b++)
        {
            availble_moves[a][b] = 0;
        }
    }
    for (int i = 0;i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chess[i][j] == 'K' || chess[i][j] == 'P' || chess[i][j] == 'N' || chess[i][j] == 'B' || chess[i][j] == 'R' || chess[i][j] == 'Q')
            {
                x1 = i;
                y1 = 7-j;
                for (int q = 0;q<8;q++)
                {
                    for (int w =0;w<8;w++)
                    {
                        flag_check =0;
                        exist = 0;
                        x2 = q;
                        y2 = 7-w;
                        int x = x2 - x1;
                        int y = y1 - y2;
                        if (chess[q][w] == 'K' || chess[q][w] == 'Q' || chess[q][w] == 'R' || chess[q][w] == 'P' || chess[q][w] == 'B' || chess[q][w] == 'N')
                        {
                            flag_check = 0;
                        }
                        else
                        {
                            switch (chess[i][j])
                            {
                            case 'P':
                                if (pawns_check_ai(x,y,x2,y2) == 1)
                                {
                                    exist = 1;
                                    flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                }
                                break;
                            case 'K':
                                if ((abs(x) == 1 && y == 0) || (abs(x) == 1 && abs(y) == 1) || (x == 0 && abs(y) == 1))
                                {
                                   exist = 1;
                                   flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                }
                                break;
                            case 'N':
                                if ((abs(x) == abs(y) + 1 && (x == 2 || x == -2)) || (abs(y) == abs(x) + 1 && (y == 2 || y == -2)))
                                {
                                    exist = 1;
                                    flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                }
                                break;
                            case 'R':
                                if (rooks_check (x,y,y1,x1) == 1)
                                {
                                    exist = 1;
                                    flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                }
                                break;
                            case 'B':
                                if (bishops_check (x,y,y1,x1) == 1)
                                {
                                    exist = 1;
                                    flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                }
                                break;
                            case 'Q':
                                if (queen_check (x,y,y1,x1) == 1)
                                {
                                    exist = 1;
                                    flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                }
                                break;
                            }
                        }
                        if (flag_check == 0 && exist == 1)
                        {
                            availble_moves [v][0] = i;
                            availble_moves [v][1] = j;
                            availble_moves [v][2] = q;
                            availble_moves [v][3] = w;
                            v++;
                        }
                    }
                }
            }
        }
    }
}

void giving_values()
{
    int v = 0;
    for (int u =0;u<1024;u++)
        values[u] = 0;
    while(!(availble_moves[v][0] == 0 && availble_moves[v][1] == 0 && availble_moves[v][2] == 0 && availble_moves[v][3] == 0))
    {
        switch (chess[availble_moves[v][2]][availble_moves[v][3]])
        {
        case '.':
        case '-':
            values [v] = 20;
            break;
        case 'q':
            values [v] = 300;
            break;
        case 'b':
        case 'r':
        case 'n':
            values [v] = 100;
            break;
        case 'p':
            values [v] = 40;
            break;
        }
        int flag_check = check_myenemy();
        if (flag_check == 0)
            values[v] = values[v] + 200;
        v++;
    }
}

void mine_max ()
{
    int kill =0;
    int change_queen = 0;
    int sum =0;
    while (!(availble_moves[kill][0] == 0 && availble_moves[kill][1] == 0 && availble_moves[kill][2] == 0 && availble_moves[kill][3] == 0))
    {
        change_queen = 0;
        int a1 = availble_moves[kill][0];
        int a2 = availble_moves[kill][2];
        int b1 = 7-availble_moves[kill][1];
        int b2 = 7-availble_moves[kill][3];
        if (b2 == 0 && chess[a1][7-b1] == 'P')
        {
            chess[a1][b1] = 'Q';
            change_queen =1;
        }
        char flash1 = chess[a1][7-b1], flash2 = chess[a2][7-b2];
        if((a1+b1)%2==0)
        {
            chess[a2][7-b2] = chess[a1][7-b1];
            chess[a1][7-b1]='-';
        }
        else
        {
            chess[a2][7-b2]=chess[a1][7-b1];
            chess[a1][7-b1]='.';
        }
        sum = 0;
        counter++;
        /*********************************************************************/
        int flag_check = 0;
        int exist = 0;
        int c2,d2;
        int c1,d1;
        for (int i = 0;i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (chess[i][j] == 'k' || chess[i][j] == 'p' || chess[i][j] == 'n' || chess[i][j] == 'b' || chess[i][j] == 'r' || chess[i][j] == 'q')
                {
                    c1 = i;
                    d1 = 7-j;
                    for (int q = 0;q<8;q++)
                    {
                        for (int w =0;w<8;w++)
                        {
                            flag_check =0;
                            exist = 0;
                            c2 = q;
                            d2 = 7-w;
                            int c = c2 - c1;
                            int d = d1 - d2;
                            if (chess[q][w] == 'k' || chess[q][w] == 'q' || chess[q][w] == 'r' || chess[q][w] == 'p' || chess[q][w] == 'b' || chess[q][w] == 'n')
                            {
                                flag_check = 0;
                            }
                            else
                            {
                                switch (chess[i][j])
                                {
                                case 'p':
                                    if (pawns_check_ai(c,d,c2,d2) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (c1,d1,c2,d2);
                                    }
                                    break;
                                case 'k':
                                    if ((abs(c) == 1 && d == 0) || (abs(c) == 1 && abs(d) == 1) || (c == 0 && abs(d) == 1))
                                    {
                                       exist = 1;
                                       flag_check = change_board_structure_for_checkmate (c1,d1,c2,d2);
                                    }
                                    break;
                                case 'n':
                                    if ((abs(c) == abs(d) + 1 && (c == 2 || c == -2)) || (abs(d) == abs(c) + 1 && (d == 2 || d == -2)))
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (c1,d1,c2,d2);
                                    }
                                    break;
                                case 'r':
                                    if (rooks_check (c,d,d1,c1) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (c1,d1,c2,d2);
                                    }
                                    break;
                                case 'b':
                                    if (bishops_check (c,d,d1,c1) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (c1,d1,c2,d2);
                                    }
                                    break;
                                case 'q':
                                    if (queen_check (c,d,d1,c1) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (c1,d1,c2,d2);
                                    }
                                    break;
                                }
                            }
                            if (flag_check == 0 && exist == 1)
                            {
                                int change_queen_2 =0;
                                if (d2 == 7 && chess[c1][7-d1] == 'p')
                                {
                                    chess[c1][d1] = 'q';
                                    change_queen_2 = 1;
                                }
                                char flash3 = chess[c1][7-d1], flash4 = chess[c2][7-d2];
                                if((c1+d1)%2==0)
                                {
                                    chess[c2][7-d2] = chess[c1][7-d1];
                                    chess[c1][7-d1]='-';
                                }
                                else
                                {
                                    chess[c2][7-d2]=chess[c1][7-d1];
                                    chess[c1][7-d1]='.';
                                }
                                counter++;
                                /********************************************************************************************************/
                                int flag_check_2 = 0;
                                int exist_2 = 0;
                                int x2,y2;
                                int x1,y1;
                                for (int i = 0;i < 8; i++)
                                {
                                    for (int j = 0; j < 8; j++)
                                    {
                                        if (chess[i][j] == 'K' || chess[i][j] == 'P' || chess[i][j] == 'N' || chess[i][j] == 'B' || chess[i][j] == 'R' || chess[i][j] == 'Q')
                                        {
                                            x1 = i;
                                            y1 = 7-j;
                                            for (int q = 0;q<8;q++)
                                            {
                                                for (int w =0;w<8;w++)
                                                {
                                                    flag_check_2 =0;
                                                    exist_2 = 0;
                                                    x2 = q;
                                                    y2 = 7-w;
                                                    int x = x2 - x1;
                                                    int y = y1 - y2;
                                                    if (chess[q][w] == 'K' || chess[q][w] == 'Q' || chess[q][w] == 'R' || chess[q][w] == 'P' || chess[q][w] == 'B' || chess[q][w] == 'N')
                                                    {
                                                        flag_check_2 = 0;
                                                    }
                                                    else
                                                    {
                                                        switch (chess[i][j])
                                                        {
                                                        case 'P':
                                                            if (pawns_check_ai(x,y,x2,y2) == 1)
                                                            {
                                                                exist_2 = 1;
                                                                flag_check_2 = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                                            }
                                                            break;
                                                        case 'K':
                                                            if ((abs(x) == 1 && y == 0) || (abs(x) == 1 && abs(y) == 1) || (x == 0 && abs(y) == 1))
                                                            {
                                                               exist_2 = 1;
                                                               flag_check_2= change_board_structure_for_checkmate (x1,y1,x2,y2);
                                                            }
                                                            break;
                                                        case 'N':
                                                            if ((abs(x) == abs(y) + 1 && (x == 2 || x == -2)) || (abs(y) == abs(x) + 1 && (y == 2 || y == -2)))
                                                            {
                                                                exist_2 = 1;
                                                                flag_check_2 = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                                            }
                                                            break;
                                                        case 'R':
                                                            if (rooks_check (x,y,y1,x1) == 1)
                                                            {
                                                                exist_2 = 1;
                                                                flag_check_2 = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                                            }
                                                            break;
                                                        case 'B':
                                                            if (bishops_check (x,y,y1,x1) == 1)
                                                            {
                                                                exist_2 = 1;
                                                                flag_check_2 = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                                            }
                                                            break;
                                                        case 'Q':
                                                            if (queen_check (x,y,y1,x1) == 1)
                                                            {
                                                                exist_2 = 1;
                                                                flag_check_2 = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                                            }
                                                            break;
                                                        }
                                                    }
                                                    if (flag_check_2 == 0 && exist_2 == 1)
                                                    {
                                                        switch (chess[x2][7-y2])
                                                        {
                                                        case '.':
                                                        case '-':
                                                            sum++;
                                                            break;
                                                        case 'q':
                                                            sum+=10;
                                                            break;
                                                        case 'b':
                                                        case 'r':
                                                        case 'n':
                                                            sum+=5;
                                                            break;
                                                        case 'p':
                                                            sum+=2;
                                                            break;
                                                        }
                                                        int flag_check_3 = check_myenemy();
                                                        if (flag_check_3 == 0)
                                                            sum+=11;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                /********************************************************************************************************/
                                counter--;
                                chess[c2][7-d2] = flash4;
                                chess[c1][7-d1] = flash3;
                                if (change_queen_2 == 1)
                                    chess[c1][d1] = 'P';
                                switch (chess[c2][7-d2])
                                {
                                case '.':
                                case '-':
                                    sum-=10;
                                    break;
                                case 'Q':
                                    sum -=200;
                                    break;
                                case 'B':
                                case 'R':
                                case 'N':
                                    sum-= 50;
                                    break;
                                case 'P':
                                    sum-=20;
                                    break;
                                }
                                int flag_check_4 = check_myenemy();
                                if (flag_check_4 == 0)
                                    sum-=100;
                            }
                        }
                    }
                }
            }
        }
        /*********************************************************************/
        counter--;
        values[kill] +=sum;
        chess[a2][7-b2] = flash2;
        chess[a1][7-b1] = flash1;
        if (change_queen == 1)
            chess[a1][b1] = 'P';
        kill++;
    }
}

void printing()
{
    for (int i = 0; i <1024;i++)
    {
        if (availble_moves[i][0] == 0 && availble_moves[i][1] == 0 && availble_moves[i][2] == 0 && availble_moves[i][3] == 0)
            i = 1024;
        else
        {
            printf("%c%i%c%i",availble_moves[i][0]+65,8-availble_moves[i][1],availble_moves[i][2]+65,8-availble_moves[i][3]);
            printf("\t%i\n",values[i]);
        }
    }
}

void taking_decision()
{
     int max = 0;
     int place =0;
     int arr[500] = {0};
     int u =0;
     for (int k =0;k <1024;k++)
     {
        if (availble_moves[k][0] == 0 && availble_moves[k][1] == 0 && availble_moves[k][2] == 0 && availble_moves[k][3] == 0)
            k = 1024;
        else if(values[k] >= max)
        {
            max = values[k];
        }
     }
     if (max == 0)
        place_change = -1;
     else
     {
         for (int j = 0;j<1024;j++)
         {
             if (values[j] == max)
             {
                arr[u] = j;
                u++;
             }
         }
         place = arr[(u-1)/2];
         place_change = place;
        change_board_structure_ai(place);
     }
}

int pawns_check_ai(int x,int y,int x2,int y2)
{
        int y1 = y + y2;
    if (counter%2 == 0)
    {
        if (y == 2 && x == 0 && y1 == 6 && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-') && (chess[x2][6-y2] == '.' || chess[x2][6-y2] == '-'))
            return 1;
        else if (y == 1 && x == 0 && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-'))
            return 1;
        else if (y == 1 && abs(x) == 1 && chess[x2][7-y2] != '.' && chess[x2][7-y2] != '-')
            return 1;
        else
            return 0;
    }
    else
    {
        if (y == -2 && x == 0 && y1 == 1 && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-') && (chess[x2][6-y2] == '.' || chess[x2][6-y2] == '-'))
            return 1;
        else if (y == -1 && x == 0 && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-'))
            return 1;
        else if (y == -1 && abs(x) == 1 && chess[x2][7-y2] != '.' && chess[x2][7-y2] != '-')
            return 1;
        else
            return 0;
    }
}

void change_board_structure_ai(int place)
{
    int x1 = availble_moves[place][0];
    int x2 = availble_moves[place][2];
    int y1 = 7-availble_moves[place][1];
    int y2 = 7-availble_moves[place][3];
    if (y2 == 0 && chess[x1][7-y1] == 'P')
    {
        chess[x1][y1] = 'Q';
        change = 1;
    }
    if((x1+y1)%2==0)
    {
        if (chess[x2][7-y2]!= '.' && chess[x2][7-y2]!= '-')
        {
            dead[w] = chess[x2][7-y2];
            w++;
        }
        chess[x2][7-y2] = chess[x1][7-y1];
        chess[x1][7-y1]='-';
    }
    else
    {
        if (chess[x2][7-y2]!= '.' && chess[x2][7-y2]!= '-')
        {
            dead[w] = chess[x2][7-y2];
            w++;
        }
        chess[x2][7-y2]=chess[x1][7-y1];
        chess[x1][7-y1]='.';
    }
}

void ai_redo()
{
    int counter_delr=0,i=0;
    char tempr[11]={'\0'};
    FILE * redo;
    FILE * redotemp;
    FILE * redorestore;
    FILE * appendmain;
    FILE * readmain;

    redo = fopen("redofile.txt","r");
    while(!feof(redo))
    {
        fgets(tempr,11,redo);
        counter_delr++;
    }
    fseek(redo,0,SEEK_SET);
    if(unrdo_counter==0 || redo==NULL)
    {
        colour_it("red");
        printf("sorry can't redo\n");
        colour_it("white");
    }
    else
    {
    i=0;
    while(i<counter_delr-3)
    {
        fgets(tempr,11,redo);
        i++;
    }
    redotemp = fopen("temp.txt","w+");
    appendmain = fopen("#####.txt","a");
    char bug2[6] = {'\0'};
     int b =-1;
     while (bug2[b] != '\n')
     {
        b++;
        bug2[b]= fgetc(redo);
     }
        fgets(tempr,11,redo);
        fprintf(appendmain,tempr);
        fprintf(appendmain,bug2);
        fclose(appendmain);
        fseek(redo,0,SEEK_SET);
        i=0;
    while(i<counter_delr-3)
    {
        fgets(tempr,11,redo);
        fprintf(redotemp,tempr);
        i++;
    }
    i=0;
    fseek(redotemp,0,SEEK_SET);
    redorestore = fopen("redofile.txt","w+");
    while(i<counter_delr-3)
    {
        fgets(tempr,11,redotemp);
        fprintf(redorestore,tempr);
        i++;
    }
    counter_delr=0;
    i=0;
    readmain = fopen("#####.txt","r");
    while(!feof(readmain))
    {
        fgets(tempr,11,readmain);
        counter_delr++;
    }
    fseek(readmain,0,SEEK_SET);
    first_board_structure_undo();
    while(i<counter_delr-1)
    {
        fgets(tempr,11,readmain);
        change_board_structure_for_load(tempr);
        i++;
    }
    system("cls");
    Printing_board();
    fclose(redo);
    fclose(redorestore);
    fclose(redotemp);
    unrdo_counter--;
    counter+=2;
    }
}

void ai_undo()
{
  char tempu[11]={'\0'};
  int i=0,counter_delu=0;
  FILE * pointerundo;
  FILE * pointertemp;
  FILE * pointerredofile;
  FILE * pointerestore;
  pointertemp= fopen("temp.txt","w+");
  pointerundo= fopen("#####.txt","r");
    if(unrdo_counter == 0)
    {
     pointerredofile = fopen("redofile.txt","w+");
    }
    else
    {
      pointerredofile= fopen("redofile.txt","a");
    }
  if(counter==1)
  {
    colour_it("red");
    printf("Sorry can't undo\n");
    colour_it("white");
  }
  else if (counter==3)
  {
    fseek(pointerundo,0,SEEK_SET);
    char bug2[6] = {'\0'};
     int b =-1;
     while (bug2[b] != '\n')
     {
        b++;
        bug2[b]= fgetc(pointerundo);
     }
     fgets(tempu,11,pointerundo);
     fprintf(pointerredofile,tempu);
     fprintf(pointerredofile,bug2);
    first_board_structure();
    pointerestore=fopen("#####.txt","w");
    counter-=2;
    unrdo_counter++;
    fclose(pointerundo);
    fclose(pointerestore);
    fclose(pointerredofile);
    fclose(pointertemp);
  }
  else
  {

    while(!feof(pointerundo))
    {
        fgets(tempu,11,pointerundo);
        counter_delu++;
    }
    fseek(pointerundo,0,SEEK_SET);
    first_board_structure_undo();
    while(i<(counter_delu-3))
    {
        fgets(tempu,11,pointerundo);
        fprintf(pointertemp,tempu);
        change_board_structure_for_load(tempu);
        i++;
    }
     char bug[6] = {'\0'};
     int a =-1;
     while (bug[a] != '\n')
     {
        a++;
        bug[a]= fgetc(pointerundo);
     }
     fgets(tempu,11,pointerundo);
     fprintf(pointerredofile,tempu);
     fprintf(pointerredofile,bug);
    counter_delu=0;i=0;
    fseek(pointertemp,0,SEEK_SET);
    pointerestore=fopen("#####.txt","w");
    while(!feof(pointertemp))
    {
        fgets(tempu,11,pointertemp);
        counter_delu++;
    }
    fseek(pointertemp,0,SEEK_SET);
    while(i<(counter_delu-1))
    {
        fgets(tempu,11,pointertemp);
        fprintf(pointerestore,tempu);
        i++;
    }
  system("cls");
  Printing_board();
  counter-=2;
  unrdo_counter++;
  fclose(pointerundo);
  fclose(pointerestore);
  fclose(pointerredofile);
  fclose(pointertemp);
  }
}

int check_myenemy ()
{
    if (counter%2 ==0)
    {
        int xking=0,yking=0;
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'k')
                {
                    xking=i;
                    yking=j;
                    j=8;
                    i=8;
                }
            }
        }
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'P' || chess[i][j] == 'N' || chess[i][j] == 'R' || chess[i][j] == 'Q' || chess[i][j] == 'B')
                {
                    counter++;
                    check = checkmate_input(chess[i][j],i,7-j,xking,7-yking);
                    counter--;
                    if (check == 1)
                        return 0;
                }
            }
        }
        return 1;
    }
    else
    {
        int xking=0,yking=0;
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'K')
                {
                    xking=i;
                    yking=j;
                    j=8;
                    i=8;
                }
            }
        }
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'p' || chess[i][j] == 'n' || chess[i][j] == 'r' || chess[i][j] == 'q' || chess[i][j] == 'b')
                {
                    counter++;
                    check = checkmate_input(chess[i][j],i,7-j,xking,7-yking);
                    counter--;
                    if (check == 1)
                        return 0;
                }
            }
        }
        return 1;
    }
}

