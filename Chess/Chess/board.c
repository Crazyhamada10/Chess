#include <math.h>
#include <stdio.h>
#include "board.h"
#include <windows.h>

void Starting ()
{
    colour_it("green");
    printf (" _____  _                     \n");
    colour_it("yellow");
    printf ("/  __ \\| |                   \n");
    colour_it("blue");
    printf ("| /  \\/| |__    ___  ___  ___ \n");
    colour_it("green");
    printf ("| |    | '_ \\  / _ \\/ __|/ __|\n");
    colour_it("yellow");
    printf ("| \\__/\\| | | ||  __/\\__ \\\\__ \\\n");
    colour_it("blue");
    printf (" \\____/|_| |_| \\___||___/|___/\n\n");
    colour_it("white");

    printf("Chess is a two-player board game played on a chessboard, a checkered gameboard\nwith 64 squares arranged in an eight-by-eight grid. Each player begins the\ngame with 16 pieces. The objective is to 'checkmate' the opponent's king by placing\nit under an inescapable threat of capture.\n\n");
    printf("1) Start a new game\n");
    printf("2) Load saved game\n");
    printf("3) How to play\n");
    printf("4) Quit\n\n");

    flag1 = 0;
    save_flag = 0;
    flag2 = 0;
    unrdo_counter = 0;
    char indicator = '\0';
    char newline = '\0';
    int i =0;
    while (newline != '\n' || (indicator != '1' && indicator != '2' && indicator != '3' && indicator != '4'))
    {
        if (i != 0)
        {
            colour_it("red");
            printf("Invalid Input, Retry: ");
            colour_it("white");
        }
        fflush(stdin);
        scanf ("%c%c",&indicator,&newline);
        i++;
    }
    int y =0;/*check about 1 player or 2 players*/
    switch (indicator)
    {
    case '1':
        y = test();
        if (y == 1)
            new_game();
        else
            ai_new_game ();
        break;
    case '2':
        load_outside();
        game();
        break;
    case '3':
        how_to_play();
        break;
    case '4':
        flag1 = 1;
        game();
        break;
    }
}

int test()
{
    int flag_test =0;
    int y =0;
     system ("cls");
    printf("\n1) Two players\n");
    printf("2) One player\n\n");
    int var1 = 0;
    do
    {
        fflush(stdin);
        if (y != 0)
            printf("Retry: ");
        var1 = 0;
        char var2='\0';
        scanf("%i%c", &var1,&var2);
        y++;
        if((var1 == 1 || var1 == 2) && var2 == '\n')
            flag_test = 1;
    }
    while(flag_test == 0);
    return var1;
}

void first_board_structure ()
{
    for(int j=0;j<8;j++)
    {
        for(int i=0;i<8;i++)
        {
            if((i+j)%2==0 && j!=1 && j!=6)
                chess[i][j]='.';
            else if(j==6)
                chess[i][j]='p';
            else if (j==1)
                chess[i][j] = 'P';
            else
                chess[i][j]='-';
        }
    }
    chess[0][0]='R';chess[1][0]='N';chess[2][0]='B';chess[3][0]='Q';chess[4][0]='K';chess[5][0]='B';chess[6][0]='N';chess[7][0]='R';
    chess[0][7]='r';chess[1][7]='n';chess[2][7]='b';chess[3][7]='q';chess[4][7]='k';chess[5][7]='b';chess[6][7]='n';chess[7][7]='r';
    system ("cls");
    Printing_board();
}

