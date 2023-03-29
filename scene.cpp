#include "scene.h"

ALLEGRO_FONT *font = NULL,*font1 =NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *background_about1 = NULL;
ALLEGRO_BITMAP *background_about2 = NULL;
ALLEGRO_BITMAP *background_count = NULL;
ALLEGRO_BITMAP *background_sand = NULL;
ALLEGRO_BITMAP *ht = NULL;
ALLEGRO_BITMAP *award = NULL;
char time_game[5]={'0','2',':','0','0'};
int countdown=7259;
// function of menu
void menu_init(){
    font = al_load_ttf_font("./font/bdfef6884a8c1500.ttf",80,0);
    font1 = al_load_ttf_font("./font/bdfef6884a8c1500.ttf",130,0);
    background=al_load_bitmap("./image/2.jpg");
}
void menu_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) //Start -> 選場地
        if( event.mouse.x >= (WIDTH/2)-180 && event.mouse.y >=(HEIGHT/2)-30 && event.mouse.x <= (WIDTH/2)+180 && event.mouse.y <=(HEIGHT/2)+50)
            judge_next_window = true;
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) //about -> 遊戲介紹
        if( event.mouse.x >= (WIDTH/2)-180 && event.mouse.y >=(HEIGHT/2)+100 && event.mouse.x <= (WIDTH/2)+180 && event.mouse.y <=(HEIGHT/2)+180){
            win=6;
            judge_next_window = true;
        }
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) //Exit -> 關遊戲
        if( event.mouse.x >= (WIDTH/2)-180 && event.mouse.y >=(HEIGHT/2)+230 && event.mouse.x <= (WIDTH/2)+180 && event.mouse.y <=(HEIGHT/2)+310){
            printf("Don't give up ! Bro\n");
            game_destroy();
        }
}
void menu_draw(){
    al_draw_bitmap(background,0,0,0);
    al_draw_text(font1, al_map_rgb(80,0,255), (WIDTH/2), (HEIGHT/2)-300 , ALLEGRO_ALIGN_CENTRE, "Hockey wars");     //背景圖片
    al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2), (HEIGHT/2)-30 , ALLEGRO_ALIGN_CENTRE, "start");
    al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2), (HEIGHT/2)+100 , ALLEGRO_ALIGN_CENTRE, "about");
    al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2), (HEIGHT/2)+230 , ALLEGRO_ALIGN_CENTRE, "exit");
    //al_draw_rectangle((WIDTH/2)-180,(HEIGHT/2)-30,(WIDTH/2)+180,(HEIGHT/2)+50,al_map_rgb(255,255,255),1);
    //al_draw_rectangle((WIDTH/2)-180,(HEIGHT/2)+100,(WIDTH/2)+180,(HEIGHT/2)+180,al_map_rgb(255,255,255),1);
    //al_draw_rectangle((WIDTH/2)-180,(HEIGHT/2)+230,(WIDTH/2)+180,(HEIGHT/2)+310,al_map_rgb(255,255,255),1);
}
void menu_destroy(){
    al_destroy_font(font);
    al_destroy_font(font1);
    al_destroy_bitmap(background);
}


void about1_init(){
    background_about1=al_load_bitmap("./image/About-1.png");
}
void about1_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) //Start -> 選場地
        if( event.mouse.x >= 35 && event.mouse.y >= 30 && event.mouse.x <= 175 && event.mouse.y <= 170 ){
            judge_next_window = true;
            win=8;
        }

    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) //about -> 遊戲介紹
        if( event.mouse.x >= 855 && event.mouse.y >= 755 && event.mouse.x <= 950 && event.mouse.y <= 835){
            judge_next_window = true;
            win=7;
        }
    //if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) printf("x=%d ,y=%d \n",event.mouse.x,event.mouse.y);

}
void about1_draw(){
    al_draw_bitmap(background_about1,0,0,0);

}
void about1_destroy(){
    al_destroy_bitmap(background_about1);
}


void about2_init(){
    background_about2=al_load_bitmap("./image/About-2.png");
}
void about2_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) //Start -> 選場地
        if( event.mouse.x >= 35 && event.mouse.y >= 30 && event.mouse.x <= 175 && event.mouse.y <=170){
            judge_next_window = true;
            win=0;
        }
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) //about -> 遊戲介紹
        if( event.mouse.x >= 650 && event.mouse.y >= 760 && event.mouse.x <= 730 && event.mouse.y <= 835 ){
            judge_next_window = true;
            win=6;
        }
    //if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) printf("x=%d ,y=%d \n",event.mouse.x,event.mouse.y);
}
void about2_draw(){
    al_draw_bitmap(background_about2,0,0,0);
}
void about2_destroy(){
    al_destroy_bitmap(background_about2);
}



// function of game_scene
void game_scene_init(){
    character_init();
    background = al_load_bitmap("./image/stage.jpg");
}
void game_scene_draw(){
    al_draw_bitmap(background, 0, 0, 0);
    character_draw();
}
void game_scene_destroy(){
    al_destroy_bitmap(background);
    character_destory();
}

