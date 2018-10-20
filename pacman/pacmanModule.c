#define UPARROW     72
#define DOWNARROW   80
#define LEFTARROW   75
#define RIGHTARROW  77
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//Global variables

int character[2] = { 1, 1 };
char state[15] = { ' ', '>', 177, 177, '#', 248,'<','v','^'};
int tile[25][80],count=0,cou1=0,cou2=0;
int a=-1;

//Measures the game speed

float measureTime(clock_t start, clock_t end){
    float totalSeconds;
    totalSeconds = ((long double)(end - start))/CLOCKS_PER_SEC;
    return(totalSeconds);
}

//The array position updates this function

void updatePlayer(char direction) {
    switch(direction) {
       case 'W':
         if(tile[character[0]-1][character[1]] == 5) {
           tile[character[0]-1][character[1]] = 0;
           count++;
         }
         if(character[0] > 0 && tile[character[0]-1][character[1]] == 0) {
            tile[character[0]][character[1]] = 0;
            character[0]--;
            tile[character[0]][character[1]] = 8;
         }
       break;
       case 'A':
         if(tile[character[0]][character[1]-1] == 5) {
           tile[character[0]][character[1]-1] = 0;
           count++;
         }
         if(character[1] > 0 && tile[character[0]][character[1]-1] == 0) {
            tile[character[0]][character[1]] = 0;
            character[1]--;
            tile[character[0]][character[1]] = 6;
         }
       break;
       case 'S':
         if(tile[character[0]+1][character[1]] == 5) {
           tile[character[0]+1][character[1]] = 0;
           count++;
         }
         if(character[0] < 23 && tile[character[0]+1][character[1]] == 0) {
           tile[character[0]][character[1]] = 0;
           character[0]++;
           tile[character[0]][character[1]] = 7;
         }
       break;
       case 'D':
           if(tile[character[0]][character[1]+1] == 5) {
           tile[character[0]][character[1]+1] = 0;
           count++;
         }
         if(character[1] < 79 && tile[character[0]][character[1]+1] == 0) {
           tile[character[0]][character[1]] = 0;
           character[1]++;
           tile[character[0]][character[1]] = 1;
           }
       break;

    }
}

//the screen is drawn using this function

void drawScreen() {
    system("cls");
    int i, j;
    printf("Score --> %d     level--> %d\n'W', 'A', 'S', 'D' to move.'R' to Restart, 'X' to Exit.\n\n\nDon't hit the walls !!\n\n\n",cou2+count,a+1);
    printf("Cordinates of the PacMan (X,Y)(%d, %d)\n",character[0],character[1]);
    for(j=0; j < 15; j++) {
        for(i=0; i < 30; i++) {
            printf("%c", state[tile[j][i]]);
        }printf("\n");
    }
}

//Levels are fetched from here

int level(int n){
    FILE *fp[4];
    char ch[4][25]={"levels//1.txt","levels//2.txt","levels//3.txt","levels//4.txt"};
    fp[n]=fopen(ch[n],"r");
    int k,l;
    for(k=0;k<15;k++){
        for(l=0;l<30;l++){
            fscanf(fp[n],"%d",&tile[k][l]);
        }
    }
    fclose(fp[n]);
    return n;
}

int main(){

// For the input behavior console mode changed

    DWORD        mode;
    HANDLE       hstdin;
    hstdin = GetStdHandle( STD_INPUT_HANDLE );
    GetConsoleMode( hstdin, &mode );

//The input variables

    char input='D',in;
    float i,j;
    int r1,r2,lvs[4]={3,3,3,3};
    r1=r2=1;
    clock_t start, end;

//Game screen for the first time

    printf("The pacMan prototype.\n\nChoose your level !!");
    while(a<1||a>4){
        printf("\nLevel (1), (2) ,(3) ,(4) are available only !!\n\n");
        scanf("%d",&a);
    }
    level(--a);
    drawScreen();
    start = clock();

//Game loop starts here

    do{

//Checking for Restart game or Restart level

        if(input=='R'||(r1==0)&&(r2==0)){
            system("cls");
            printf("\nPress (1) & hit ENTER to Restart level?\nPress (2) & hit ENTER to Restart Game ?\n\nTo quit Game press (X) & hit ENTER !\n");
            input=getchar();
            for(;input!='1'&&input!='2'&&input!='X'&&input!='x';){
                input=getchar();
            }
            if(input=='1'){
                count=0;
                level(a);input='D';
            }else if(input=='2'){
                printf("The pacMan prototype.\n\nChoose your level!!\n");
                scanf("%d",&a);
                while(a<1||a>4){
                printf("\nLevel (1), (2) ,(3) ,(4) are available only !!\n\n");
                scanf("%d",&a);
                }
                count=0;
                cou2=0;
                level(--a);input='D';
            }else{
                break;
            }
            character[0]=1;
            character[1]=1;
        }

//Checking for level completion

        if(count==lvs[a]){
            cou1=1;
            cou2+=count;
            count=0;
        }
        if(cou1==1){
            character[0]=1;
            character[1]=1;
            input='D';
            a++;
            if(a==4){
                break;
            }
            level(a);
        }
        cou1=0;

//controls the game speed

        i=j=0;
        for(;j<.6;i++){
            end = clock();
            j=measureTime(start, end);
        }start=end;

//taking input

        while(kbhit()){
            SetConsoleMode( hstdin, 0 );
            in =getchar();
            in=toupper((int)in);
            if(in=='D'||in=='A'||in=='S'||in=='W'||in=='X'||in=='R'){
                input=in;
                input = toupper((int)input);
            }
        }

//Collision detection mechanism

        r1=character[0];
        r2=character[1];
        updatePlayer(input);
        r1=character[0]-r1;
        r2=character[1]-r2;
        drawScreen();
    }while(input != 'X');
    system("cls");
    printf("Thanks for playing the Game :)\nYour Score is %d\n",cou2+count);
    return 0;
}
