/* This project is written for
 * CEN 116 course
 * Licensed under the GNU General Public License, version 3.0 (GPLv3)
 * Authors: Mustafa BOLEKEN, Uğur Can ÖZİPEK, Ümit KORKMAZER
 */
#include "functions.h"

/* draw_menu: draw the components of the menu */
void draw_menu()
{
    al_draw_bitmap(background,0,0,0);
    /* drawing play button */
    al_draw_filled_rounded_rectangle(SCREENWIDTH/2-200*Scale, SCREENSPACE, SCREENWIDTH/2+200*Scale, SCREENSPACE+130*Scale, 20*Scale, 20*Scale, BLACK);
    al_draw_textf(font, WHITE, SCREENWIDTH/2-85*Scale, SCREENSPACE+25*Scale, 0, "Play");
    /* drawing settings button */
    al_draw_filled_rounded_rectangle(SCREENWIDTH/2-200*Scale, SCREENSPACE+180*Scale, SCREENWIDTH/2+200*Scale, SCREENSPACE+310*Scale, 20*Scale, 20*Scale, BLACK);
    al_draw_textf(font, WHITE, SCREENWIDTH/2-135*Scale, SCREENSPACE+205*Scale, 0, "Settings");
    /* drawing exit button */
    al_draw_filled_rounded_rectangle(SCREENWIDTH/2-200*Scale, SCREENSPACE+360*Scale, SCREENWIDTH/2+200*Scale, SCREENSPACE+490*Scale, 20*Scale, 20*Scale, BLACK);
    al_draw_textf(font, WHITE, SCREENWIDTH/2-85*Scale, SCREENSPACE+375*Scale, 0, "Exit");
}

/* draw_settings: draw the components of the settings */
void draw_settings()
{
    al_draw_bitmap(background,0,0,0);

    al_draw_filled_rounded_rectangle(SCREENWIDTH/2-300*Scale, SCREENSPACE, SCREENWIDTH/2+300*Scale, SCREENSPACE+150*Scale, 20*Scale, 20*Scale, BLACK);
    al_draw_textf(font, WHITE, SCREENWIDTH/2-280*Scale, SCREENSPACE+25, 0, "Choose The Theme");

    al_draw_scaled_rotated_bitmap(Block1, 0, 0, SCREENWIDTH/2-225*Scale, SCREENSPACE+200*Scale, Scale, Scale, 0, 0);
    al_draw_scaled_rotated_bitmap(Block2, 0, 0, SCREENWIDTH/2+25*Scale, SCREENSPACE+200*Scale, Scale, Scale, 0, 0);

    /* drawing sound button */
    al_draw_scaled_rotated_bitmap(SoundButton, 0, 0, SCREENWIDTH/2-50*Scale, SCREENSPACE+350*Scale, Scale, Scale, 0, 0);

    /* drawing back button */
    al_draw_filled_rounded_rectangle(SCREENWIDTH/2-125*Scale, SCREENSPACE+475*Scale, SCREENWIDTH/2+125*Scale, SCREENSPACE+575*Scale, 20*Scale, 20*Scale, BLACK);
    al_draw_textf(font, WHITE, SCREENWIDTH/2-75*Scale, SCREENSPACE+485*Scale, 0, "Back");
}

/* draw_game_area: draw the layout of screen */
void draw_game_area(int finish_line, int lwl)
{
    al_draw_bitmap(background, 0, 0, 0);
    /* drawing border lines */
    al_draw_filled_rounded_rectangle(COEFFICIENTCOLUMN-50*Scale, COEFFICIENTROW-50*Scale, 6*BlockSize+COEFFICIENTCOLUMN+50*Scale, 6*BlockSize+COEFFICIENTROW+50*Scale, 50*Scale, 50*Scale, BLACK);
    /* drawing game field */
    al_draw_filled_rounded_rectangle(COEFFICIENTCOLUMN, COEFFICIENTROW, 6*BlockSize+COEFFICIENTCOLUMN, 6*BlockSize+COEFFICIENTROW, 25*Scale, 25*Scale, LIGHTWOODBROWN);
    /* drawing finish_line */
    al_draw_filled_rectangle(6*BlockSize+COEFFICIENTCOLUMN, finish_line, 6*BlockSize+COEFFICIENTCOLUMN+50*Scale, finish_line+BlockSize, LIGHTWOODBROWN);
    /* write the lwl */
    al_draw_textf(font, BLACK, COEFFICIENTCOLUMN-50*Scale+2*BlockSize, COEFFICIENTROW-50*Scale-BlockSize, 0, "Puzzle %d", lwl-1);
    al_draw_scaled_bitmap(Home, 0, 0, al_get_bitmap_width(Home), al_get_bitmap_height(Home), COEFFICIENTCOLUMN+100*Scale, 6*BlockSize+COEFFICIENTROW+55*Scale, al_get_bitmap_width(Home)*Scale, al_get_bitmap_height(Home)*Scale, 0);
    al_draw_scaled_bitmap(Back, 0, 0, al_get_bitmap_width(Back), al_get_bitmap_height(Back), COEFFICIENTCOLUMN+300*Scale, 6*BlockSize+COEFFICIENTROW+55*Scale, al_get_bitmap_width(Back)*Scale, al_get_bitmap_height(Back)*Scale, 0);
    if(lwl==1)/* check if it is tutorial screen */
      al_draw_scaled_rotated_bitmap(Help, 0, 0, COEFFICIENTCOLUMN, COEFFICIENTROW, Scale, Scale, 0, 0);

}

