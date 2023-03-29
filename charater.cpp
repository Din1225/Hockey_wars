#include "charater.h"

ALLEGRO_FONT *font2 = NULL;
ALLEGRO_BITMAP *barrier_img;
ALLEGRO_SAMPLE *sound_effect=NULL;
ALLEGRO_SAMPLE_INSTANCE *effect;

char scorea[3];
char scoreb[3];
char time_item[5]={'0','0',':','1','0'};

int item_flag=0;
int ok_flag=0;
int keeping_item_flag=0;
ALLEGRO_BITMAP *box_img;
int countdown_item=7259;
int keeping_item=620;


// the state of character
enum {STOP = 0, MOVE, ATK};
typedef struct character
{
    double x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
    int score=0;
}Character;

Character chara;
Character charb;
Character ball;
Character item;
Character black_hole_left;
Character black_hole_right;
Character white_hole_left;
Character white_hole_right;

ALLEGRO_SAMPLE *sample = NULL;
int dir_x=20;
int dir_y=20;
double ball_velocity=16;
double ball_direction;
int flag=0;

void character_init(){
    countdown_item=7259;
    keeping_item_flag=0;

    char tmp[50];
    item_flag=0;
    sprintf( tmp, "./image/box.png" );
    box_img = al_load_bitmap(tmp);

    barrier_img=al_load_bitmap("./image/barrier.png");

    font2 = al_load_ttf_font("./font/normal.ttf",75,0);
    scorea[0]=48;
    scorea[1]=0;
    scorea[2]=0;
    scoreb[0]=48;
    scoreb[1]=0;
    scoreb[2]=0;
    flag=0;
    chara.score=0;
    charb.score=0;
    srand( time(NULL) );
    ball_direction=rand();
    while((cos(ball_direction)*ball_velocity<ball_velocity/2 && cos(ball_direction)*ball_velocity>(-1)*ball_velocity/2) ||
           (sin(ball_direction)*ball_velocity<ball_velocity/3 && sin(ball_direction)*ball_velocity>(-1)*ball_velocity/3)){
        ball_direction=rand();
    }
    if(cos(ball_direction)>0){
        dir_x=1;
    }else{
        dir_x=-1;
    }
    if(sin(ball_direction)>0){
        dir_y=1;
    }else{
        dir_y=-1;
    }
    //printf("dir_x=%d dir_y=%d\n",dir_x,dir_y);
    // load character images
    if(win==1){
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/little_bin.png" );
        chara.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/little_bin.png" );
        charb.img_move[i-1] = al_load_bitmap(temp);
        }
    }else if(win==2){
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/crab.png" );
        chara.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/crab.png" );
        charb.img_move[i-1] = al_load_bitmap(temp);
        }
    }else if(win==3){
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/bird.png" );
        chara.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/bird.png" );
        charb.img_move[i-1] = al_load_bitmap(temp);
        }
    }else if(win==4){
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/space.png" );
        chara.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/space.png" );
        charb.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/black_hole.png" );
        black_hole_left.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/black_hole.png" );
        black_hole_right.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/white_hole.png" );
        white_hole_left.img_move[i-1] = al_load_bitmap(temp);
        }
        for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/white_hole.png" );
        white_hole_right.img_move[i-1] = al_load_bitmap(temp);
        }

    }

    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        if(win==1) sprintf( temp, "./image/ball.png" );
        else if(win==2) sprintf( temp, "./image/beachball.png" );
        else if(win==3) sprintf( temp, "./image/iceball.png" );
        else sprintf( temp, "./image/spaceball.png" );
        ball.img_move[i-1] = al_load_bitmap(temp);
    }
    /*
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_atk%d.png", i );
        chara.img_atk[i-1] = al_load_bitmap(temp);
    }*/
    // load effective sound
    /*
    sample = al_load_sample("./sound/atk_sound.wav");
    chara.atk_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());
    */
    // initial the geometric information of characterA ,characterB ,ball
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = WIDTH/2 + 480;
    chara.y = HEIGHT/2;
    chara.dir = true;

    charb.width = al_get_bitmap_width(charb.img_move[0]);
    charb.height = al_get_bitmap_height(charb.img_move[0]);
    charb.x = WIDTH/2 - 600;
    charb.y = HEIGHT/2;
    charb.dir = false;

    ball.width = al_get_bitmap_width(ball.img_move[0]);
    ball.height = al_get_bitmap_height(ball.img_move[0]);
    ball.x = WIDTH/2 - 51;
    ball.y = HEIGHT/2 + 5;
    ball.dir = false;
    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 30;
    if(win==4){
        black_hole_left.width = al_get_bitmap_width( black_hole_left.img_move[0]);
        black_hole_left.height = al_get_bitmap_height( black_hole_left.img_move[0]);
        black_hole_left.x=400;
        black_hole_left.y=177;

        black_hole_right.width = al_get_bitmap_width(black_hole_right.img_move[0]);
        black_hole_right.height = al_get_bitmap_height(black_hole_right.img_move[0]);
        black_hole_right.x=1020;
        black_hole_right.y=710;

        white_hole_left.width = al_get_bitmap_width(white_hole_left.img_move[0]);
        white_hole_left.height = al_get_bitmap_height(white_hole_left.img_move[0]);
        white_hole_left.x=400;
        white_hole_left.y=710;

        white_hole_right.width = al_get_bitmap_width(white_hole_right.img_move[0]);
        white_hole_right.height = al_get_bitmap_height(white_hole_right.img_move[0]);
        white_hole_right.x=1020;
        white_hole_right.y=177;
    }
    ball_velocity=16;
    //冰原球速變快1.1
    if(win==3) ball_velocity*=(1.2);
}

