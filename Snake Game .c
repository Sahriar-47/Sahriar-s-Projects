#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int height = 20, width = 20;
int x, y, fruitx, fruity, gameover, Score, MAX_Score, flag;
int tailx[200], taily[200], counttail = 0;

void setup()
{
    gameover = 0;
    x = height/2;
    y = width/2;

level1:
    fruitx = rand()%20;
    if(fruitx == 0)
        goto level1;

level2:
    fruity = rand()%20;
    if(fruity == 0)
        goto level2;

    Score = 0;
    MAX_Score=0;
}

void draw()
{
    system("cls");
    printf("\nScore = %d\n",Score);
    printf("\npress x to quit the game:\n\n");

    for( int i=0; i<width; i++ )
    {
        for( int j=0; j<height; j++ )
        {
            if( i==0 || i==width-1 )
                printf("-");
            else if( j==0 || j==height-1 )
                printf("|");
            else
            {
                if( i==x && j==y )
                    printf("0");
                else if( i==fruitx && j==fruity )
                {
                    printf("*");
                }
                else
                {
                    int c = 0;
                    for( int k=0; k<counttail; k++ )
                    {
                        if( i==tailx[k] && j==taily[k] )
                        {
                            printf("o");
                            c = 1;
                        }
                    }
                    if( c==0 )
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
    if(gameover==1)
    {
        printf("\nGAME OVER!\n\n");
        printf("TOTAL Score: %d\n",Score);
    }
}

void input()
{
    if(kbhit())
    {
        switch(getch())
        {
        case 'a':
            flag=1;
            break;
        case 's':
            flag=2;
            break;
        case 'w':
            flag=3;
            break;
        case 'z':
            flag=4;
            break;
        case 'x':
            gameover=1;
            break;
        }
    }
}

void makelogic()
{
    int prevx, prevy, prev2x, prev2y;
    prevx = tailx[0];
    prevy = taily[0];
    tailx[0] = x;
    taily[0] = y;
    for( int i=1; i<counttail; i++ )
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    switch(flag)
    {
    case 1:
        y--;
        break;
    case 2:
        y++;
        break;
    case 3:
        x--;
        break;
    case 4:
        x++;
        break;
    default:
        break;
    }

    if( x<1 || x>width-2 || y<1 || y>height-2 )
        gameover=1;

    if( x==fruitx && y==fruity )
    {
level3:
        fruitx = rand()%20;
        if( fruitx==0 )
            goto level3;

level4:
        fruity = rand()%20;
        if( fruity==0 )
            goto level4;

        Score+=10;
        counttail++;
    }
}

int main()
{
    setup();
    while(!gameover)
    {
        for( int m=1; m<10000; m++ )
            for( int n=1; n<10000; n++ )
            {

            }
        makelogic();
        draw();
        input();
    }

    FILE *fptr = NULL;
    fptr = fopen("Snake_Game_DATA.txt","a");
    if( fptr == NULL )
    {
        printf("NO FILE HERE!\n");
        exit(1);
    }

    if(Score>MAX_Score)
    {
        MAX_Score=Score;

        fprintf(fptr, "MAX_Score: %d\n ",MAX_Score);
    }
    fclose(fptr);
}