void Printing_board()
{
    printf("    %c       %c       %c       %c       %c       %c       %c       %c    \n",'A','B','C','D','E','F','G','H');
    char alphabit ='A';
    for(int j=0;j<34;j++)
    {
        for(int i=0;i<9;i++)
        {
            if(j%4!=0 && j%2!=0 && j!=0 && i!=8 && j!=33)
                printf(" |     |");
            else if(j%2==0 && j%4!=0 && j!=0 && i!=8 && j!=33)
                {
                printf(" |  ");
                if(chess[i][(j-2)/4]>='a' && chess[i][(j-2)/4]<'z')
                {
                  colour_it("yellow");
                }
                else if(chess[i][(j-2)/4]>='A' && chess[i][(j-2)/4]<'Z')
                {
                  colour_it("blue");
                }
                printf("%c",chess[i][(j-2)/4]);
                colour_it("white");
                printf("  |");
                }
            else if((j%4==0 || j==0) && i!=11 && i!=8 && j!=33)
                printf("  ~~~~~ ");
            else if (i==8 && j%2==0 && j%4!=0 && j!=0 && j!=33)
                printf(" %d",(int)fabs(((j-2)/4)-8));
            else if (j==33 && i!=8 )
                printf("    %c   ",alphabit++);
        }
        printf("\n");
    }
    int o = 0,u=0;
    char dead1[20] = {'\0'};
    char dead2[20] = {'\0'};
    for (int i =0;i <36;i++)
    {
        if (dead[i] == 'p' || dead[i] == 'q' ||dead[i] == 'n' ||dead[i] == 'b' || dead[i] == 'r')
        {
            dead1[u] = dead[i];
            u++;
        }
        else if (dead[i] == 'P' || dead[i] == 'Q' ||dead[i] == 'N' ||dead[i] == 'B' || dead[i] == 'R')
        {
            dead2[o] = dead[i];
            o++;
        }
    }
    colour_it("red");
    printf("Player one deads: ");
    colour_it("yellow");
    for (int i =0;i<u;i++)
        printf("%c  ",dead1[i]);
    printf("\n");
    colour_it("red");
    printf("Player two deads: ");
    colour_it("blue");
    for (int i = 0;i<o;i++)
        printf("%c  ",dead2[i]);
    colour_it("white");
    printf("\n");
}

void change_board_structure()
{
        flag2 = 0;
        int x1 = input[0] - 'A';
        int x2 = input[2] - 'A';
        int y1 = input[1] - '1';
        int y2 = input[3] - '1';
        char flash1 = chess[x1][7-y1], flash2 = chess[x2][7-y2];
        if (input[4] != '\n')
            chess[x1][7-y1] = input[4];
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
        int flash = check_myself();
        if (flash == 0)
        {
            chess[x2][7-y2] = flash2;
            chess[x1][7-y1] = flash1;
            flag2 = 1;
        }
        if (flag2 == 0)
            genralsave();
}

void new_game()
{
    first_board_structure();
    counter = 1;
    w = 0;
    game ();
}

void game ()
{
    while (flag1 == 0)
    {
        if (counter != 1)
        {
            int mate1 = checkmate();
            int mate2 = probability_of_movement();
            if (mate2 == 1 && mate1 == 1)
            {
                colour_it("red");
                printf("\n\t\t\t\t\t\*\* CHECKMATE \*\*\n");
                colour_it("white");
                if (counter % 2 == 0)
                {
                    colour_it("red");
                    printf("\n\t\t\t\t\t\*\* PLAYER ONE WINS \*\*\n");
                    colour_it("white");
                }
                else{
                        colour_it("red");
                        printf("\n\t\t\t\t\t\*\* PLAYER TWO WINS \*\*\n");
                        colour_it("white");
                    }
                flag1 = 1;
            }
            else if (mate2 == 1 && mate1 == 0)
            {
                colour_it("red");
                printf("\n\t\t\t\t\t\*\* STALEMATE \*\*\n");
                colour_it("white");
                flag1 = 1;
            }
            else if (mate2 == 0 && mate1 == 1)
            {
                colour_it("red");
                printf("\n\*\* YOU ARE CHECKED \*\*\n");
                colour_it("white");
            }
        }
        if (flag1 == 0)
        {
            Get_Input();
            if (flag1 != 1)
            {
                change_board_structure();
                if (flag2 != 1)
                {
                    system ("cls");
                    Printing_board();
                    counter++;
                }
            }
        }
    }
    colour_it("red");
    printf("\n\t\t\t\t\t\*\* Game Ended \*\*\n");
    colour_it("white");
}

void how_to_play ()
{
    system ("cls");
    printf("When you start playing, enter the position of the piece you want to move\nfollowed by the position you want it to go. At any time you can save by\nentering \'S\'\, can load by entering \'L\'\, can undo by entering \'U\' and can\nredo by entering \'R\',you also can quit by entering \'Q\'.\n");
    printf("Enter \'B'\ to go back: ");
    char indicator = '\0';
    char newline = '\0';
    int i =0;
    while (newline != '\n' || indicator != 'B')
    {
        if (i != 0){
            colour_it("red");
            printf("Invalid Input, Retry: ");
            colour_it("white");}
        fflush(stdin);
        scanf ("%c%c",&indicator,&newline);
        i++;
    }
    printf("\n");
    system ("cls");
    Starting();
}