void game_soccer_init(){
    countdown=7259;
    character_init();
    font = al_load_ttf_font("./font/normal.ttf",60,0);
    background = al_load_bitmap("./image/soccer.jpg");
    background_count = al_load_bitmap("./image/count.jpg");
}
void game_soccer_draw(){
    countdown--;
    al_draw_bitmap(background, 0, -20, 0);
    al_draw_bitmap(background_count, 0, 0, 0);
    //al_draw_rectangle(0,52,1550,52,al_map_rgb(220,220,220),110);
    character_draw();
    if(countdown%60==0){
        if(countdown==7200){
            time_game[1]='1';
            time_game[3]='5';
            time_game[4]='9';
        }else if(countdown==3600){
            time_game[1]='0';
            time_game[3]='5';
            time_game[4]='9';
        }else if(countdown%600==0){
            time_game[3]--;
            time_game[4]='9';
        }else{
            time_game[4]--;
        }
    }
    if(countdown>=2)al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2)+550, (HEIGHT/2)-400 , ALLEGRO_ALIGN_CENTRE, time_game);
    if(countdown>=2)al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2)+360, (HEIGHT/2)-400 , ALLEGRO_ALIGN_CENTRE, "Time:");
}
void game_soccer_destroy(){
    al_destroy_bitmap(background);
    al_destroy_bitmap(background_count);
    al_destroy_font(font);
    character_destory();
}

void game_ice_init(){
    countdown=7259;
    character_init();
    font = al_load_ttf_font("./font/normal.ttf",60,0);
    background = al_load_bitmap("./image/ice (2).jpg");
    background_count = al_load_bitmap("./image/count.jpg");
}
void game_ice_draw(){
    countdown--;
    al_draw_bitmap(background, 0, -20, 0);
    al_draw_bitmap(background_count, 0, 0, 0);
    //al_draw_rectangle(0,52,1550,52,al_map_rgb(220,220,220),110);
    character_draw();
    if(countdown%60==0){
        if(countdown==7200){
            time_game[1]='1';
            time_game[3]='5';
            time_game[4]='9';
        }else if(countdown==3600){
            time_game[1]='0';
            time_game[3]='5';
            time_game[4]='9';
        }else if(countdown%600==0){
            time_game[3]--;
            time_game[4]='9';
        }else{
            time_game[4]--;
        }
    }
    if(countdown>=2)al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2)+550, (HEIGHT/2)-400 , ALLEGRO_ALIGN_CENTRE, time_game);
    if(countdown>=2)al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2)+360, (HEIGHT/2)-400 , ALLEGRO_ALIGN_CENTRE, "Time:");
}
void game_ice_destroy(){
    al_destroy_bitmap(background);
    al_destroy_bitmap(background_count);
    al_destroy_font(font);
    character_destory();
}

void game_beach_init(){
    countdown=7259;
    character_init();
    font = al_load_ttf_font("./font/normal.ttf",60,0);
    background = al_load_bitmap("./image/blur_sand.png");
    background_count = al_load_bitmap("./image/count.jpg");
    //background_sand= al_load_bitmap("./image/sand.png");
}
void game_beach_draw(){
    countdown--;
    al_draw_bitmap(background, 0, -20, 0);
    al_draw_bitmap(background_count, 0, 0, 0);
    //al_draw_rectangle(0,52,1550,52,al_map_rgb(220,220,220),110);
    character_draw();
    //al_draw_bitmap(background_sand, 580, 178, 0);
    if(countdown%60==0){
        if(countdown==7200){
            time_game[1]='1';
            time_game[3]='5';
            time_game[4]='9';
        }else if(countdown==3600){
            time_game[1]='0';
            time_game[3]='5';
            time_game[4]='9';
        }else if(countdown%600==0){
            time_game[3]--;
            time_game[4]='9';
        }else{
            time_game[4]--;
        }
    }
    if(countdown>=2)al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2)+550, (HEIGHT/2)-400 , ALLEGRO_ALIGN_CENTRE, time_game);
    if(countdown>=2)al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2)+360, (HEIGHT/2)-400 , ALLEGRO_ALIGN_CENTRE, "Time:");
}
void game_beach_destroy(){
    al_destroy_bitmap(background);
    al_destroy_bitmap(background_count);
    al_destroy_font(font);
    character_destory();
}

