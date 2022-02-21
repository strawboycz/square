#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include <windows.h>
#define LENGTH 45
#define WIDTH 166
#define WALL 219
#define PLAYER 254
#define PLAYER_UP 223
#define PLAYER_DOWN 220
#define JUMP_HEIGHT 4
void map_print(char map[][LENGTH], int player_pos[]);

int main(){
    CONSOLE_SCREEN_BUFFER_INFO info = {0};
    int width, height;
    HANDLE hConsole = NULL;
    ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);

    int player_pos[] = {WIDTH/2, LENGTH-2};
    int velocity_up = 0;
    char map[WIDTH][LENGTH] = {};
    for(int y=0; y<LENGTH; y++){
        for(int x = 0; x < WIDTH; x++){
            if(y==0||y==LENGTH-1){
                map[x][y] = WALL;
            }
            else if(x==0 || x==1 ||x==WIDTH-1|| x==WIDTH-2){
                map[x][y] = WALL;
            }
            else if(y==player_pos[1]&&x==player_pos[0]){
                map[x][y] = PLAYER;
            }
        }
    }
    system("cls");
    map_print(map, player_pos);
    while(1){
            if(velocity_up>JUMP_HEIGHT){
                velocity_up--;
                map[player_pos[0]][player_pos[1]] = '\0';
                player_pos[1]--;
            }
            else if(velocity_up > 0){
                velocity_up--;
                map[player_pos[0]][player_pos[1]] = '\0';
                player_pos[1]++;
            }
        if(_kbhit()) {
            switch(_getch()) {
            case 'w':
                if(player_pos[1]==1){
                    continue;
                }
                if(velocity_up > 0){
                    break;
                }
                if(velocity_up==0){
                    velocity_up=JUMP_HEIGHT*2;
                }
                map[player_pos[0]][player_pos[1]] = '\0';
                velocity_up--;
                player_pos[1]--;
                break;
            case 'a':
                if(player_pos[0]==2){
                    continue;
                }
                map[player_pos[0]][player_pos[1]] = '\0';
                player_pos[0]--;
                break;
            case 's':
                if(player_pos[1]==LENGTH-2){
                    continue;
                }
                if(velocity_up > 0){
                    break;
                }
                map[player_pos[0]][player_pos[1]] = '\0';
                player_pos[1]++;
                break;
            case 'd':
                if(player_pos[0]==WIDTH-3){
                    continue;
                }
                map[player_pos[0]][player_pos[1]] = '\0';
                player_pos[0]++;
                break;
            }

        }
        system("cls");
        map_print(map, player_pos);
    }

    return 0;
}

void map_print(char map[][LENGTH], int player_pos[]) {
    char string[WIDTH*LENGTH + 1 + LENGTH];

    for(int i = 0; i < LENGTH; i++) {
        for(int j = 0; j < WIDTH; j++) {
            if(j==player_pos[0]&&i==player_pos[1]){
                if(map[j][i-1] == (char)WALL) {
                    map[j][i] = PLAYER_UP;
                }
                else if(map[j][i+1] == (char)WALL) {
                    map[j][i] = PLAYER_DOWN;
                }
                else {
                    map[j][i] = PLAYER;
                }
            }
            if(map[j][i] == 0) {
                string[i*(WIDTH + 1) + j] = ' ';
            }else {
                string[i*(WIDTH + 1) + j] = map[j][i];
            }
        }
        string[i*(WIDTH + 1) + WIDTH] = '\n';
    }
    string[WIDTH*LENGTH + LENGTH] = '\0';

    printf("%s", string);
}
