#include "maze.h"

int main () {
    // Get Width and Height
    printf("Maze Width : ");
    scanf("%d", &WIDTH);
    printf("Maze Height : ");
    scanf("%d", &HEIGHT);

    MazeAlloc();

    if (WIDTH > 1 && HEIGHT > 1) {
        MazeEllers();
    }
    else {
        Maze1D();
    }

    // MazePrint(); // for debugging
    MazeOut();
    MazeDealloc();
}

void MazeAlloc() {
    int i, j;
    maze = malloc (sizeof(cell*) * HEIGHT);
    for (i = 0; i < HEIGHT; i++) {
        maze[i] = malloc (sizeof(cell) * WIDTH);
        for (j = 0; j < WIDTH; j++) {
            maze[i][j].right = -1;
            maze[i][j].bottom = -1;
            maze[i][j].setNum = -1;
        }
    }
    return;
}

void MazeDealloc() {
    int i;
    for (i = 0; i < HEIGHT; i++) {
        free(maze[i]);
    }
    free(maze);
    return;
}

void MazeEllers() {
    int i, j;
    int newSetNum = 1;
    int bottomFlag = 0;

    srand(time(NULL));    
    maze[0][0].setNum = newSetNum;
    
    for (i = 0; i < HEIGHT - 1; i++) {  // Last Line needs Exceptional Process
        // Pull Down Set Num where there is no bottom
        for (j = 0; j < WIDTH; j++) {
            if (i > 0) {
                if(maze[i-1][j].bottom == 0) {
                    maze[i][j].setNum = maze[i-1][j].setNum;
                }
            }
        }

        // Set Set Num        
        for (j = 0; j < WIDTH; j++) {
            if (maze[i][j].setNum == -1) {
                newSetNum++;
                maze[i][j].setNum = newSetNum;
            }

        }

        // Set Right Wall
        for (j = 0; j < WIDTH - 1; j++) {
            if (maze[i][j].right == -1) {
                if(maze[i][j+1].setNum == maze[i][j].setNum){
                    maze[i][j].right = 1;
                }
                else {
                    maze[i][j].right = rand()%2;
                }
            }
        }
        maze[i][WIDTH - 1].right = 1;   // Right End always has wall
        
        // Adjust Set Num
        for (j = 0; j <WIDTH; j++) {
            if (maze[i][j].right == 0) {
                SetNumAdj(i, maze[i][j].setNum, maze[i][j+1].setNum); // Does not go out of bound since right end has wall
            }
        }

        // Set Bottom Wall
        bottomFlag = 0;
        for (j = 0; j < WIDTH - 1; j++) {
            if (maze[i][j].setNum != maze[i][j+1].setNum) {
                if (bottomFlag == 0) {
                    maze[i][j].bottom = 0;
                }
                else {
                    maze[i][j].bottom = rand()%2;
                }
                bottomFlag = 0;            
            }
            else {
                maze[i][j].bottom = rand()%2;
                if (maze[i][j].bottom == 0) {
                    bottomFlag = 1;
                }
            }
        }
        //  bottomWall of Right End
        if (bottomFlag == 0) {
            maze[i][WIDTH - 1].bottom = 0;
        }
        else {
            maze[i][WIDTH - 1].bottom = rand()%2; 
        }
    }

    // Last Line
    // Pull Down Set Num
    for (j = 0; j < WIDTH; j++) {
        if (maze[i-1][j].bottom == 0) {
            maze[i][j].setNum = maze[i-1][j].setNum;
        }
        else {
            newSetNum++;
            maze[i][j].setNum = newSetNum;
        }    
    }

    // Set or Destroy Right Wall
    for (j = 0; j < WIDTH - 1 ; j++) {
        if (maze[HEIGHT-1][j].setNum != maze[HEIGHT-1][j+1].setNum) {
            maze[HEIGHT-1][j].right = 0;
        }
        else {
            maze[HEIGHT-1][j].right = 1;
        }
        maze[HEIGHT-1][j].bottom = 1;
    }

    // Edge
    maze[HEIGHT-1][WIDTH-1].bottom = 1;
    maze[HEIGHT-1][WIDTH-1].right = 1;
}

void SetNumAdj(int height, int to, int from) {
    int j;
    for (j = 0; j < WIDTH; j++) {
        if (maze[height][j].setNum == from) {
            maze[height][j].setNum = to;
        }
    }
    return;
}


void MazePrint() {
    int i, j;

    // First Line
    printf("+");
    for (j = 0; j <WIDTH; j++) {
        printf("-+");
    }
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        // Vertical
        printf("|");
        for (j = 0; j <WIDTH; j++) {
            if (maze[i][j].right == 1){
                printf("%d|", maze[i][j].setNum);
            }
            else if (maze[i][j].right == 0) {
                printf("%d ", maze[i][j].setNum);
            }
            else {
                printf("%d?", maze[i][j].setNum);
            }
        }
        printf("\n+");

        // Horizontal
        for (j = 0; j < WIDTH; j++) {
            if(maze[i][j].bottom == 1) {
                printf("-+");
            }
            else if (maze[i][j].bottom == 0) {
                printf(" +");
            }
            else {
                printf("?+");
            }
        }
        printf("\n");
    }
}

void Maze1D () {
    int i;
    if (HEIGHT == 1) {
        for (i = 0; i < WIDTH - 1; i++) {
            maze[0][i].right = 0;
            maze[0][i].bottom = 1;
        }
        maze[0][WIDTH-1].right = 1;
        maze[0][WIDTH-1].bottom = 1;        
    }
    else if (WIDTH == 1) {
        for (i = 0; i < HEIGHT - 1; i++) {
            maze[i][0].right = 1;
            maze[i][0].bottom = 0;
        }
        maze[HEIGHT-1][0].right = 1;
        maze[HEIGHT-1][0].bottom = 1;
    }
    else {
        printf("Error: Invalid Input\n");
        MazeDealloc();
        exit(1);
    }
    return;
}

void MazeOut() {
    int i, j;
    FILE* fp;
    fp = fopen("maze.maz", "wt");

    // First Line
    fprintf(fp, "+");
    for (j = 0; j <WIDTH; j++) {
        fprintf(fp, "-+");
    }
    fprintf(fp, "\n");

    for (i = 0; i < HEIGHT; i++) {
        // Vertical
        fprintf(fp, "|");
        for (j = 0; j <WIDTH; j++) {
            if (maze[i][j].right == 1){
                fprintf(fp, " |");
            }
            else {
                fprintf(fp, "  ");
            }
        }
        fprintf(fp, "\n+");

        // Horizontal
        for (j = 0; j < WIDTH; j++) {
            if(maze[i][j].bottom == 1) {
                fprintf(fp, "-+");
            }
            else {
                fprintf(fp, " +");
            }
            
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Maze File 'maze.maz' Generated.\n");
    return;
}