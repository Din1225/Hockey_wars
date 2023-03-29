#include "GameWindow.h"

bool draw = false;
int window = 1;

const char *title = "Final Project 110020001+110020003+110020022";

/// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
//主選單音樂
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;
//選場地音樂
ALLEGRO_SAMPLE *choosesong=NULL;
ALLEGRO_SAMPLE_INSTANCE *choose_song;
//遊戲時音樂
ALLEGRO_SAMPLE *soccersong=NULL;
ALLEGRO_SAMPLE_INSTANCE *soccer_song;
//結算音樂
ALLEGRO_SAMPLE *endsong=NULL;
ALLEGRO_SAMPLE_INSTANCE *end_song;


int Game_establish() {
    int msg = 0;

    game_init();
    game_begin();

    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf( "Game Over\n" );
    }

    game_destroy();
    return 0;
}

void game_init() {
    printf( "Game Initializing...\n" );
    al_init();
    /// init audio
    al_install_audio();
    al_init_acodec_addon();
    /// Create display
    display = al_create_display(WIDTH, HEIGHT);
    /// create event queue
    event_queue = al_create_event_queue();
    /// Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    /// Register event 把視窗,鍵盤,滑鼠,fps_timer讀進去
    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps  = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;
    /// initialize the icon
    ALLEGRO_BITMAP *icon = al_load_bitmap("./image/icon.jpg");
    al_set_display_icon(display, icon);

}



void game_begin() {
    ///設定主選單音樂
    song = al_load_sample("./sound/menu_song.mp3");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(sample_instance,0.6) ;
    al_play_sample_instance(sample_instance);
    al_start_timer(fps);
    ///初始化主選單
    menu_init();
}