void game_outspace_init(){
    countdown=7259;
    character_init();
    font = al_load_ttf_font("./font/normal.ttf",60,0);
    background = al_load_bitmap("./image/out.png");
    background_count = al_load_bitmap("./image/count.jpg");
}
void game_outspace_draw(){
    countdown--;
    al_draw_bitmap(background, 0, -20, 0);
    al_draw_bitmap(background_count, 0, 0, 0);
    //al_draw_rectangle(0,52,1550,52,al_map_rgb(220,220,220),110);
    character_draw();
    if(countdown%60==0){
        if(countdown==7200){
            time_game[1]='1';
            time_game[3]='5';
            time_game[4]='9';
        }else if(countdown==3600){
            time_game[1]='0';
            time_game[3]='5';
            time_game[4]='9';
        }else if(countdown%600==0){
            time_game[3]--;
            time_game[4]='9';
        }else{
            time_game[4]--;
        }
    }
    if(countdown>=2)al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2)+550, (HEIGHT/2)-400 , ALLEGRO_ALIGN_CENTRE, time_game);
    if(countdown>=2)al_draw_text(font, al_map_rgb(255,255,255), (WIDTH/2)+360, (HEIGHT/2)-400 , ALLEGRO_ALIGN_CENTRE, "Time:");
}
void game_outspace_destroy(){
    al_destroy_bitmap(background);
    al_destroy_bitmap(background_count);
    al_destroy_font(font);
    character_destory();
}

void choose_scene_init(){
    background = al_load_bitmap("./image/choose(final).png");
}
void choose_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )  //選場地 -> 足球場
        if( event.mouse.x >= 88 && event.mouse.y >=246 && event.mouse.x <=395 && event.mouse.y <=426 ){
            judge_next_window = true;
            win=1;
        }
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )  //選場地 -> 沙灘
        if( event.mouse.x >= 454 && event.mouse.y >= 246 && event.mouse.x <= 730 && event.mouse.y <=427){
            judge_next_window = true;
            win=2;
        }
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )  //選場地 -> 冰原
        if( event.mouse.x >= 790 && event.mouse.y >=247 && event.mouse.x <= 1070 && event.mouse.y <=426){
            judge_next_window = true;
            win=3;
        }
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )  //選場地 -> 外太空
        if( event.mouse.x >= 1130 && event.mouse.y >=246 && event.mouse.x <= 1409 && event.mouse.y <=426){
            judge_next_window = true;
            win=4;
        }
}

void choose_scene_draw(){
    al_draw_bitmap(background, 0, 0, 0);
}
void choose_scene_destroy(){
    al_destroy_bitmap(background);
}


void end_init(){
    font = al_load_ttf_font("./font/normal.ttf",130,0);
    background = al_load_bitmap("./image/end(final).png");
    award = al_load_bitmap("./image/Award.png");
    ht = al_load_bitmap("./image/htchen.png");
}

void end_process(ALLEGRO_EVENT event){

    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ) {
        if( event.mouse.x >= 625 && event.mouse.y >=700 && event.mouse.x <=930 && event.mouse.y <=820 ){
            judge_next_window = true;
        }
    }
}

void end_draw(){
    int a_point=0;
    int b_point=0;
    for(int i=0 ; i<2 ;i++){
        if(scorea[i]!=0){
            a_point*=10;
            a_point+=scorea[i]-'0';
        }
    }
    for(int i=0 ; i<2 ;i++){
        if(scoreb[i]!=0){
            b_point*=10;
            b_point+=scoreb[i]-'0';
        }
    }
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_text(font, al_map_rgb(100,100,200), (WIDTH/2)+150, 80 , ALLEGRO_ALIGN_CENTRE, scorea);
    al_draw_text(font, al_map_rgb(200,100,100), (WIDTH/2)-150, 80 , ALLEGRO_ALIGN_CENTRE, scoreb);
    if(a_point>b_point){
        al_draw_bitmap(ht, 850, 400, 0);
        al_draw_bitmap(award, 1250, 350, 0);
        al_draw_text(font, al_map_rgb(235, 177, 89), 1350, 60 , ALLEGRO_ALIGN_CENTRE, "Win");
        al_draw_text(font, al_map_rgb(62, 65, 66), 200, 60 , ALLEGRO_ALIGN_CENTRE, "LOSE");
    }else if(a_point<b_point){
        al_draw_bitmap(ht, 310, 400, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_bitmap(award, 230 , 350, 0);
        al_draw_text(font, al_map_rgb(235, 177, 89), 200, 60 , ALLEGRO_ALIGN_CENTRE, "Win");
        al_draw_text(font, al_map_rgb(62, 65, 66), 1350, 60 , ALLEGRO_ALIGN_CENTRE, "Lose");
    }else{
        al_draw_bitmap(ht, 850, 400, 0);
        al_draw_bitmap(ht, 310, 400, ALLEGRO_FLIP_HORIZONTAL);
        al_draw_bitmap(award, 1250, 350, 0);
        al_draw_bitmap(award, 220, 350, 0);
        al_draw_text(font, al_map_rgb(255, 237, 117), 775, 220 , ALLEGRO_ALIGN_CENTRE, "Tie");
    }

}

void end_destroy(){
    al_destroy_font(font);
    al_destroy_bitmap(background);
    al_destroy_bitmap(award);
    al_destroy_bitmap(ht);
}


