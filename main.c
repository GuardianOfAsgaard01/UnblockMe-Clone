/* This project is written for
 * CEN 116 course
 * Compile with: gcc main.c functions.c functions.h -o UnblockMe -lallegro -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf
 * Authors: Mustafa BOLEKEN, Uğur Can ÖZİPEK, Ümit KORKMAZER
 */
#include <stdio.h>
#include "functions.h"

ALLEGRO_SAMPLE *wood_move = NULL;
ALLEGRO_SAMPLE *wood_success = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *Help = NULL;
ALLEGRO_BITMAP *Block = NULL;
ALLEGRO_BITMAP *Block1 = NULL;
ALLEGRO_BITMAP *Block2 = NULL;
ALLEGRO_BITMAP *SoundButton = NULL;
ALLEGRO_BITMAP *SoundOn = NULL;
ALLEGRO_BITMAP *SoundOff = NULL;
ALLEGRO_BITMAP *End = NULL;
ALLEGRO_BITMAP *Home = NULL;
ALLEGRO_BITMAP *Back = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_MONITOR_INFO resolution;

/* game area represented by matrices
 * 9 represents Walls, 1 represents Vertical Blocks and 2 represents Horizontal Blocks
 */
int map[8][8]= {
    9, 9, 9, 9, 9, 9, 9, 9,
    9, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 9,
    9, 0, 0, 0, 0, 0, 0, 9,
    9, 9, 9, 9, 9, 9, 9, 9
  };
int BlockSize = 1;
double Scale = 1;

