#include <stdio.h>

void printboard(int board[9]){
    printf("\n");
    printf("%c|%c|%c\n", board[0], board[1], board[2]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n", board[3], board[4], board[5]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n", board[6], board[7], board[8]);
}

void setup(int *board){
    for(int i = 0; i<9; i++){
        board[i] = ' ';
    }
}

void win(int player, int board[9]){
    printboard(board);
    printf("Player %d is the winner!\n", player);
}

void setplayer(int count, int *sign, int *player){
    if(count % 2 == 0){
        *sign = 'X';
        *player = 1;
    }else{
        *sign = 'O';
        *player = 2;
    }
    printf("Player %d's turn.", *player);
}

void getinput(int *index, int *board, int *sign, int *count){
    scanf("%d", index);
    if(*index < 1 || *index > 9){
        printf("Allowed index is 1-9.\n");
    }else if(board[(*index)-1] == 'X' || board[(*index)-1] == 'O'){
        printf("That spot is already taken.\n");
    }else{
        board[(*index) - 1] = *sign;
        (*count)++;
    }
}

void checkrow (int *board, int *sign, int *winner, int player){
    int flag = 0;
    for(int i = 0; i < 9; i++){
        if(i % 3 == 0){
            flag = 0;
        }
        if(board[i] == *sign){
            flag++;
        }
        if(flag == 3){
            *winner = 1;
            return;
        }
    }
}

void checkcol (int *board, int *sign, int *winner, int player){
    int flag = 0;
    for(int i = 0; i<3; i++){
        for(int k=i; k<= i+6; k += 3){
            if (board[k] == *sign){
                flag++;
            }
            if(flag == 3){
                *winner = 1;
                return;
            }
            flag = 0;
        }
    }
}

void checkdiagonal(int *board, int *sign, int *winner, int player){
    if(board[0] == *sign && board[4] == *sign && board[8] == *sign ||
        board[2] == *sign && board[4] == *sign && board[6] == *sign){
            *winner = 1;
    }
}

int checkwin(int *board, int *sign, int player){
    int winner = 0;
    
    checkrow(board, sign, &winner, player);
    if(winner)
        return winner;
    checkcol(board, sign, &winner, player);
    if(winner)
        return winner;
    checkdiagonal(board, sign, &winner, player);

    return winner;
}

void draw(int *board){
    printf("Its a draw.");
    printboard(board);
}

void play(int *count, int *winner, int *board){
    int index, sign, player, i, j, k;
    printboard(board);
    setplayer(*count, &sign, &player);
    getinput(&index, board, &sign, count);

    *winner = checkwin(board, &sign, player);
    if(*winner)
        win(player, board);
    
}

int isplaying(int count, int winner){
    return (count < 9 && !winner);
}

int main(){
    int winner = 0, count = 0;
    int board[9];

    setup(board);

    while(isplaying(count, winner))
        play(&count, &winner, board);

    if(!winner)
        draw();
    
}