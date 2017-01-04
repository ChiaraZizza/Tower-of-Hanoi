#pragma once

typedef struct disk {
  int val;
  struct disk *next;
} disk_t;

typedef struct tower {
  disk_t *first;
} tower_t;

typedef struct hanoi {
  int moves;
  tower_t *tower1;
  tower_t *tower2;
  tower_t *tower3;
} hanoi_t;


#define NUMBER_OF_DISKS 5

/*
 * Allocates a new disk on the heap with the given value.
 */
disk_t* make_disk(int val, disk_t *next);

/*
 * Allocates a new, empty tower on the heap.
 */
tower_t* make_tower(void);

/*
 * Allocates a new, empty hanoi game on the heap.
 */
hanoi_t* make_hanoi(void);

/* 
 * Frees the given disk.
 */
void free_disk(disk_t *disk);

/*
 * Frees the given tower.
 */
void free_tower(tower_t *tow);

/*
 * Frees the given hanoi game.
 */
void free_hanoi(hanoi_t *game);

/*
 * Counts the size of the tower.
 */
int size(tower_t *tow);

/*
 * Removes the top disk from the tower.
 */
int pop(tower_t *tow);

/*
 * Puts the disk on top of the tower.
 */
void push(tower_t *tow, int val);

/*
 * Returns true iff there is a valid move from the source tower to the
 * destination tower according to the rules of the Tower of Hanoi
 */
bool has_valid_move(tower_t *src, tower_t *dest);

/*
 * Performs a legal move of a disk from the source tower to the destination
 * tower (pre: has_valid_move(src, dest) is true)
 */
void move_disk(tower_t *src, tower_t *dest);

/*
 * Returns true iff the tower is complete (i.e., has all of the disks in
 * descending order of size)
 */
bool is_complete_tower(tower_t *src);

/*
 * Prints the disks onto the screen in the proper positions on the tower.
 */
void print_disks(tower_t *tow, int offset);
