#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "game.h"


/*
 * Renders the base layer as laid out above uses the curses library.
 */
void render_base_layer(void) {

  //REMOVE CLEAR TO MANUALLY INPUT IN MAIN
    initscr();    // Initializes the screen
    clear();      // Clears the screen
    curs_set(0);  // Hides the cursor

    /*
     * The following three towers and move count are printed to the
     * terminal screen as the default background.
     */
    
    /* Tower 1 */
    for(int y = 4; y < 10; y++) {
      mvprintw(y, 10, "|");
    }
    for(int x = 5; x < 16; x++) {
      mvprintw(10, x, "-");
    }

    /* Tower 2 */
    for(int y = 4; y < 10; y++) {
      mvprintw(y, 24, "|");
    }
    for(int x = 19; x < 30; x++) {
      mvprintw(10, x, "-");
    }

    /* Tower 3 */
    for(int y = 4; y < 10; y++) {
      mvprintw(y, 38, "|");
    }
    for(int x = 33; x < 44; x++) {
      mvprintw(10, x, "-");
    }
    
    /* Prints move count */
    mvprintw(11, 19, "#/moves = 0");
    
    refresh();
}

/* 
 * Creates the initial tower with which the game begins. (i.e. peg of size five on the bottom
 * with pegs of decreasing size (until of size 1) on top.)
 */
tower_t* initial_tower(void) {
  tower_t *itower = make_tower();
  for(int i = NUMBER_OF_DISKS; i > 0; i--) {
    push(itower, i);
  }
  return itower;
}

/*
 * Renders the given game to the screen on top of the base layer.
 */
void render_game_layer(hanoi_t *game) {
  render_base_layer();
  
  mvprintw(12, 3, "Enter source and destination towers [1-3], then hit 'enter'");
  print_disks(game->tower1, 10);
  print_disks(game->tower2, 24);
  print_disks(game->tower3, 38);
  refresh();
}

int main(void) {
  hanoi_t *hanoi = make_hanoi();    //makes three towers
  hanoi->tower1 = initial_tower();  //puts disks onto first tower

  bool flag1 = true;  //tests if user-input towers exist.
  bool flag2 = true;  //tests if user-input move is legal.
  int count = 0;      //move counter
  
  render_game_layer(hanoi);

  /* Continues playing the game until a tower is completed on the second or third space */
  while(!(is_complete_tower(hanoi->tower2)) &&
	!(is_complete_tower(hanoi->tower3))) {
    mvprintw(16, 3, "Enter source tower.");
    refresh();

    /* First user input */
    int key1 = getchar();
    mvprintw(16, 3, "Source tower: %c", key1);
    clrtoeol();
    refresh();
    
    mvprintw(18, 3, "Enter destination tower.");
    refresh();

    /* Second user input */
    int key2 = getchar();
    mvprintw(18, 3, "Destination tower: %c", key2);
    clrtoeol();
    refresh();
    getchar();
    
    tower_t *src = make_tower();  //first user input = tower
    tower_t *dest = make_tower();  //second user input = tower

    /* Takes first user input and assigns it to tower */
    if(key1 == '1') {
      src = hanoi->tower1;
    } else if (key1 == '2') {
      src = hanoi->tower2;
    } else if (key1 == '3') {
      src = hanoi->tower3;
    } else {
      flag1 = false;
    }

    /* Takes second user input and assigns it to tower */
    if(key2 == '1') {
      dest = hanoi->tower1;
    } else if (key2 == '2') {
      dest = hanoi->tower2;
    } else if (key2 == '3') {
      dest = hanoi->tower3;
    } else {
      flag1 = false;
    }

    /* Checks if first and second input and move are valid */
    if(flag1 != false && has_valid_move(src, dest)) {
      move_disk(src, dest);
      count++;
    } else {
      flag1 = true;
      flag2 = false;
    }

    render_game_layer(hanoi);
    mvprintw(11, 19, "#/moves = %d", count);
    refresh();

    /* Error code if user input is invalid */
    if(flag2 == false) {
      mvprintw(19, 3, "Error: cannnot move from tower %c to tower %c. Hit 'enter' to continue.", key1, key2);
      refresh();
      getchar();
      move(19, 3);
      clrtoeol();
      refresh();
      flag2 = true;
    }
    
    refresh();
  }

  /* Success message */
  mvprintw(20, 19, "YOU'VE WON!");
  
  refresh();
  getchar();
  endwin();
  
  return 0;
}
