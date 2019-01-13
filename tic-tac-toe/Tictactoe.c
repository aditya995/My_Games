#include<stdio.h>
#include <time.h>
char a[9]={'1','2','3','4','5','6','7','8','9'};

//Randomizes the Value using time variables

float measureTime(clock_t start, clock_t end){

    float totalSeconds;

    totalSeconds = ((long double)(end - start))/CLOCKS_PER_SEC;

    return(totalSeconds);
}

//Draws the screen

void draw(){
    int i;
    for(i=0;i<9;i+=3){
        printf("____________\n %c || %c || %c \n____________\n",a[i],a[i+1],a[i+2]);
    }
}

//Checks for the winning or losing conditions

int checker(char c){
    if(a[0]==c&&a[1]==c&&a[2]==c){
        return 1;
    }else if(a[6]==c&&a[7]==c&&a[8]==c){
        return 1;
    }else if(a[3]==c&&a[4]==c&&a[5]==c){
        return 1;
    }else if(a[0]==c&&a[3]==c&&a[6]==c){
        return 1;
    }else if(a[0]==c&&a[4]==c&&a[8]==c){
        return 1;
    }else if(a[2]==c&&a[4]==c&&a[6]==c){
        return 1;
    }else if(a[2]==c&&a[5]==c&&a[8]==c){
        return 1;
    }else{
        return 0;
    }
}
int main(){
    int n,i = 0,j,k=0,m = 0,input[9]={1,2,3,4,5,6,7,8,9};
    clock_t start, end;
    start = clock();
    draw();

//Game loop starts

    for(i=0;i<7;i+=2){

//Taking input

        printf("\nGive your choice :\n");
        scanf("%d",&n);
        while(a[n-1]=='x'||a[n-1]=='0'){
            printf("This block is occupied!!\nTry another one.\n");
            scanf("%d",&n);
        }

//Assigning the users input

        a[n-1]='x';
        system("cls");
        draw();

//Checking for if the player win or not

        if(checker('x')==1){
            k = 1;
            printf("\nYou win !!\n");
            break;
        }

//The randomized input for the computer

        end = clock();
        j=measureTime(start, end);
        m=(j*rand())%9;
        for(;a[m]=='x'||a[m]=='0';){
            m=rand()%8;
        }

//Assigning the computer's input

        a[m]='0';
        system("cls");
        draw();

//Checking for if the player lose or not

        if(checker('0')==1){
            k = 1;
            printf("\nYou lose !!\n");
            break;
        }
    }

//Game loop ends

    if(k == 0){
        printf("\nMatch draw!!\n");
    }
    return 0;
}
