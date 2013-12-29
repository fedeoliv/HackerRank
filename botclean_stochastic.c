#include<stdio.h>
#include<string.h>
/* Head ends here */
void nextMove(int posx, int posy, char board[5][5]) {
    if (board[posx][posy] == 'd')
        printf("CLEAN");
    else{
        int k, m;

        for (k = 0; k < 5; k++){
            for (m = 0; m < 5; m++)
                if (board[k][m] == 'd')
                    break;
            if(m != 5)
                break;
        }

        if (m < posy)
            printf("LEFT");
        else if (m > posy)
            printf("RIGHT");
        else if (k != posx)
            printf((k < posx) ? "UP" : "DOWN");
    }
}
/* Tail starts here */
int main(void) {
    int pos[2], i;
    char board[5][5];
    char line[5];
    scanf("%d", &pos[0]);
    scanf("%d", &pos[1]);
    for(i=0; i<5; i++) {
        scanf("%s", line);
        strncpy(board[i], line, 5);
    }
    nextMove(pos[0], pos[1], board);
    return 0;
}