void game_update(){
    if( judge_next_window ){
        if( window == 1 ){
            menu_destroy();
            al_destroy_sample_instance(sample_instance);
            choosesong = al_load_sample("./sound/choose_song.mp3");
            al_reserve_samples(20);
            choose_song = al_create_sample_instance(choosesong);
            al_set_sample_instance_playmode(choose_song, ALLEGRO_PLAYMODE_LOOP);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(choose_song, al_get_default_mixer());
            al_set_sample_instance_gain(choose_song,0.6);
            al_play_sample_instance(choose_song);
            judge_next_window = false;
            if(win!=6 ){                ///1.主選單 -> 2.選場地畫面
                choose_scene_init();
                window = 2;
            }else{                      ///1.主選單 -> 6.About畫面
                about1_init();
                window = 6;
            }
        }
        else if( window == 2&& win==1){         ///2.選場地畫面 -> 4-1 足球場
            choose_scene_destroy();
            al_destroy_sample_instance(choose_song);
            soccersong = al_load_sample("./sound/soccer_song.mp3");
            al_reserve_samples(20);
            soccer_song = al_create_sample_instance(soccersong);
            al_set_sample_instance_playmode(soccer_song, ALLEGRO_PLAYMODE_LOOP);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(soccer_song, al_get_default_mixer());
            al_set_sample_instance_gain(soccer_song,1);
            al_play_sample_instance(soccer_song);
            game_soccer_init();
            judge_next_window = false;
            window = 4;
        }
        else if( window == 2  &&win==2){        ///2.選場地畫面 -> 4-2 沙灘
            choose_scene_destroy();
            al_destroy_sample_instance(choose_song);
            soccersong = al_load_sample("./sound/soccer_song.mp3");
            al_reserve_samples(20);
            soccer_song = al_create_sample_instance(soccersong);
            al_set_sample_instance_playmode(soccer_song, ALLEGRO_PLAYMODE_LOOP);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(soccer_song, al_get_default_mixer());
            al_set_sample_instance_gain(soccer_song,1);
            al_play_sample_instance(soccer_song);
            game_beach_init();
            judge_next_window = false;
            window = 4;
        }
        else if( window == 2  &&win==3){        ///2.選場地畫面 -> 4-3 沙灘
            choose_scene_destroy();
            al_destroy_sample_instance(choose_song);
            soccersong = al_load_sample("./sound/soccer_song.mp3");
            al_reserve_samples(20);
            soccer_song = al_create_sample_instance(soccersong);
            al_set_sample_instance_playmode(soccer_song, ALLEGRO_PLAYMODE_LOOP);// Loop the song until the display closes
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(soccer_song, al_get_default_mixer());
            al_set_sample_instance_gain(soccer_song,1);
            al_play_sample_instance(soccer_song);
            game_ice_init();
            judge_next_window = false;
            window = 4;
        }
        else if( window == 2  &&win==4){        ///2.選場地畫面 -> 4-4 沙灘
            choose_scene_destroy();
            al_destroy_sample_instance(choose_song);
            soccersong = al_load_sample("./sound/soccer_song.mp3");
            al_reserve_samples(20);
            soccer_song = al_create_sample_instance(soccersong);
            al_set_sample_instance_playmode(soccer_song, ALLEGRO_PLAYMODE_LOOP);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(soccer_song, al_get_default_mixer());
            al_set_sample_instance_gain(soccer_song,1);
            al_play_sample_instance(soccer_song);
            game_outspace_init();
            judge_next_window = false;
            window = 4;
        }
        else if( window == 4){                  ///4.遊戲畫面 -> 5.結算畫面
            if(win==1){
                game_soccer_destroy();
            }
            else if(win==2){
                game_beach_destroy();
            }
            else if(win==3){
                game_ice_destroy();
            }
            else if(win==4){
                game_outspace_destroy();
            }
            al_destroy_sample_instance(soccer_song);
            endsong = al_load_sample("./sound/end_song.mp3");
            al_reserve_samples(20);
            sample_instance = al_create_sample_instance(endsong);
            al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
            al_set_sample_instance_gain(sample_instance,0.6) ;
            al_play_sample_instance(sample_instance);
            end_init();
            judge_next_window = false;
            window = 5;
        }
        else if( window == 6 ){                ///6.About1畫面 -> About2畫面 or 主選單
            judge_next_window=false;
            if(win==0){         //About2 -> 主選單
                about2_destroy();
                game_begin();
                window=1;
                al_destroy_sample_instance(choose_song);
            }
            else if(win==6){    //About2 -> About1
                about2_destroy();
                about1_init();
            }
            else if(win==7){    //About1 -> About2
                about1_destroy();
                about2_init();
            }
            else if(win==8){    //About1 -> 主選單
                about1_destroy();
                game_begin();
                window=1;
                win=0;
                al_destroy_sample_instance(choose_song);
            }
        }
        else if(window == 5){                   ///5.結算畫面 -> 1.主選單
            judge_next_window = false;
            end_destroy();
            window=1;
            al_destroy_sample_instance(sample_instance);
            game_begin();
        }
    }
    if( window == 4 ){           ///4是遊戲畫面 要初始化character
        charater_update();
    }
}


int process_event(){
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    /// 呼叫每個畫面需要的Process
    if( window == 1 ){
        menu_process(event);
    }else if( window == 2 ){
        choose_process(event);
    }else if( window == 4){
        charater_process(event);
    }else if( window == 6 && win == 6){
        about1_process(event);
    }else if( window == 6 && win == 7){
        about2_process(event);
    }else if( window == 5){
        end_process(event);
    }
    // Shutdown our program
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;
    else if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps)
            draw = true;
    if(draw) game_update();
    return 0;
}


void game_draw(){
    if( window == 1 ){
        menu_draw();
    }else if( window == 2 ){
        choose_scene_draw();
    }else if( window == 4 && win == 1 ){
        game_soccer_draw();
    }else if(window == 4 && win == 2){
        game_beach_draw();
    }else if(window == 4 && win == 3){
        game_ice_draw();
    }else if(window == 4 && win == 4){
        game_outspace_draw();
    }else if(window == 6 && win == 6){
        about1_draw();
    }else if(window == 6 && win == 7){
        about2_draw();
    }else if(window == 5){
        end_draw();
    }

    al_flip_display();
}


int game_run() {
    int error = 0;
    if( draw ){
        game_draw();
        draw = false;
    }
    if ( !al_is_event_queue_empty(event_queue) ) {
        error = process_event();
    }
    return error;
}

void game_destroy() {
    al_destroy_sample_instance(sample_instance);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    menu_destroy();
    game_scene_destroy();
}
