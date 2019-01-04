/* This project is written for
 * CEN 116 course
 * Licensed under the GNU General Public License, version 3.0 (GPLv3)
 * Authors: Mustafa BOLEKEN, Uğur Can ÖZİPEK, Ümit KORKMAZER
 */
#ifndef functions
#define functions

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define FPS 10.0
#define SCREENWIDTH resolution.x2 / 2
#define SCREENHEIGHT resolution.y2

/* COEFFICIENT & BlockSize are used to determine
 * coordination from location in matrix
 */
#define COEFFICIENTCOLUMN (SCREENWIDTH-6*BlockSize)/2
#define COEFFICIENTROW 160
#define NUMBEROFBLOCKS 11
#define SCREENSPACE 250*Scale /* space between top and the components like game area etc. */

#define CENTERX al_get_bitmap_width(Block)/2
#define CENTERY al_get_bitmap_height(Block)/2

#define RED al_map_rgba_f(255, 0, 0, 1)
#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define LIGHTWOODBROWN al_map_rgb(130, 82, 1)

/* Definition of the Block */
struct Block {
    int type;
    int row;
    int column;
} a[NUMBEROFBLOCKS];

enum Types {blank, special, vertical, horizontal};
enum Sound { sound_off, sound_on};

extern int map[8][8];

int level(int*);
void draw_settings();
void draw_menu();
void draw_game_area(int, int);
void draw();
void detect_click(int, int, int, int, int);
void print_map();
void refresh_map(int);
void move_the_block(struct Block*, int, int);

extern ALLEGRO_SAMPLE *wood_move;
extern ALLEGRO_SAMPLE *wood_success;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_BITMAP *background;
extern ALLEGRO_BITMAP *Help;
extern ALLEGRO_BITMAP *Block;
extern ALLEGRO_BITMAP *Block1;
extern ALLEGRO_BITMAP *Block2;
extern ALLEGRO_BITMAP *SoundButton;
extern ALLEGRO_BITMAP *SoundOn;
extern ALLEGRO_BITMAP *SoundOff;
extern ALLEGRO_BITMAP *End;
extern ALLEGRO_BITMAP *Home;
extern ALLEGRO_BITMAP *Back;
extern ALLEGRO_EVENT_QUEUE *queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_MONITOR_INFO resolution;
extern int lwl;
extern int finish_line;
extern int BlockSize;
extern double Scale;

#endif