void genralsave ()
{
  FILE * pointercreate;
  FILE * pointergenralsave;
  unrdo_counter=0;
  if(counter==1)
  {
        pointercreate =fopen("#####.txt","w");
        fclose(pointercreate);
  }
    pointergenralsave = fopen("#####.txt","a");
    fprintf(pointergenralsave,"%s",input);
    fclose(pointergenralsave);
}

void save()
{
  int counterread=0 ;
  char savename [11];
  char temp [11] ;
  FILE * pointersave;
  FILE * pointerread;
  FILE * pointersavename;
  pointerread = fopen("#####.txt","r");
  pointersavename = fopen("345.txt","a");
  colour_it("green");
  printf("Enter the name of your new save: ");
  colour_it("white");
  fflush(stdin);
  gets(savename);
  pointersave = fopen(savename,"w+");
  fprintf(pointersavename,"%s\n",savename);
  while(counterread<counter-1)
  {
    fgets(temp,11,pointerread);
    fprintf(pointersave,"%s",temp);
    counterread++;
  }
    fclose(pointersave);
    fclose(pointersavename);
}

void load_inside()
{
  int i=1,counter_del=1,c1=0,load_flag=1;
  char temp1[11]={'\0'};
  char temp2[11]={'\0'};
  char c2='\0';
  FILE * pointerreadsave;
  FILE * pointerload;
  pointerreadsave = fopen("345.txt","r");

    if(pointerreadsave==NULL)
    {
        colour_it("red");
        printf("Sorry, there are no loads\n\n");
        colour_it("white");
        fclose(pointerreadsave);
    }
    else
    {
        colour_it("green");
        printf("\nsaves are:\n");
        while(!feof(pointerreadsave))
        {
            fgets(temp2,11,pointerreadsave);
            counter_del++;
        }
        fseek(pointerreadsave,0,SEEK_SET);
        colour_it("yellow");
        while(i<counter_del-1)
        {
            fgets(temp2,11,pointerreadsave);
            printf("%d}%s",i,temp2);
            i++;
        }
        colour_it("green");
        printf("\nChoose a save:(TO GO BACK TO GAME<b>)\n");gets(temp1);
        colour_it("white");
        strcat(temp1,"\n");
        fseek(pointerreadsave,0,SEEK_SET);
        i=0;
        while(i<counter_del-1)
        {
            fgets(temp2,11,pointerreadsave);
            if((strcmp(temp1,temp2))==0)
            {
                load_flag=0;
            }
            i++;
        }
        if(temp1[0]=='b' && counter == 0)
        {
          Starting();
        }
        else if (temp1[0]=='b' && counter != 0)
        {
          NULL;
        }
        else
        {
            load_logo();
            save_flag = 1;
            while(load_flag==1 && save_flag==1)
            {
                save_flag=1;
                colour_it("red");
                printf("This save doesn't exist \n1)To go back press 1\n2)To load another save press 2 \n");
                colour_it("white");
                scanf("%d%c",&c1,&c2);
                fflush(stdin);
                while(!(c1==1 || c1==2) || c2!='\n')
                {
                    colour_it("red");
                    printf("wrong input\n1)To go back press 1\n2)To save another save press 2 \n");
                    colour_it("white");
                    scanf("%d%c",&c1,&c2);
                    fflush(stdin);
                }
                if(c1==1 && counter!=0)
                {
                    save_flag=0;
                    system ("cls");
                    Printing_board();
                }
                else  //c1==2
                {
                    fseek(pointerreadsave,0,SEEK_SET);
                    colour_it("yellow");
                    while(i<counter_del-1)
                    {
                        fgets(temp2,11,pointerreadsave);
                        printf("%d}%s",i,temp2);
                        i++;
                    }
                    colour_it("green");
                    printf("Choose a save : \n");
                    colour_it("white");
                    scanf("%s",temp1);
                    fseek(pointerreadsave,0,SEEK_SET);
                    i=0;
                    while(i<counter_del-1)
                    {
                        fgets(temp2,11,pointerreadsave);
                        if(temp1==temp2)
                        {
                            i=counter_del;
                        }
                        i++;
                    }
                }
            }
            if(save_flag==1)
            {
                for(i=0;temp1[i]!='\0';i++)
                {
                  temp2[i]='\0';
                }
                for(i=0;temp1[i]!='\n';i++)
                {
                  temp2[i]=temp1[i];
                }
                pointerload = fopen(temp2,"r");
                counter_del=0;
                while(!feof(pointerload))
                {
                    fgets(temp1,11,pointerload);
                    counter_del++;
                }
                fseek(pointerload,0,SEEK_SET);
                i = 0;
                first_board_structure_undo();
                while(i < (counter_del-1))
                {
                    fgets(temp1,11,pointerload);
                    change_board_structure_for_load(temp1);
                    i++;
                }
                system("cls");
                Printing_board();
            }
        }
    }
}

