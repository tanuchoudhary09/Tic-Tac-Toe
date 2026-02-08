/*mini group project for end sem
project topic: tic tac toe game
team members
Laxmikant - 125cs0050
Abdulla - 125cs0040
Asim - 125ad0037
Tanu - 125ec0045
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char board[3][3];

void initialboard(){
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            board[i][j]=' ';
            
        }
    }
}



void printboard(){

    printf("\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int c=i*3+1+j;
            if(board[i][j]==' ')
               printf(" %d ",c);
            else
               printf(" %c ",board[i][j]);
            if(j<2)printf("|");
    }
     printf("\n");
     if(i<2)printf("---+---+---\n");
    
    }
}



char checkwin(){
    
    for(int i=0;i<3;i++){
        if(board[i][0]!=' ' && board[i][1]==board[i][0] && board[i][2]==board[i][0])
        return board[i][0];
        if(board[0][i]!=' ' && board[1][i]==board[0][i] && board[2][i]==board[0][i])
        return board[0][i];
    }
    if(board[0][0]!=' ' && board[1][1]==board[0][0] && board[2][2]==board[1][1])
    return board[0][0];
    if(board[0][2]!=' ' && board[1][1]==board[0][2] && board[2][0]==board[1][1])
    return board[0][2];

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' ')
            return ' ';
        }  
    }
    return 'D';
    
}



int minimax(char ai,char cu_pl,int dep){
    char res=checkwin();
    if(res==ai)return 10-dep;
    else if(res=='D')return 0;
    else if(res!=' '&& res!=ai)return dep-10;

    if(cu_pl==ai){
        int best=-1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==' '){
                    board[i][j]=cu_pl;
                    int score=minimax(ai,(cu_pl=='X')?'O':'X',dep+1);
                    board[i][j]=' ';
                    if(score>best)
                       best=score;
                }
            }
        }
        return best;
    }else{
        int best=1000;
         for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==' '){
                    board[i][j]=cu_pl;
                    int score=minimax(ai,(cu_pl=='X')?'O':'X',dep+1);
                    board[i][j]=' ';
                    if(score<best)
                       best=score;
                }
            }
    }
    return best;
}
}



void findwinmove(char ai,int *rr,int *cc){
    int bestval=-1000;
    *rr=-1,*cc=-1;
     for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==' '){
                    board[i][j]=ai;
                    int curval=minimax(ai,(ai=='X')?'O':'X',0);
                    board[i][j]=' ';
                    if(curval>bestval){
                       bestval=curval;
                       *rr=i;
                       *cc=j;
                    }
                }
            }
        }
}



int hum_mov(int pla){
    int cell;
    printf("player %c turn\n",pla);
    printf("enter cell no : ");
    if(scanf("%d",&cell)!=1){
        while(getchar()!='\n');
        printf("invalid input.Try again\n");
       
        return 0;
    }
    if(cell<1||cell>9){
        printf("cell must be 1 to 9\n");
       
        return 0;
    }

    int r=(cell-1)/3;
    int c=(cell-1)%3;
    if(board[r][c]!=' '){
        printf("cell already taken.Try again\n");
        
        
        return 0;
    }
    board[r][c]=pla;
    return 1;
}



void pvp(){
    initialboard();
    char cur='X';
    while(1){
        printboard();
        while(hum_mov(cur)!=1){};
        int res=checkwin();
        if(res=='X'||res=='O'){
        printboard();    
        printf("player %c wins!\n",res);
        return;
        }
        else if(res=='D'){
            printboard();
            printf("It's a DRAW!!\n");
            return;
        }
        cur=(cur=='X')?'O':'X';
    }
}



void random_move(int *rr,int *cc){
    int empties[9][2];
    int cnt =0;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' '){
                empties[cnt][0]=i;
                empties[cnt][1]=j;
                cnt++;
            }
        }
    }
    if(cnt==0){
        *rr=-1;
        *cc=-1;
        return;
    }
    int index = rand()%cnt;
    *rr=empties[index][0];
    *cc=empties[index][1];
}




void plavai(char pla, char ai, char str){

    initialboard();
    char cur = str;

    int level;
    printf("\nChoose AI difficulty:\n");
    printf("1) Easy\n2) Medium\n3) Hard\nEnter level: ");
    scanf("%d", &level);

    if(level<1 || level>3){
        printf("invalid input !\n defaul to hard mode");
        level=3;
    }

    while(1){
        printboard();

        if(cur == pla){
            while(hum_mov(cur) != 1){}
        } 
        else {
            printf("AI is thinking ...\n");

            int r = -1, c = -1;

            if(level == 1){
                // EASY → totally random move
                random_move(&r, &c);
                printf("AI chooses it's move...\n");
            }
            else if(level == 2){
                // MEDIUM → 60% random, 40% minimax
                int chance = rand() % 100;
                if(chance < 60){
                    findwinmove(ai,&r, &c);
                    printf("AI chooses it's move...\n");
                } else {
                    random_move( &r, &c);
                    printf("AI chooses it's move...\n");
                }
            }
            else { 
                // HARD → always minimax
                findwinmove(ai, &r, &c);
                printf("AI chooses it's move...\n");
            }

            board[r][c] = ai;
            printf("AI moved in cell : %d\n\n", r*3 + 1 + c);
        }

        char res = checkwin();

        if(res == ai){
            printboard();
            printf("AI wins!!!\n");
            return;
        }
        else if(res == pla){
            printboard();
            printf("Player wins!!!\n");
            return;
        }
        else if(res == 'D'){
            printboard();
            printf("It's a draw!!!\n");
            return;
        }

        cur = (cur=='X') ? 'O' : 'X';
    }
}



int main(){

    srand(time(NULL));
   printf("Tic-Tac-Toe\n");
   printf("1)player vs player\n");
   printf("2)player vs AI\n");

   printf("chose mode (1) or (2) : ");
   int mode;
   if(scanf("%d",&mode)!=1){
    printf("invalid input\n exiting\n");
    return 0;
   }

   if(mode==1){
    printf("starting player vs player...\n\n");
    printf("player 1 is X and player 2 is O\n\n");
    pvp();
   }else if(mode==2){
    char humplayer,aiplayer,starter;
    int choice;
    printf("do you want to play as X or O?\nenter 1 for X and 2 for O : ");
    if(scanf("%d",&choice)!=1){
        printf("invalid input \n exiting\n");
        return 0;
    }

    if(choice==1){
        humplayer='X';
        aiplayer='O';
    }else if(choice==2){
        humplayer='O';
        aiplayer='X';
    }else{
        printf("entering default mode you are X and ai is O\n");
        humplayer='X';
        aiplayer='O';
    }

    printf("who will go first ?\n (1)-you (%c) \n (2)-AI (%c).\nenter 1 or 2 : ",humplayer,aiplayer);
    if(scanf("%d",&choice)!=1){
        printf("invalid input\nexiting ");
        return 0;
    }
    if(choice<1||choice>2){
        printf("entering default mode ai will go first!\n");
        choice=2;
    }

    starter=(choice==1)?humplayer:aiplayer;

    printf("starting player vs AI....\n you are %c and ai is %c",humplayer,aiplayer);
    plavai(humplayer,aiplayer,starter);

   }else{
    printf("unmkown mode\nexiting...");
    return 0;
   }

    printf("\nPress Enter to exit...");
    getchar();
    getchar();

return 0;
}