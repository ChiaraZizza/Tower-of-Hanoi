#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ncurses.h>
#include "game.h"

/* 
 * Allocates a new disk on the heap with the given value.
 */
disk_t* make_disk(int val, disk_t *next) {
  disk_t *new_disk = (disk_t*)malloc(sizeof(disk_t));
  new_disk->val = val;
  new_disk->next = next;
  return new_disk;
}

/*
 * Allocates a new, empty tower on the heap.
 */
tower_t* make_tower(void) {
  tower_t *new_tow = (tower_t*)malloc(sizeof(tower_t));
  new_tow->first = NULL;
  return new_tow;
}

/*
 * Allocates a new, empty hanoi game on the heap.
 */
hanoi_t* make_hanoi(void) {
  hanoi_t *new_hanoi = (hanoi_t*)malloc(sizeof(hanoi_t));
  new_hanoi->moves = 0;
  new_hanoi->tower1 = make_tower();
  new_hanoi->tower2 = make_tower();
  new_hanoi->tower3 = make_tower();
  return new_hanoi;
}

/*
 * Frees the given disk.
 */
void free_disk(disk_t *disk) {
  free(disk);
}

/*
 * Frees the given tower.
 */
void free_tower(tower_t *tow) {
  disk_t *cur = tow->first;
  while (cur != NULL) {
    disk_t *next = cur->next;
    free_disk(cur);
    cur = next;
  }
  free(tow);
}

/*
 * Frees the given hanoi game.
 */
void free_hanoi(hanoi_t *game) {
  free_tower(game->tower1);
  free_tower(game->tower2);
  free_tower(game->tower3);
  free(game);
}

/*
 * Counts the size of the tower.
 */
int size(tower_t *tow) {
    disk_t* cur = tow->first;
    int count = 0;
    while (cur != NULL){
        cur = cur->next;
        count++;
    }
    return count;
}

/*
 * Removes the top disk from a non-empty tower.
 */
int pop(tower_t *tow) {
  int val = tow->first->val;
  if(tow->first == NULL) {
    return -1;
  } else {
    tow->first = tow->first->next;
    return val;
  }
}

/*
 * Puts the disk on top of the tower.
 */
void push(tower_t *tow, int val) {
  disk_t* new_disk = make_disk(val, tow->first);
  tow->first = new_disk;
}

/*
 * Returns true iff there is a valid move from the source tower to the
 * destination tower according to the rules of the Tower of Hanoi
 */
bool has_valid_move(tower_t *src, tower_t *dest) {
  disk_t *start = src->first;
  disk_t *end = dest->first;
  if(start == NULL) {
    return false;
  }
  if(end == NULL) {
    return true;
  }
  if(start->val < end->val) {
    return true;
  }
  return false;
}

/*
 * Performs a legal move of a disk from the source tower to the destination tower
 * (pre: has_valid_move(src, dest) is true)
 */
void move_disk(tower_t *src, tower_t *dest) {
  disk_t *start = src->first;
  push(dest, pop(src));
  free_disk(start);
}

/*
 * Returns true iff the tower is complete (i.e., has all of the disks in
 * descending order of size)
 */
bool is_complete_tower(tower_t *src) {
  if(size(src) == NUMBER_OF_DISKS) {
    return true;
  }
  return false;
}

/*
 * Prints the disks onto the screen in the proper positions on the tower.
 */
void print_disks(tower_t *tow, int offset) {
  disk_t *cur = tow->first;
  int s = size(tow);
  int height = 10 - s;
  int rad;
  while(cur != NULL) {
    rad = cur->val;
    for(int i = offset - rad; i < offset; i++) {
      mvprintw(height, i, "-");
    }
    for(int j = offset + 1; j < offset + 1 + rad; j++) {
      mvprintw(height, j, "-");
    }
    cur = cur->next;
    height += 1;
  }
}