void load_outside()
{
  int i=1,counter_del=1,c1=0,load_flag=1;
  char temp1[11]={'\0'};
  char temp2[11]={'\0'};
  char c2='\0';
  FILE * pointerreadsave;
  FILE * pointerload;
  pointerreadsave = fopen("345.txt","r");

    if(pointerreadsave==NULL)
    {
     system ("cls");
     colour_it("red");
     printf("Sorry, there are no loads\n\n");
     colour_it("white");
     fclose(pointerreadsave);
     Starting();
    }
    else
    {
        colour_it("green");
        printf("\nsaves are:\n");
        while(!feof(pointerreadsave))
        {
            fgets(temp2,11,pointerreadsave);
            counter_del++;
        }
        fseek(pointerreadsave,0,SEEK_SET);
        colour_it("yellow");
        while(i<counter_del-1)
        {
            fgets(temp2,11,pointerreadsave);
            printf("%d}%s",i,temp2);
            i++;
        }
        colour_it("green");
        printf("\nChoose a save:(TO GO BACK TO GAME<b>)\n");
        colour_it("white");
        gets(temp1);
        strcat(temp1,"\n");
        fseek(pointerreadsave,0,SEEK_SET);
        i=0;
        while(i<counter_del-1)
        {
            fgets(temp2,11,pointerreadsave);
            if((strcmp(temp1,temp2))==0)
            {
                load_flag=0;
                i=counter_del;
            }
            i++;
        }
        if(temp1[0]=='b' && counter==0)
        {
          Starting();
        }
        else if (temp1[0]=='b' && counter!=0)
        {
          NULL;
        }
        else
        {
            load_logo();
            save_flag = 1;
            while(load_flag==1 && save_flag==1)
            {
                save_flag=1;
                colour_it("red");
                printf("This save doesn't exist \n1)To go back press 1\n2)To load another save press 2 \n");
                colour_it("white");
                scanf("%d%c",&c1,&c2);
                fflush(stdin);
                while(!(c1==1 || c1==2) || c2!='\n')
                {
                    colour_it("red");
                    printf("wrong input\n1)To go back press 1\n2)To save another save press 2 \n");
                    colour_it("white");
                    scanf("%d%c",&c1,&c2);
                    fflush(stdin);
                }
                if(c1==1 && counter==0)
                {
                    save_flag=0;
                    system("cls");
                    //Starting();
                }
                else  //c1==2
                {
                    fseek(pointerreadsave,0,SEEK_SET);
                    while(i<counter_del-1)
                    {
                        fgets(temp2,11,pointerreadsave);
                        printf("%d}%s",i,temp2);
                        i++;
                    }
                    colour_it("green");
                    printf("Choose a save : \n");scanf("%s",temp1);
                    colour_it("white");
                    fseek(pointerreadsave,0,SEEK_SET);
                    i=0;
                    while(i<counter_del-1)
                    {
                        fgets(temp2,11,pointerreadsave);
                        if(temp1==temp2)
                        {
                            i=counter_del;
                        }
                        i++;
                    }
                }
            }
            if(save_flag==1)
            {
                for(i=0;temp1[i]!='\0';i++)
                {
                  temp2[i]='\0';
                }
                for(i=0;temp1[i]!='\n';i++)
                {
                  temp2[i]=temp1[i];
                }
                pointerload = fopen(temp2,"r");
                counter_del=0;
                while(!feof(pointerload))
                {
                    fgets(temp1,11,pointerload);
                    counter_del++;
                }
                fseek(pointerload,0,SEEK_SET);
                i = 0;
                first_board_structure_undo();
                while(i < (counter_del-1))
                {
                    fgets(temp1,11,pointerload);
                    change_board_structure_for_load(temp1);
                    i++;
                }
                system("cls");
                Printing_board();
            }
        }
    }
}

