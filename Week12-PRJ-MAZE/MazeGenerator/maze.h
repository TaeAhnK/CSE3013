#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Data Structure of Cell */
typedef struct cell {
    int right;
    int bottom;
    int setNum;
} cell;

/* Maze Info */
cell** maze;
int WIDTH;
int HEIGHT;

/* Allocate Memory for Maze */
void MazeAlloc();

/* Deallocate Mememory for Maze */
void MazeDealloc();

/* Generate Maze With Eller's Algorithm */
void MazeEllers();

/* Change All Set Number of Current height */
void SetNumAdj(int height, int to, int from);

/* Generate Maze with WIDTH 1 or HEIGHT 1 */
void Maze1D();

/* Print Maze and Set Num of Each Cell */
void MazePrint();

/* Create maze.maz file with Maze Data */
void MazeOut();