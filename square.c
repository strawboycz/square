#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include <windows.h>
#define LENGTH 25//45
#define WIDTH 60//166
#define WALL (char)219
#define LAVA (char)177
#define PLAYER (char)254
#define PLAYER_UP (char)223
#define PLAYER_DOWN (char)220
#define JUMP_HEIGHT 4
#define PRINT_CHARACTERS for(int i=0;i<=255;i++) printf("\n%d.\t%c",i,(char)i);  system("pause");
char map[WIDTH][LENGTH] = {};
int player_pos[2];
int (*platforms)[4];
void platform_make(int start_x, int start_y, int end_x, int end_y);
void map_print();
void game_over();
void level_load(int level);
int main(){
    // full screen
    CONSOLE_SCREEN_BUFFER_INFO info = {0};
    int width, height;
    HANDLE hConsole = NULL;
    ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
    //PRINT_CHARACTERS; // vypis vsech znaku
    //promenne :)
    int current_level = 0;
    _Bool just_landed = 0;
    int velocity_up = 0;
    // naplneni map (pozdeji funkce)
    level_load(current_level);
    //vypis
    system("cls");
    map_print();
    //GAME LOOP
    while(1){
        // checkuje jestli je nad hracem zed
        if(map[player_pos[0]][player_pos[1]-1] == WALL){
            velocity_up = 0;
        }
        // checkuje jestli je pod hracem zed
        if(map[player_pos[0]][player_pos[1]+1] == WALL){
            velocity_up = 0;
        }
        //skok
        if(velocity_up > 0){
            velocity_up--;
            map[player_pos[0]][player_pos[1]] = '\0';
            player_pos[1]--;
        }
        // gravitace
        else if(map[player_pos[0]][player_pos[1]+1] != WALL){
            map[player_pos[0]][player_pos[1]] = '\0';
            player_pos[1]++;
            just_landed = 1;
        }
        else{
            just_landed = 0;
        }
        // user input
        if(_kbhit()) {
            switch(_getch()) {
            case 'w':
                //checkuje jestli je hrac ve skoku/pada (jestli muze vyskocit)
                if(velocity_up > 0 || map[player_pos[0]][player_pos[1]+1] != WALL || just_landed){
                    break;
                }
                //zacina skok
                velocity_up=JUMP_HEIGHT-1;
                map[player_pos[0]][player_pos[1]] = '\0';
                player_pos[1]--;
                break;
            case 'a':
                //checkuje jestli je vedle hrace zed
                if(map[player_pos[0]-1][player_pos[1]] == WALL){
                    break;
                }
                map[player_pos[0]][player_pos[1]] = '\0';
                player_pos[0]--;
                break;
            case 'd':
                //checkuje jestli je vedle hrace zed
                if(map[player_pos[0]+1][player_pos[1]] == WALL){
                    break;
                }
                map[player_pos[0]][player_pos[1]] = '\0';
                player_pos[0]++;
                break;
                case 'r':
                    level_load(current_level);
                    map_print();
                break;
                case ';':
                    return 0;
            }
                }





        //vypis
        //sleep(1);
        if(map[player_pos[0]][player_pos[1]]==LAVA){
            game_over();
            return 0;
        }
        Sleep(20);
        map_print();
    }

    return 0;
}

void map_print() {
    char string[WIDTH*LENGTH + 1 + LENGTH];
    //konverze mapy do stringu NEMENIT
    for(int i = 0; i < LENGTH; i++) {
        for(int j = 0; j < WIDTH; j++) {
            if(j==player_pos[0]&&i==player_pos[1]){
                if(map[j][i-1] == WALL) {
                    map[j][i] = PLAYER_UP;
                }
                else if(map[j][i+1] == WALL) {
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

    //system("cls");
    Sleep(50);
    printf("%s", string);
}
void game_over(){
    printf("\a");
    system("color 4");
    Sleep(125);
    system("color f");
    Sleep(250);
    system("cls");
    printf("\n   _____          __  __ ______         ______      ________ _____");
    printf("\n  / ____|   /\\   |  \\/  |  ____|       / __ \\ \\    / /  ____|  __ \\");
    printf("\n | |  __   /  \\  | \\  / | |__         | |  | \\ \\  / /| |__  | |__) |");
    printf("\n | | |_ | / /\\ \\ | |\\/| |  __|        | |  | |\\ \\/ / |  __| |  _  /");
    printf("\n | |__| |/ ____ \\| |  | | |____       | |__| | \\  /  | |____| | \\ \\");
    printf("\n  \\_____/_/    \\_\\_|  |_|______|       \\____/   \\/   |______|_|  \\_\\");
    Sleep(1000);
    printf("\t");
    system("pause");
}
void level_load(int level){
    int number_of_platforms;
    map[player_pos[0]][player_pos[1]] = '\0';
    switch(level){
    case 0 :
        player_pos[0] = WIDTH/2;
        player_pos[1] = LENGTH - 2;
        number_of_platforms = 3;
        /*if((platforms = (int(*)[4])malloc(sizeof(int)*number_of_platforms*4)) == NULL) {
            return -6;
        }*/
        for(int y=0; y<LENGTH; y++){
            for(int x = 0; x < WIDTH; x++){
                if((y==0||y==LENGTH-1)||(x==0 || x==1 ||x==WIDTH-1|| x==WIDTH-2)){
                    map[x][y] = WALL;
                }
                else if(x==player_pos[0]&&y==player_pos[1]){
                    map[x][y] = PLAYER;
                }
                else if(x<80 && x>20 && y == LENGTH - 4){
                    map[x][y] = WALL;
                }
                else if(x>40 && x<60 && y == LENGTH - 2){
                    map[x][y] = LAVA;
                }
            }
        }
        /*free(platforms);
        platforms = NULL;*/
        break;
    case 1 :
        player_pos[0] = WIDTH/2;
        player_pos[1] = LENGTH - 2;
        for(int y=0; y<LENGTH; y++){
            for(int x = 0; x < WIDTH; x++){
                if((y==0||y==LENGTH-1)||(x==0 || x==1 ||x==WIDTH-1|| x==WIDTH-2)){
                    map[x][y] = WALL;
                }
                else if(x==player_pos[0]&&y==player_pos[1]){
                    map[x][y] = PLAYER;
                }
                else if(x<80 && x>20 && y == LENGTH - 4){
                    map[x][y] = WALL;
                }
                else if(x>120 && x<150 && y == LENGTH - 2){
                    map[x][y] = LAVA;
                }
            }
        }
        break;
    case 2 :
        break;
    case 3 :
        break;
    case 4 :
        break;
    case 5 :
        break;
    case 6 :
        break;

    }

}