void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
    }
    // process the keyboard event
    else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
    else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        charb.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}

void charater_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_UP] ){
        if(chara.y < 170){
            chara.state = STOP;
        }
        else{
            chara.y -= 13;
            chara.state = MOVE;
        }
    }
    /*
    else if( key_state[ALLEGRO_KEY_A] ){
        chara.dir = false;
        chara.x -= 5;
        chara.state = MOVE;
    }*/
    else if( key_state[ALLEGRO_KEY_DOWN] ){
        if(chara.y > 680){
            chara.state = STOP;
        }
        else{
            chara.y += 13;
            chara.state = MOVE;
        }
    }

    if( key_state[ALLEGRO_KEY_W] ){
        if(charb.y < 170){
            charb.state = STOP;
        }
        else{
            charb.y -= 13;
            charb.state = MOVE;
        }
    }
    else if( key_state[ALLEGRO_KEY_S] ){
        if(charb.y > 680){
            charb.state = STOP;
        }
        else{
            charb.y += 13;
            charb.state = MOVE;
        }
    }
    if(countdown_item<=7200){

        double x_veloc=cos(ball_direction);
        if(x_veloc<0) x_veloc*=-1;
        double y_veloc=sin(ball_direction);
        if(y_veloc<0) y_veloc*=-1;
        //printf("%llf\n",ball_direction);
        ball.x += (ball_velocity*x_veloc)*dir_x;
        ball.y += (ball_velocity*y_veloc)*dir_y;
        //printf("ball_velocity*sin(ball_direction)*dir_y=%f\n",ball_velocity*sin(ball_direction)*dir_y);
        //反彈條件
        if( ball.y >= 750  || ball.y <= 170 ){
            dir_y*=(-1);
            ball_direction+=(0.005);
        }
        if( ((ball.x+71<=chara.x+96 && ball.x+71>=chara.x) && (ball.y<=chara.y+120 && ball.y+67>=chara.y && dir_x==1))){
            dir_x*=(-1);
        }else if((ball.x<=charb.x+96 && ball.x>=charb.x) && (ball.y<=charb.y+120 && ball.y+67>=charb.y && dir_x==-1)){
            dir_x*=(-1);
        }
        //得分條件
        if( ball.x <= 100 && flag==0 ){         //左邊
            flag=1;
            chara.score++;
            //printf("b:%d\n",charb.score);
        }
        if( ball.x >= 1380 && flag==0 ){          //右邊
            flag=1;
            charb.score++;
            //printf("a:%d\n",chara.score);
        }
        //(吃到道具後的洞口判定範圍)
        if( (ball.x <= 300 && ball.x>=300-25) && ((ball.y <= 750 && ball.y >= 610 ) || (ball.y <= 310 && ball.y >= 170 )) && keeping_item_flag==1 && flag==0 && dir_x<0){
            dir_x*=(-1);
        }

        if( (ball.x >= 1180 && ball.x<=1180+25) && ((ball.y <= 750 && ball.y >= 610 ) || (ball.y <= 310 && ball.y >= 170 )) && keeping_item_flag==2 && flag==0 && dir_x>0){
            dir_x*=(-1);
        }

        //緩衝區 把球傳回起始點
        //printf("ball.x=%f 100-120*(ball_velocity*x_veloc)=%f flag=%d\n",ball.x,100-120*(ball_velocity*x_veloc),flag);
        if( ball.x <= 100-120*(ball_velocity*x_veloc) && flag==1 ){
            ball.x = WIDTH/2 - 51;
            ball.y = HEIGHT/2 + 5;
            srand( time(NULL) );
            ball_direction=rand();
            while((cos(ball_direction)*ball_velocity<ball_velocity/2 && cos(ball_direction)*ball_velocity>(-1)*ball_velocity/2) ||
                   (sin(ball_direction)*ball_velocity<ball_velocity/3 && sin(ball_direction)*ball_velocity>(-1)*ball_velocity/3)){
                ball_direction=rand();
            }
            flag=0;
            if(cos(ball_direction)>0){
                dir_x=1;
            }else{
                dir_x=-1;
            }
            if(sin(ball_direction)>0){
                dir_y=1;
            }else{
                dir_y=-1;
            }
        }
        if( ball.x >= 1380+120*(ball_velocity*x_veloc) && flag==1){
            ball.x = WIDTH/2 - 51;
            ball.y = HEIGHT/2 + 5;
            srand( time(NULL) );
            ball_direction=rand();
            while((cos(ball_direction)*ball_velocity<ball_velocity/2 && cos(ball_direction)*ball_velocity>(-1)*ball_velocity/2) ||
                   (sin(ball_direction)*ball_velocity<ball_velocity/3 && sin(ball_direction)*ball_velocity>(-1)*ball_velocity/3)){
                ball_direction=rand();
            }
            flag=0;
            if(cos(ball_direction)>0){
                dir_x=1;
            }else{
                dir_x=-1;
            }
            if(sin(ball_direction)>0){
                dir_y=1;
            }else{
                dir_y=-1;
            }
        }



        //球吃到道具
        if(ball.x>=item.x-71 && ball.x<=item.x+133 && ball.y>=item.y-67 && ball.y<=item.y+121 && dir_x==1 && item_flag==1){
            //道具時間
            time_item[0]='0';
            time_item[1]='0';
            time_item[2]=':';
            time_item[3]='1';
            time_item[4]='0';
            keeping_item=620;
            item_flag=0;
            ok_flag=0;
            keeping_item_flag=1;
            //printf("%d",keeping_item_flag);
            //球速度改變
            ball_velocity*=1.2;

            //播放音效
            sound_effect = al_load_sample("./sound/item_sound_effect.mp3");
            al_reserve_samples(20);
            effect = al_create_sample_instance(sound_effect);
            // Loop the song until the display closes
            al_set_sample_instance_playmode(effect, ALLEGRO_PLAYMODE_LOOP);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(effect, al_get_default_mixer());
            // set the volume of instance
            al_set_sample_instance_gain(effect,1) ;
            al_play_sample_instance(effect);


        }
        else if(ball.x>=item.x-71 && ball.x<=item.x+133 && ball.y>=item.y-67 && ball.y<=item.y+121 && dir_x==-1 && item_flag==1 ){
            time_item[0]='0';
            time_item[1]='0';
            time_item[2]=':';
            time_item[3]='1';
            time_item[4]='0';
            keeping_item=620;
            item_flag=0;
            ok_flag=0;
            keeping_item_flag=2;
            //球速度改變
            ball_velocity*=1.2;

            //播放音效
            sound_effect = al_load_sample("./sound/item_sound_effect.mp3");
            al_reserve_samples(20);
            effect = al_create_sample_instance(sound_effect);
            // Loop the song until the display closes
            al_set_sample_instance_playmode(effect, ALLEGRO_PLAYMODE_LOOP);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(effect, al_get_default_mixer());
            // set the volume of instance
            al_set_sample_instance_gain(effect,1) ;
            al_play_sample_instance(effect);
        }

        //外太空
        if(win==4){
            if(ball.x>=black_hole_left.x-71 && ball.x<=black_hole_left.x+100 && ball.y>=black_hole_left.y-67 && ball.y<=black_hole_left.y+100){
                ball.x=white_hole_right.x+15;
                ball.y=white_hole_right.y+15;
                srand( time(NULL) );
                ball_direction=rand();
                while((cos(ball_direction)*ball_velocity<ball_velocity && cos(ball_direction)*ball_velocity>(-1)*ball_velocity/2) ||
                       (sin(ball_direction)*ball_velocity<ball_velocity/3 && sin(ball_direction)*ball_velocity>(-1)*ball_velocity/3)){
                    ball_direction=rand();
                }
                if(cos(ball_direction)>0){
                    dir_x=1;
                }else{
                    dir_x=-1;
                }
                if(sin(ball_direction)>0){
                    dir_y=1;
                }else{
                    dir_y=-1;
                }
            }
            if(ball.x>=black_hole_right.x-71 && ball.x<=black_hole_right.x+100 && ball.y>=black_hole_right.y-67 && ball.y<=black_hole_right.y+100 ){
                ball.x=white_hole_left.x+15;
                ball.y=white_hole_left.y+15;
                srand( time(NULL) );
                ball_direction=rand();
                while((cos(ball_direction)*ball_velocity<ball_velocity/2 && cos(ball_direction)*ball_velocity>(-1)*ball_velocity) ||
                       (sin(ball_direction)*ball_velocity<ball_velocity/3 && sin(ball_direction)*ball_velocity>(-1)*ball_velocity/3)){
                    ball_direction=rand();
                }
                if(cos(ball_direction)>0){
                    dir_x=1;
                }else{
                    dir_x=-1;
                }
                if(sin(ball_direction)>0){
                    dir_y=1;
                }else{
                    dir_y=-1;
                }
            }
        }

        //判定時間到 要切換畫面了
        if(countdown_item==0){
            judge_next_window=true;
        }
        /*
        else if( key_state[ALLEGRO_KEY_D] ){
            chara.dir = true;
            chara.x += 5;
            chara.state = MOVE;
        }else if( key_state[ALLEGRO_KEY_SPACE] ){
            chara.state = ATK;
        }else if( chara.anime == chara.anime_time-1 ){
            chara.anime = 0;
            chara.state = STOP;
        }else if ( chara.anime == 0 ){
            chara.state = STOP;
        }*/
    }
}
void character_draw(){
    countdown_item--;
    if(countdown_item==5400 || countdown_item==3600 || countdown_item==1800 ){
        item_flag=1;
        ok_flag=0;
    }
    //道具持續時間顯示
    if( keeping_item_flag==1 || keeping_item_flag==2){
        if(keeping_item_flag==1){
            al_draw_bitmap(barrier_img, 290, 177, 0);
            al_draw_bitmap(barrier_img, 290, 680, 0);
        }
        if(keeping_item_flag==2){
            al_draw_bitmap(barrier_img, 1235, 177, 0);
            al_draw_bitmap(barrier_img, 1235, 680, 0);
        }
        keeping_item--;
        if(keeping_item%60==0){
            if(keeping_item%600==0){
                time_item[3]--;
                time_item[4]='9';
            }else{
                time_item[4]--;
            }
        }
        if( keeping_item==2){
            ball_velocity/=1.2;
            keeping_item_flag=0;
        }
        //printf("<%s>",time_item);
        al_draw_text(font2, al_map_rgb(255,255,0), (WIDTH/2)-550, (HEIGHT/2)-400 , ALLEGRO_ALIGN_CENTRE, time_item);
        //結束吃到道具的音效
        if(keeping_item==565) al_destroy_sample_instance(effect);
    }

    if(chara.score<=9){
        scorea[0]=chara.score+48;
        scorea[1]=0;
    }else{
        scorea[0]=chara.score/10+48;
        scorea[1]=chara.score%10+48;
    }
    if(charb.score<=9){
        scoreb[0]=charb.score+48;
        scoreb[1]=0;
    }else{
        scoreb[0]=charb.score/10+48;
        scoreb[1]=charb.score%10+48;
    }
    al_draw_text(font2, al_map_rgb(100,100,200), (WIDTH/2)+100, 20 , ALLEGRO_ALIGN_CENTRE, scorea);
    al_draw_text(font2, al_map_rgb(200,100,100), (WIDTH/2)-100, 20 , ALLEGRO_ALIGN_CENTRE, scoreb);
    // with the state, draw corresponding image
    if( chara.state == STOP ){
        if( chara.dir )
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
    }else if( chara.state == MOVE ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }
        }
    }
    if( charb.state == STOP ){
        if( charb.dir )
            al_draw_bitmap(charb.img_move[0], charb.x, charb.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(charb.img_move[0], charb.x, charb.y, 0);
    }else if( charb.state == MOVE ){
        if( charb.dir ){
            if( charb.anime < charb.anime_time/2 ){
                al_draw_bitmap(charb.img_move[0], charb.x, charb.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(charb.img_move[1], charb.x, charb.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( charb.anime < charb.anime_time/2 ){
                al_draw_bitmap(charb.img_move[0], charb.x, charb.y, 0);
            }else{
                al_draw_bitmap(charb.img_move[1], charb.x, charb.y, 0);
            }
        }
    }
    if(((ball.x<600 || ball.x>900) && win==2) || win!=2){
        if( ball.state == STOP ){
            if( ball.dir )
                al_draw_bitmap(ball.img_move[0], ball.x, ball.y, ALLEGRO_FLIP_HORIZONTAL);
            else
                al_draw_bitmap(ball.img_move[0], ball.x, ball.y, 0);
        }else if( ball.state == MOVE ){
            if( ball.dir ){
                if( ball.anime < ball.anime_time/2 ){
                    al_draw_bitmap(ball.img_move[0], ball.x, ball.y, ALLEGRO_FLIP_HORIZONTAL);
                }else{
                    al_draw_bitmap(ball.img_move[1], ball.x, ball.y, ALLEGRO_FLIP_HORIZONTAL);
                }
            }else{
                if( ball.anime < ball.anime_time/2 ){
                    al_draw_bitmap(ball.img_move[0], ball.x, ball.y, 0);
                }else{
                    al_draw_bitmap(ball.img_move[1], ball.x, ball.y, 0);
                }
            }
        }
    }
    if(win==4){
        if( black_hole_left.state == STOP ){
            if( black_hole_left.dir )
                al_draw_bitmap(black_hole_left.img_move[0], black_hole_left.x, black_hole_left.y, ALLEGRO_FLIP_HORIZONTAL);
            else
                al_draw_bitmap(black_hole_left.img_move[0],black_hole_left.x, black_hole_left.y, 0);
        }else if( black_hole_left.state == MOVE ){
            if( black_hole_left.dir ){
                if( black_hole_left.anime < black_hole_left.anime_time/2 ){
                    al_draw_bitmap(black_hole_left.img_move[0], black_hole_left.x, black_hole_left.y, ALLEGRO_FLIP_HORIZONTAL);
                }else{
                    al_draw_bitmap(black_hole_left.img_move[1], black_hole_left.x, black_hole_left.y, ALLEGRO_FLIP_HORIZONTAL);
                }
            }else{
                if( black_hole_left.anime < black_hole_left.anime_time/2 ){
                    al_draw_bitmap(black_hole_left.img_move[0], black_hole_left.x, black_hole_left.y, 0);
                }else{
                    al_draw_bitmap(black_hole_left.img_move[1], black_hole_left.x, black_hole_left.y, 0);
                }
            }
        }
        if( black_hole_right.state == STOP ){
            if( black_hole_right.dir )
                al_draw_bitmap(black_hole_right.img_move[0], black_hole_right.x, black_hole_right.y, ALLEGRO_FLIP_HORIZONTAL);
            else
                al_draw_bitmap(black_hole_right.img_move[0],black_hole_right.x, black_hole_right.y, 0);
        }else if( black_hole_right.state == MOVE ){
            if( black_hole_right.dir ){
                if( black_hole_right.anime < black_hole_right.anime_time/2 ){
                    al_draw_bitmap(black_hole_right.img_move[0], black_hole_right.x, black_hole_right.y, ALLEGRO_FLIP_HORIZONTAL);
                }else{
                    al_draw_bitmap(black_hole_right.img_move[1], black_hole_right.x, black_hole_right.y, ALLEGRO_FLIP_HORIZONTAL);
                }
            }else{
                if( black_hole_right.anime < black_hole_right.anime_time/2 ){
                    al_draw_bitmap(black_hole_right.img_move[0], black_hole_right.x, black_hole_right.y, 0);
                }else{
                    al_draw_bitmap(black_hole_right.img_move[1], black_hole_right.x, black_hole_right.y, 0);
                }
            }
        }
        if( white_hole_left.state == STOP ){
            if( white_hole_left.dir )
                al_draw_bitmap(white_hole_left.img_move[0], white_hole_left.x, white_hole_left.y, ALLEGRO_FLIP_HORIZONTAL);
            else
                al_draw_bitmap(white_hole_left.img_move[0],white_hole_left.x, white_hole_left.y, 0);
        }else if( white_hole_left.state == MOVE ){
            if( white_hole_left.dir ){
                if( white_hole_left.anime < white_hole_left.anime_time/2 ){
                    al_draw_bitmap(white_hole_left.img_move[0], white_hole_left.x, white_hole_left.y, ALLEGRO_FLIP_HORIZONTAL);
                }else{
                    al_draw_bitmap(white_hole_left.img_move[1], white_hole_left.x, white_hole_left.y, ALLEGRO_FLIP_HORIZONTAL);
                }
            }else{
                if( white_hole_left.anime < white_hole_left.anime_time/2 ){
                    al_draw_bitmap(white_hole_left.img_move[0], white_hole_left.x, white_hole_left.y, 0);
                }else{
                    al_draw_bitmap(white_hole_left.img_move[1], white_hole_left.x, white_hole_left.y, 0);
                }
            }
        }
        if( white_hole_right.state == STOP ){
            if( white_hole_right.dir )
                al_draw_bitmap(white_hole_right.img_move[0], white_hole_right.x, white_hole_right.y, ALLEGRO_FLIP_HORIZONTAL);
            else
                al_draw_bitmap(white_hole_right.img_move[0],white_hole_right.x, white_hole_right.y, 0);
        }else if( white_hole_right.state == MOVE ){
            if( white_hole_right.dir ){
                if( white_hole_right.anime < white_hole_right.anime_time/2 ){
                    al_draw_bitmap(white_hole_right.img_move[0], white_hole_right.x, white_hole_right.y, ALLEGRO_FLIP_HORIZONTAL);
                }else{
                    al_draw_bitmap(white_hole_right.img_move[1], white_hole_right.x, white_hole_right.y, ALLEGRO_FLIP_HORIZONTAL);
                }
            }else{
                if( white_hole_right.anime < white_hole_right.anime_time/2 ){
                    al_draw_bitmap(white_hole_right.img_move[0], white_hole_right.x, white_hole_right.y, 0);
                }else{
                    al_draw_bitmap(white_hole_right.img_move[1], white_hole_right.x, white_hole_right.y, 0);
                }
            }
        }

    }
    if(item_flag==1){
        srand( time(NULL) );
        int min_tmp = 1;
        int max_tmp = 4;

        /* 產生 [min , max] 的整數亂數 */
        if(!ok_flag){
            int tmp = rand() % (max_tmp - min_tmp + 1) + min_tmp;
            if(tmp==1){
                srand( time(NULL) );
                double min_x = 296;
                double max_x = 596-133;
                item.x = (max_x - min_x) * rand() / (RAND_MAX + 1.0) + min_x;
                double min_y = 170;
                double max_y = 750-121;
                item.y = (max_y - min_y) * rand() / (RAND_MAX + 1.0) + min_y;
            }else if(tmp==2){
                srand( time(NULL) );
                double min_x = 780-150-133;
                double max_x = 780+150-133;
                item.x = (max_x - min_x) * rand() / (RAND_MAX + 1.0) + min_x;
                double min_y = 170;
                double max_y = 498-80-121;
                item.y = (max_y - min_y) * rand() / (RAND_MAX + 1.0) + min_y;
            }else if(tmp==3){
                srand( time(NULL) );
                double min_x = 780-150-133;
                double max_x = 780+150-133;
                item.x = (max_x - min_x) * rand() / (RAND_MAX + 1.0) + min_x;
                double min_y = 498+80;
                double max_y = 750-121;
                item.y = (max_y - min_y) * rand() / (RAND_MAX + 1.0) + min_y;
            }else if(tmp==4){
                srand( time(NULL) );
                double min_x = 780+150-133;
                double max_x = 1237-133;
                item.x = (max_x - min_x) * rand() / (RAND_MAX + 1.0) + min_x;
                double min_y = 170;
                double max_y = 750-121;
                item.y = (max_y - min_y) * rand() / (RAND_MAX + 1.0) + min_y;
            }
            ok_flag=1;
        }
        al_draw_bitmap(box_img, item.x, item.y, 0);

    }
    /*
    else if( chara.state == ATK ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara.atk_Sound);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, 0);
                al_play_sample_instance(chara.atk_Sound);
            }
        }
    }*/
}
void character_destory(){
    al_destroy_bitmap(box_img);
    al_destroy_bitmap(chara.img_atk[0]);
    al_destroy_bitmap(chara.img_atk[1]);
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
//自己加的自己加的自己加的自己加的自己加的自己加的
    al_destroy_bitmap(charb.img_atk[0]);
    al_destroy_bitmap(charb.img_atk[1]);
    al_destroy_bitmap(charb.img_move[0]);
    al_destroy_bitmap(charb.img_move[1]);
    al_destroy_bitmap(ball.img_atk[0]);
    al_destroy_bitmap(ball.img_atk[1]);
    al_destroy_bitmap(ball.img_move[0]);
    al_destroy_bitmap(ball.img_move[1]);
    if(win==4){
        al_destroy_bitmap(black_hole_left.img_move[0]);
        al_destroy_bitmap(black_hole_left.img_move[1]);
        al_destroy_bitmap(black_hole_right.img_move[0]);
        al_destroy_bitmap(black_hole_right.img_move[1]);
        al_destroy_bitmap(white_hole_left.img_move[0]);
        al_destroy_bitmap(white_hole_left.img_move[1]);
        al_destroy_bitmap(white_hole_right.img_move[0]);
        al_destroy_bitmap(white_hole_right.img_move[1]);
    }
    al_destroy_font(font2);
    al_destroy_sample_instance(chara.atk_Sound);
}
