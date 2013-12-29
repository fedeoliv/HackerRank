#include<stdio.h>
#include<stdlib.h>
/* Head ends here */
void next_move(int posx, int posy, int dimx, int dimy, char board[50][50]) {
    if (board[posx][posy] == 'd')
        printf("CLEAN");
    else{
        int k, m, min_dist = 100;

        for (int i = 0; i < dimx; i++)
            for (int j = 0; j < dimy; j++)
                if (board[i][j] == 'd' && (abs(i - posx) + abs(j - posy)) < min_dist){
                    k = i;
                    m = j;
                    min_dist = abs(i - posx) + abs(j - posy);
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
    int pos[2], dim[2], i;
    char board[50][50];
    scanf("%d", &pos[0]);
    scanf("%d", &pos[1]);
    scanf("%d", &dim[0]);
    scanf("%d", &dim[1]);
    for(i=0; i<dim[0]; i++) {
        scanf("%s[^\\n]%*c", board[i]);
    }
    next_move(pos[0], pos[1],dim[0],dim[1], board);
    return 0;
}