void change_board_structure_for_load (char inputafterload[11])
{
    int x1 = inputafterload[0] - 'A';
    int x2 = inputafterload[2] - 'A';
    int y1 = inputafterload[1] - '1';
    int y2 = inputafterload[3] - '1';
    if (inputafterload[4] != '\n')
        chess[x1][7-y1] = inputafterload[4];
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

void first_board_structure_undo()
{
    for(int j=0;j<8;j++)
    {
        for(int i=0;i<8;i++)
        {
            if((i+j)%2==0 && j!=1 && j!=6)
                chess[i][j]='.';
            else if(j==6)
                chess[i][j]='p';
            else if (j==1)
                chess[i][j] = 'P';
            else
                chess[i][j]='-';
        }
    }
    chess[0][0]='R';chess[1][0]='N';chess[2][0]='B';chess[3][0]='Q';chess[4][0]='K';chess[5][0]='B';chess[6][0]='N';chess[7][0]='R';
    chess[0][7]='r';chess[1][7]='n';chess[2][7]='b';chess[3][7]='q';chess[4][7]='k';chess[5][7]='b';chess[6][7]='n';chess[7][7]='r';
    for (int viper =0;viper<32;viper++)
    {
        dead[viper] = '\0';
    }
    w =0;
}

void undo()
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
  else if (counter==2)
  {
    fseek(pointerundo,0,SEEK_SET);
    fgets(tempu,11,pointerundo);
    fprintf(pointerredofile,tempu);
    first_board_structure();
    pointerestore=fopen("#####.txt","w");
    counter--;
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
    while(i<(counter_delu-2))
    {
        fgets(tempu,11,pointerundo);
        fprintf(pointertemp,tempu);
        change_board_structure_for_load(tempu);
        i++;
    }
    while(i<(counter_delu-1))
    {
     fgets(tempu,11,pointerundo);
     fprintf(pointerredofile,tempu);
     i++;
    }
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
  counter--;
  unrdo_counter++;
  fclose(pointerundo);
  fclose(pointerestore);
  fclose(pointerredofile);
  fclose(pointertemp);
  }
}

void redo()
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
    redotemp = fopen("temp.txt","w+");
    appendmain = fopen("#####.txt","a");
    fprintf(appendmain,tempr);
    fclose(appendmain);
    fseek(redo,0,SEEK_SET);
    while(i<counter_delr-2)
    {
        fgets(tempr,11,redo);
        fprintf(redotemp,tempr);
        i++;
    }
    i=0;
    fseek(redotemp,0,SEEK_SET);
    redorestore = fopen("redofile.txt","w+");
    while(i<counter_delr-2)
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
    counter++;
    }
}

void colour_it (char color[11])
{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole,&consoleInfo);

   if(color[0]=='r')
   {
      SetConsoleTextAttribute(hConsole,12);
   }
    if(color[0]=='w')
   {
       SetConsoleTextAttribute(hConsole,15);
   }
    if(color[0]=='b')
   {
       SetConsoleTextAttribute(hConsole,9);
   }
    if(color[0]=='y')
   {
       SetConsoleTextAttribute(hConsole,14);
   }
    if(color[0]=='g')
   {
       SetConsoleTextAttribute(hConsole,10);
   }
}

void delay ()
{
   double i=0;
   for(i=0;i<100000000;i++)
   {
     NULL;
   }
}

void load_logo()
{
    for(int i=0;i<2;i++)
    {
        printf("                                                    loading ");printf("*...");delay ();system("cls");
        colour_it("red");
        printf("                                                    loading ");printf(".*..");delay();system("cls");
        colour_it("yellow");
        printf("                                                    loading ");printf("..*.");delay ();system("cls");
        colour_it("blue");
        printf("                                                    loading ");printf("...*");delay ();system("cls");
        colour_it("red");
        printf("                                                    loading ");printf("..*.");delay ();system("cls");
        colour_it("green");
        printf("                                                    loading ");printf(".*..");delay();system("cls");
    }
}