/* draw: draw the components */
void draw()
{
  /* a[0] is the special Block which is red */
  if(a[0].type)
    al_draw_tinted_scaled_bitmap(Block, RED, 0, 0, CENTERX*2, CENTERY*2, (a[0].column-1)*BlockSize+COEFFICIENTCOLUMN, (a[0].row-1)*BlockSize+COEFFICIENTROW, CENTERX*2*Scale, CENTERY*2*Scale, 0);
  for(int i=1; i<NUMBEROFBLOCKS; ++i)
      switch((a+i)->type) {
          case vertical:
              al_draw_scaled_bitmap(Block, 0, 0, CENTERX*2, CENTERY*2, ((a+i)->column-1)*BlockSize+COEFFICIENTCOLUMN, ((a+i)->row-1)*BlockSize+COEFFICIENTROW, CENTERX*2*Scale, CENTERY*2*Scale, 0);
              break;
          case horizontal:
              al_draw_scaled_rotated_bitmap(Block, CENTERY, CENTERX, ((a+i)->column-1)*BlockSize+COEFFICIENTCOLUMN, ((a+i)->row-1)*BlockSize+COEFFICIENTROW+CENTERY*Scale, Scale, Scale, ALLEGRO_PI / 2, 0);
              break;
      }
}

/* detect_click: check if user click on any Block */
void detect_click(int upX, int upY, int downX, int downY, int sound)
{
  for(int i=0; i<NUMBEROFBLOCKS; ++i)
      switch((a+i)->type) {
          case special: ;
          case vertical:
            if(downX >= ((a+i)->column-1)*BlockSize+COEFFICIENTCOLUMN
              && downY >= ((a+i)->row-1)*BlockSize+COEFFICIENTROW
              && downX <= ((a+i)->column+1)*BlockSize+COEFFICIENTCOLUMN
              && downY <= ((a+i)->row)*BlockSize+COEFFICIENTROW){
                /* user click left side of the Block */
                if(upX <= ((a+i)->column)*BlockSize+COEFFICIENTCOLUMN
                 && map[(a+i)->row][(a+i)->column-1] == 0){
                  move_the_block(a+i, 1, sound);
                  print_map();
                }
                /* user click right side of the Block */
                else if(upX >= ((a+i)->column)*BlockSize+COEFFICIENTCOLUMN
                 && map[(a+i)->row][(a+i)->column+2] == 0){
                  move_the_block(a+i, 2, sound);
                  print_map();
                }
              }
              break;
            case horizontal:
            if(downX >= ((a+i)->column-1)*BlockSize+COEFFICIENTCOLUMN
              && downY >= ((a+i)->row-1)*BlockSize+COEFFICIENTROW
              && downX <= ((a+i)->column)*BlockSize+COEFFICIENTCOLUMN
              && downY <= ((a+i)->row+1)*BlockSize+COEFFICIENTROW){
                /* user click top */
                if(upY <= ((a+i)->row)*BlockSize+COEFFICIENTROW
                 && map[(a+i)->row-1][(a+i)->column] == 0){
                   move_the_block(a+i, 1, sound);
                   print_map();
                }
                /* user click bottom */
                else if(upY >= ((a+i)->row)*BlockSize+COEFFICIENTROW
                 && map[(a+i)->row+2][(a+i)->column] == 0){
                   move_the_block(a+i, 2, sound);
                   print_map();
                }
              break;
            }
          }
}

