// ***
// *** You MUST modify this file
// ***

#include "solver.h"
#include "list.h"
#include "mazehelper.h"
#include "path.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Helper function to handle the movement logic
MazePos movePos(MazePos cur, char direction) {
    MazePos next = cur;
    if (direction == NORTH) next.ypos--;
    else if (direction == SOUTH) next.ypos++;
    else if (direction == EAST) next.xpos++;
    else if (direction == WEST) next.xpos--;
    return next;
}

PathLL* solveMaze(Maze* m) {
    PathLL* successPaths = buildPaths();
    // Buffer size: height * width + 1 for null terminator
    char* pathBuffer = malloc(((m->height * m->width) + 1) * sizeof(char));

    MazePos startPos = m->start;
    depthFirstSolve(m, startPos, pathBuffer, 0, successPaths);

    free(pathBuffer);
    return successPaths;
}

void depthFirstSolve(Maze* m, MazePos curpos, char* path, int step,
                     PathLL* successPaths) {

    // TODO (Your best bet is to modify a working implementation from HW9)
    // 1. Base Case: Check boundaries and walls
    // 1. If we reached the end, record the path
    if (atEnd(curpos, m)) {
        path[step] = '\0';
        addNode(successPaths, path);
        return;
    }

    // 2. Mark current spot as visited so we don't loop
    m->maze[curpos.ypos][curpos.xpos].visited = true;

    // 3. Try all four directions
    char dirs[] = {NORTH, SOUTH, EAST, WEST};
    for (int i = 0; i < 4; i++) {
        MazePos next = movePos(curpos, dirs[i]);
        
        // Use the provided squareOK from mazehelper.c
        if (squareOK(next, m)) {
            path[step] = dirs[i];
            depthFirstSolve(m, next, path, step + 1, successPaths);
        }
    }

    // 4. BACKTRACK: Unmark visited so other paths can explore this square
    m->maze[curpos.ypos][curpos.xpos].visited = false;
}