int main(void) {
    /* checking initialise errors */
    if(!al_init()){
      fprintf(stderr, "failed to initialize allegro!\n");
      exit(-1);
    }

    if(!al_init_font_addon()){
      fprintf(stderr, "failed to initialize font addon!\n");
      exit(-1);
    }

    if(!al_init_ttf_addon()){
      fprintf(stderr, "failed to initialize ttf addon!\n");
      exit(-1);
    }

    if(!al_init_primitives_addon()){
      fprintf(stderr, "failed to initialize primitive addon!\n");
      exit(-1);
    }

    if(!al_init_image_addon()){
      fprintf(stderr, "failed to initialize image addon!\n");
      exit(-1);
    }

    if(!al_install_audio()){
      fprintf(stderr, "failed to install audio!\n");
      exit(-1);
    }

    if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize acodec addon!\n");
      exit(-1);
    }

    if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      exit(-1);
    }

    wood_move = al_load_sample("media/audio/wood_move.ogg");
    if (!wood_move){
      fprintf(stderr, "failed to load wood_move!\n");
      exit(-1);
    }

    wood_success = al_load_sample("media/audio/wood_success.wav");
    if (!wood_success){
      fprintf(stderr, "failed to load wood_success!\n");
      al_destroy_sample(wood_move);
      exit(-1);
    }


    timer = al_create_timer(1.0 / FPS);
    if(!timer){
      fprintf(stderr, "failed to create timer!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      exit(-1);
    }

    al_get_monitor_info(0, &resolution);
    display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
    if(!display){
      fprintf(stderr, "failed to create display!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_timer(timer);
      exit(-1);
    }

    /* scale the components with respect to the screen resolution */
    if (SCREENHEIGHT <= 700){
        BlockSize = 40;
        Scale = 0.4;
    }
    else if (SCREENHEIGHT <= 850){
        BlockSize = 60;
        Scale = 0.6;
    }
    else if(SCREENHEIGHT <= 1280){
      BlockSize = 80;
      Scale = 0.8;
    }
    else if(SCREENHEIGHT <= 2560){
      BlockSize = 100;
      Scale = 1;
    }
    else {
      BlockSize = 200;
      Scale = 2;
    }

    background = al_load_bitmap("media/img/background.png");
    if(!background) {
      fprintf(stderr, "failed to load background!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_timer(timer);
      al_destroy_display(display);
      exit(-1);
    }

    Help = al_load_bitmap("media/img/help.png");
    if(!Help) {
      fprintf(stderr, "failed to load help!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_timer(timer);
      al_destroy_display(display);
      al_destroy_bitmap(background);
      exit(-1);
    }

    Block1 = al_load_bitmap("media/img/Block1.png");
    if(!Block1) {
      fprintf(stderr, "failed to load Block1!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_timer(timer);
      al_destroy_display(display);
      al_destroy_bitmap(background);
      al_destroy_bitmap(Help);
      exit(-1);
    }

    Block2 = al_load_bitmap("media/img/Block2.png");
    if(!Block2) {
      fprintf(stderr, "failed to load Block2!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_timer(timer);
      al_destroy_display(display);
      al_destroy_bitmap(background);
      al_destroy_bitmap(Help);
      al_destroy_bitmap(Block1);
      exit(-1);
    }

    SoundOn = al_load_bitmap("media/img/SoundOn.png");
    if(!SoundOn) {
      fprintf(stderr, "failed to load SoundOn!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_timer(timer);
      al_destroy_display(display);
      al_destroy_bitmap(background);
      al_destroy_bitmap(Help);
      al_destroy_bitmap(Block1);
      al_destroy_bitmap(Block2);
      exit(-1);
    }

    SoundOff = al_load_bitmap("media/img/SoundOff.png");
    if(!SoundOff) {
      fprintf(stderr, "failed to load SoundOff!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_timer(timer);
      al_destroy_display(display);
      al_destroy_bitmap(background);
      al_destroy_bitmap(Help);
      al_destroy_bitmap(Block1);
      al_destroy_bitmap(Block2);
      al_destroy_bitmap(SoundOn);
      exit(-1);
    }

    queue = al_create_event_queue();
    if(!queue){
      fprintf(stderr, "failed to create event queue!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_bitmap(background);
      al_destroy_bitmap(Help);
      al_destroy_bitmap(Block1);
      al_destroy_bitmap(Block2);
      al_destroy_bitmap(SoundOn);
      al_destroy_bitmap(SoundOff);
      exit(-1);
    }

    font = al_load_font("media/font/NemoyBold.otf", 52*Scale, 0);
    if(!font){
      fprintf(stderr, "failed to load NemoyBold(thin)!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_bitmap(background);
      al_destroy_bitmap(Help);
      al_destroy_bitmap(Block1);
      al_destroy_bitmap(Block2);
      al_destroy_bitmap(SoundOn);
      al_destroy_bitmap(SoundOff);
      al_destroy_event_queue(queue);
      exit(-1);
    }

    End = al_load_bitmap("media/img/end.jpg");
    if(!End){
      fprintf(stderr, "failed to load end!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_bitmap(background);
      al_destroy_bitmap(Help);
      al_destroy_bitmap(Block1);
      al_destroy_bitmap(Block2);
      al_destroy_bitmap(SoundOn);
      al_destroy_bitmap(SoundOff);
      al_destroy_event_queue(queue);
      al_destroy_font(font);
      exit(-1);
    }

    Home = al_load_bitmap("media/img/Home.png");
    if(!Home){
      fprintf(stderr, "failed to load home!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_bitmap(background);
      al_destroy_bitmap(Help);
      al_destroy_bitmap(Block1);
      al_destroy_bitmap(Block2);
      al_destroy_bitmap(SoundOn);
      al_destroy_bitmap(SoundOff);
      al_destroy_event_queue(queue);
      al_destroy_font(font);
      al_destroy_bitmap(End);
      exit(-1);
    }

    Back = al_load_bitmap("media/img/Back.png");
    if(!Back){
      fprintf(stderr, "failed to load back!\n");
      al_destroy_sample(wood_move);
      al_destroy_sample(wood_success);
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_bitmap(background);
      al_destroy_bitmap(Help);
      al_destroy_bitmap(Block1);
      al_destroy_bitmap(Block2);
      al_destroy_bitmap(SoundOn);
      al_destroy_bitmap(SoundOff);
      al_destroy_event_queue(queue);
      al_destroy_font(font);
      al_destroy_bitmap(End);
      al_destroy_bitmap(Home);
      exit(-1);
    }

    al_install_keyboard();
    al_install_mouse();

    /* registering the event source */
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    ALLEGRO_EVENT click;

    Block = Block1;
    int lwl = 0;
    int downX = 0;
    int downY = 0;
    SoundButton = SoundOn;
    int sound = sound_on;

    /* loading level 0 which is tutorial */
    int finish_line = level(&lwl);

    al_start_timer(timer);

    menu:
    while(1) {
        al_wait_for_event(queue, &click);

        /* check if user click close button */
        if (click.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            goto end;

        al_clear_to_color(al_map_rgb(0, 0, 0));

        draw_menu();

        if(click.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            /* check if user tap play */
            if(click.mouse.x >= SCREENWIDTH/2-200*Scale && click.mouse.y >= SCREENSPACE &&
               click.mouse.x <= SCREENWIDTH/2+200*Scale && click.mouse.y <= SCREENSPACE+130*Scale){
                  goto game_screen;
               }
            /* check if user tap settings */
            if(click.mouse.x >= SCREENWIDTH/2-200*Scale && click.mouse.y >= SCREENSPACE+180*Scale &&
               click.mouse.x <= SCREENWIDTH/2+200*Scale && click.mouse.y <= SCREENSPACE+310*Scale){
                 goto settings;
              }
            /* check if user tap exit */
            if(click.mouse.x >= SCREENWIDTH/2-200*Scale && click.mouse.y >= SCREENSPACE+360*Scale &&
               click.mouse.x <= SCREENWIDTH/2+200*Scale && click.mouse.y <= SCREENSPACE+490*Scale){
                  goto end;
               }
             }

        al_flip_display();
    }

    settings:
    while(1) {
        al_wait_for_event(queue, &click);

        /* check if user click close button */
        if (click.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            goto end;

        al_clear_to_color(al_map_rgb(0, 0, 0));

        draw_settings();

        if(click.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            /* check if user tap left theme */
            if(click.mouse.x >= SCREENWIDTH/2-225*Scale && click.mouse.y >= SCREENSPACE+200*Scale &&
               click.mouse.x <= SCREENWIDTH/2-225*Scale+BlockSize*2 && click.mouse.y <= SCREENSPACE+200*Scale+BlockSize)
                  Block = Block1;
            /* check if user tap right theme */
            if(click.mouse.x >= SCREENWIDTH/2+25*Scale && click.mouse.y >= SCREENSPACE+200*Scale &&
               click.mouse.x <= SCREENWIDTH/2+25*Scale+BlockSize*2 && click.mouse.y <= SCREENSPACE+200*Scale+BlockSize)
                  Block = Block2;
            /* check if user tap sound */
            if(click.mouse.x >= SCREENWIDTH/2-50*Scale && click.mouse.y >= SCREENSPACE+350*Scale &&
              click.mouse.x <= SCREENWIDTH/2+50*Scale && click.mouse.y <= SCREENSPACE+450*Scale){
                if(sound){
                  sound = sound_off;
                  /* changing the bitmap */
                  SoundButton = SoundOff;
                }
                else{
                  sound = sound_on;
                  /* changing the bitmap */
                  SoundButton = SoundOn;
                }
              }
            /* check if user tap back */
            if(click.mouse.x >= SCREENWIDTH/2-125*Scale && click.mouse.y >= SCREENSPACE+475*Scale &&
               click.mouse.x <= SCREENWIDTH/2+125*Scale && click.mouse.y <= SCREENSPACE+575*Scale){
                  goto menu;
               }
             }

        al_flip_display();
    }

    game_screen:
    while(1) {
        al_wait_for_event(queue, &click);

    	  /* check if user click close button */
        if (click.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            goto end;

    	  al_clear_to_color(al_map_rgb(0, 0, 0));

        draw_game_area(finish_line, lwl);

        draw();/* drawing Blocks */

    	  if(click.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(click.mouse.x >=0 && lwl==1)/* on tutorial screen */
                finish_line = level(&lwl);

            downX = click.mouse.x;
            downY = click.mouse.y;

            /* check if user tap home button */
            if(click.mouse.x >= COEFFICIENTCOLUMN+100*Scale && click.mouse.y >= 6*BlockSize+COEFFICIENTROW+55*Scale &&
               click.mouse.x <= COEFFICIENTCOLUMN+200*Scale && click.mouse.y <= 6*BlockSize+COEFFICIENTROW+155*Scale){
                 goto menu;
            }
            /* check if user tap back button */
            if(click.mouse.x >= COEFFICIENTCOLUMN+300*Scale && click.mouse.y >= 6*BlockSize+COEFFICIENTROW+55*Scale &&
               click.mouse.x <= COEFFICIENTCOLUMN+400*Scale && click.mouse.y <= 6*BlockSize+COEFFICIENTROW+150*Scale){
                 goto end;
            }
          }

        if(click.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
          detect_click(click.mouse.x, click.mouse.y, downX, downY, sound);
        }

        /* When level is finished */
    	  if((a[0].column+1) == 7){
          printf("Puzzle Solved Successfully\n");
          for(int i=0; i<99; ++i){
            al_draw_filled_rounded_rectangle(BlockSize+COEFFICIENTCOLUMN, 3*BlockSize+COEFFICIENTROW, BlockSize+COEFFICIENTCOLUMN+432*Scale, 3*BlockSize+COEFFICIENTROW+125*Scale, 50*Scale, 50*Scale, BLACK);
            al_draw_textf(font, WHITE, BlockSize+COEFFICIENTCOLUMN+32, 3*BlockSize+COEFFICIENTROW+15, 0, "Successful");
            if(sound)
                al_play_sample(wood_success, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            al_flip_display();
        }
        finish_line = level(&lwl);
        if(finish_line == -1){
            goto finish;
        }
      }
	      al_flip_display();
    }

    finish:
    while(1) {
        al_wait_for_event(queue, &click);

        /* check if user click close button */
        if (click.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            goto end;

        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_draw_bitmap(End, (SCREENWIDTH-852)/2, 0, 0);

        al_draw_textf(font, WHITE, SCREENWIDTH/2-175*Scale, SCREENHEIGHT/2, 0, "Main Menu");

        if(click.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            /* when user tap anywhere */
            if(click.mouse.x >= 0){
                  lwl = 1;
                  finish_line = level(&lwl);
                  goto menu;
               }
             }

        al_flip_display();
    }

    end:
    /* deleting the initialized macros */
    al_destroy_sample(wood_move);
    al_destroy_sample(wood_success);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(background);
    al_destroy_bitmap(Help);
    al_destroy_bitmap(Block1);
    al_destroy_bitmap(Block2);
    al_destroy_bitmap(SoundOn);
    al_destroy_bitmap(SoundOff);
    al_destroy_font(font);
    al_destroy_bitmap(End);
    al_destroy_bitmap(Home);
    al_destroy_bitmap(Back);
    al_shutdown_image_addon();
    al_uninstall_keyboard();
    al_shutdown_primitives_addon();
    al_uninstall_system();
    printf("Game is terminated succesfully\n");

  	return 0;
}