/* move_the_block: update new location of block
 * in graphic and matrix with respect to the type of the Block
 */
void move_the_block(struct Block *a, int direction, int sound)
{
      if(sound)
        al_play_sample(wood_move, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      if(direction == 1) {
          switch(a->type) {
              /* move Block to left */
              case special: ;
              case vertical:
                  map[a->row][a->column+1]=0;
                  a->column--;
                  map[a->row][a->column]=1;
                  break;
              /* move Block to up */
              case horizontal:
                  map[a->row+1][a->column]=0;
                  a->row--;
                  map[a->row][a->column]=2;
                  break;
          }
      }
      else if(direction == 2) {
          switch(a->type) {
              /* move Block to right */
              case special: ;
              case vertical:
                  map[a->row][a->column]=0;
                  a->column++;
                  map[a->row][a->column+1]=1;
                  break;
              /* move Block to down */
              case horizontal:
                  map[a->row][a->column]=0;
                  a->row++;
                  map[a->row+1][a->column]=2;
                  break;
          }
      }
}

/* refresh_map: delete all things on the map */
void refresh_map(int finish)
{
    for(int i=1; i<7; ++i)
        for(int j=1; j<7; ++j)
            map[i][j]=0;
    map[finish][7]=0;
}

/* print_map: print last version of map */
void print_map()
{
    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j)
            printf("%d ", map[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

/* components of levels */
int level(int *i)
{
    if(*i==0) {
        *i=1;
        refresh_map(4);
        /* location of the components */
        a[0].row=0;
        a[0].column=0;
        a[0].type=blank;
        a[1].row=0;
        a[1].column=0;
        a[1].type=blank;
        a[2].row=0;
        a[2].column=0;
        a[2].type=blank;
        a[3].row=0;
        a[3].column=0;
        a[3].type=blank;
        a[4].row=0;
        a[4].column=0;
        a[4].type=blank;
        a[5].row=0;
        a[5].column=0;
        a[5].type=blank;
        a[6].row=0;
        a[6].column=0;
        a[6].type=blank;
        a[7].row=0;
        a[7].column=0;
        a[7].type=blank;
        a[8].row=0;
        a[8].column=0;
        a[8].type=blank;
        a[9].row=0;
        a[9].column=0;
        a[9].type=blank;
        a[10].row=0;
        a[10].column=0;
        a[10].type=blank;
        printf("Tutorial Loaded Succesfully\n");
        return 3*BlockSize+COEFFICIENTROW; /* return the location of finish line */
    }

    else if(*i==1) {
        *i=2;
        refresh_map(4);
        /* location of the components */
        a[0].row=4;
        a[0].column=2;
        a[0].type=special;
        map[a[0].row][a[0].column] = 1;
        map[a[0].row][a[0].column+1] = 1;
        a[1].row=1;
        a[1].column=6;
        a[1].type=horizontal;
        map[a[1].row][a[1].column] = 2;
        map[a[1].row+1][a[1].column] = 2;
        a[2].row=3;
        a[2].column=5;
        a[2].type=vertical;
        map[a[2].row][a[2].column] = 1;
        map[a[2].row][a[2].column+1] = 1;
        a[3].row=6;
        a[3].column=4;
        a[3].type=vertical;
        map[a[3].row][a[3].column] = 1;
        map[a[3].row][a[3].column+1] = 1;
        a[4].row=1;
        a[4].column=4;
        a[4].type=vertical;
        map[a[4].row][a[4].column] = 1;
        map[a[4].row][a[4].column+1] = 1;
        a[5].row=5;
        a[5].column=3;
        a[5].type=horizontal;
        map[a[5].row][a[5].column] = 2;
        map[a[5].row+1][a[5].column] = 2;
        a[6].row=6;
        a[6].column=1;
        a[6].type=vertical;
        map[a[6].row][a[6].column] = 1;
        map[a[6].row][a[6].column+1] = 1;
        a[7].row=4;
        a[7].column=4;
        a[7].type=horizontal;
        map[a[7].row][a[7].column] = 2;
        map[a[7].row+1][a[7].column] = 2;
        a[8].row=4;
        a[8].column=5;
        a[8].type=horizontal;
        map[a[8].row][a[8].column] = 2;
        map[a[8].row+1][a[8].column] = 2;
        a[9].row=0;
        a[9].column=0;
        a[9].type=blank;
        a[10].row=0;
        a[10].column=0;
        a[10].type=blank;
        printf("First Puzzle Loaded Succesfully\n");
        return 3*BlockSize+COEFFICIENTROW; /* return the location of finish line */
    }

    else if(*i==2) {
        *i=3;
        refresh_map(2);
        /* location of the components */
        a[0].row=2;
        a[0].column=3;
        a[0].type=special;
        map[a[0].row][a[0].column] = 1;
        map[a[0].row][a[0].column+1] = 1;
        a[1].row=1;
        a[1].column=6;
        a[1].type=horizontal;
        map[a[1].row][a[1].column] = 2;
        map[a[1].row+1][a[1].column] = 2;
        a[2].row=3;
        a[2].column=5;
        a[2].type=vertical;
        map[a[2].row][a[2].column] = 1;
        map[a[2].row][a[2].column+1] = 1;
        a[3].row=1;
        a[3].column=1;
        a[3].type=vertical;
        map[a[3].row][a[3].column] = 1;
        map[a[3].row][a[3].column+1] = 1;
        a[4].row=1;
        a[4].column=4;
        a[4].type=vertical;
        map[a[4].row][a[4].column] = 1;
        map[a[4].row][a[4].column+1] = 1;
        a[5].row=2;
        a[5].column=2;
        a[5].type=horizontal;
        map[a[5].row][a[5].column] = 2;
        map[a[5].row+1][a[5].column] = 2;
        a[6].row=6;
        a[6].column=1;
        a[6].type=vertical;
        map[a[6].row][a[6].column] = 1;
        map[a[6].row][a[6].column+1] = 1;
        a[7].row=5;
        a[7].column=3;
        a[7].type=horizontal;
        map[a[7].row][a[7].column] = 2;
        map[a[7].row+1][a[7].column] = 2;
        a[8].row=3;
        a[8].column=3;
        a[8].type=vertical;
        map[a[8].row][a[8].column] = 1;
        map[a[8].row][a[8].column+1] = 1;
        a[9].row=4;
        a[9].column=6;
        a[9].type=horizontal;
        map[a[9].row][a[9].column] = 1;
        map[a[9].row+1][a[9].column] = 1;
        a[10].row=5;
        a[10].column=4;
        a[10].type=vertical;
        map[a[10].row][a[10].column] = 1;
        map[a[10].row][a[10].column+1] = 1;
        printf("Second Puzzle Loaded Succesfully\n");
        return 1*BlockSize+COEFFICIENTROW; /* return the location of finish line */
      }

      else if(*i==3) {
          *i=4;
          refresh_map(3);
          /* location of the components */
          a[0].row=3;
          a[0].column=2;
          a[0].type=special;
          map[a[0].row][a[0].column] = 1;
          map[a[0].row][a[0].column+1] = 1;
          a[1].row=2;
          a[1].column=4;
          a[1].type=horizontal;
          map[a[1].row][a[1].column] = 2;
          map[a[1].row+1][a[1].column] = 2;
          a[2].row=1;
          a[2].column=3;
          a[2].type=vertical;
          map[a[2].row][a[2].column] = 1;
          map[a[2].row][a[2].column+1] = 1;
          a[3].row=2;
          a[3].column=5;
          a[3].type=vertical;
          map[a[3].row][a[3].column] = 1;
          map[a[3].row][a[3].column+1] = 1;
          a[4].row=4;
          a[4].column=4;
          a[4].type=vertical;
          map[a[4].row][a[4].column] = 1;
          map[a[4].row][a[4].column+1] = 1;
          a[5].row=3;
          a[5].column=6;
          a[5].type=horizontal;
          map[a[5].row][a[5].column] = 2;
          map[a[5].row+1][a[5].column] = 2;
          a[6].row=0;
          a[6].column=0;
          a[6].type=blank;
          a[7].row=0;
          a[7].column=0;
          a[7].type=blank;
          a[8].row=0;
          a[8].column=0;
          a[8].type=blank;
          a[9].row=0;
          a[9].column=0;
          a[9].type=blank;
          a[10].row=0;
          a[10].column=0;
          a[10].type=blank;
          printf("Third Puzzle Loaded Succesfully\n");
          return 2*BlockSize+COEFFICIENTROW; /* return the location of finish line */
        }

    else{
        return -1;
    }
}
