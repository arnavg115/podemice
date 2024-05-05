#include "API.h"
#include "Util.h"
#include "Logger.h"
#include "MinHeap.h"
#include "FloodFill.h"

char x = 0, y = 0, dir = 3;
char cx = 7, cy = 7, round = 1;
bool reachedGoal = false;
unsigned char infos[256] = {};
short int dists[256];
bool explored[256] = {};
bool closed[256];

int headbash() {
    char dx = (dir == 0 ? 1 : (dir == 2 ? -1 : 0));
    char dy = (dir == 3 ? 1 : (dir == 1 ? -1 : 0));
    int delta = 1;

    while (!Util::wallInDir(infos[Util::id(x+delta*dx, y+delta*dy)], dir)) {
        char curX = x+delta*dx;
        char curY = y+delta*dy;
        short int min = dists[16*(curY+dy)+curX+dx];
        unsigned char id = Util::id(curX, curY);
        unsigned char info = infos[id];

        if (curX < 15 && !Util::wallInDir(info, 0) && dists[id+1]  < min ||
            curY > 0  && !Util::wallInDir(info, 1) && dists[id-16] < min ||
            curX > 0  && !Util::wallInDir(info, 2) && dists[id-1]  < min ||
            curX < 15 && !Util::wallInDir(info, 3) && dists[id+16] < min ) {
                return Util::moveForward(delta);
        }

        delta++;
    }

    return Util::moveForward(delta);
}

int findBestDir() {
    short int min = 0x7fff;
    char minDir = -1;
    unsigned char id = Util::id(x, y);
    unsigned char info = infos[id];

    if (x < 15 && !Util::wallInDir(info, 0) && 
            (dists[id+1] < min || dir == 0 && dists[id+1] <= min)) {
        minDir = 0;
        min = dists[id+1];
    }

    if (y > 0 && !Util::wallInDir(info, 1) && 
            (dists[id-16] < min || dir == 1 && dists[id-16] <= min)) {
        minDir = 1;
        min = dists[id-16];
    }

    if (x > 0 && !Util::wallInDir(info, 2) && 
            (dists[id-1] < min || dir == 2 && dists[id-1] <= min)) {
        minDir = 2;
        min = dists[id-1];
    }

    if (y < 16 && !Util::wallInDir(info, 3) && 
            (dists[id+16] < min || dir == 3 && dists[id+16] <= min)) {
        minDir = 3;
        min = dists[id+16];
    }

    int turn = Util::turnToDir(minDir);
    if (turn != 0) {
        return turn;
    }
    else if (round > 2 && !reachedGoal)
        return headbash();
    else
        return Util::moveForward();
}

void floodFillWithTime(bool findCenter) {
    for (int i=0; i<256; ++i) {
        dists[i] = 0x7fff;
        closed[i] = false;
    }

    MinHeap q;
    
    if (findCenter) {
        dists[Util::id(cx  , cy  )] = 0;
        dists[Util::id(cx+1, cy  )] = 0;
        dists[Util::id(cx  , cy+1)] = 0;
        dists[Util::id(cx+1, cy+1)] = 0;

        heap_node n1 = {Util::id(cx  , cy  ),0};
        heap_node n2 = {Util::id(cx+1, cy  ),0};
        heap_node n3 = {Util::id(cx  , cy+1),0};
        heap_node n4 = {Util::id(cx+1, cy+1),0};
        q.push(n1); q.push(n2); q.push(n3); q.push(n4);
    }
    else {
        dists[0] = 0;
        heap_node n = {Util::id(0, 0),0};
        q.push(n);
    }

    while (q.get_size() != 0) {
        heap_node node = q.pop();
        unsigned char id = node.id;
        short int i = node.dist;
        char x = id%16;
        char y = id/16;

        if (closed[id])
            continue;

        unsigned char info = infos[id];
        char dir = Util::extractDir(info);
        char distInRun = Util::extractSLDist(info);

        if (x > 0 && dists[id-1] > i + (round <= 2 ? 0 : dir == 2 ? 3-distInRun : 5) &&
                !Util::wallInDir(info, 2)) {
            if (round <= 2) {
                dists[id-1] = i+1;
            }
            else if (dir != 2 && i != 0) {
                dists[id-1] = i+6;
                infos[id-1] &= ~0xc0;
            }
            else {
                dists[id-1] = i+4-distInRun;
                infos[id-1] &= ~0xc0;
                infos[id-1] += Util::min(3, distInRun+1) << 6;
            }

            infos[id-1] &= ~0x30;
            infos[id-1] += 2 << 4;

            heap_node n = {id-1, dists[id-1]};
            q.push(n);
        }
        if (x < 15 && dists[id+1] > i + (round <= 2 ? 0 : dir == 0 ? 3-distInRun : 5) &&
                !Util::wallInDir(info, 0)) {
            if (round <= 2) {
                dists[id+1] = i+1;
            }
            else if (dir != 0 && i != 0) {
                dists[id+1] = i+6;
                infos[id+1] &= ~0xc0;
            }
            else {
                dists[id+1] = i+4-distInRun;
                infos[id+1] &= ~0xc0;
                infos[id+1] += Util::min(3, distInRun+1) << 6;
            }

            infos[id+1] &= ~0x30;
            infos[id+1] += 0 << 4;

            heap_node n = {id+1, dists[id+1]};
            q.push(n);
        }
        if (y > 0 && dists[id-16] > i + (round <= 2 ? 0 : dir == 1 ? 3-distInRun : 5) &&
                !Util::wallInDir(info, 1)) {
            if (round <= 2) {
                dists[id-16] = i+1;
            }
            else if (dir != 1 && i != 0) {
                dists[id-16] = i+6;
                infos[id-16] &= ~0xc0;
            }
            else {
                dists[id-16] = i+4-distInRun;
                infos[id-16] &= ~0xc0;
                infos[id-16] += Util::min(3, distInRun+1) << 6;
            }

            infos[id-16] &= ~0x30;
            infos[id-16] += 1 << 4;

            heap_node n = {id-16, dists[id-16]};
            q.push(n);
        }
        if (y < 15 && dists[id+16] > i + (round <= 2 ? 0 : dir == 3 ? 3-distInRun : 5) &&
                !Util::wallInDir(info, 3)) {
            if (round <= 2) {
                dists[id+16] = i+1;
            }
            else if (dir != 3 && i != 0) {
                dists[id+16] = i+6;
                infos[id+16] &= ~0xc0;
            }
            else {
                dists[id+16] = i+4-distInRun;
                infos[id+16] &= ~0xc0;
                infos[id+16] += Util::min(3, distInRun+1) << 6;
            }

            infos[id+16] &= ~0x30;
            infos[id+16] += 3 << 4;

            heap_node n = {id+16, dists[id+16]};
            q.push(n);
        }

        closed[id] = true;
    }
}

int getCommand() {
    Logger::logWalls();
    explored[Util::id(x,y)] = true;

    if ((x == cx || x == cx+1) && (y == cy || y == cy+1) &&
            !reachedGoal) {
        round++;

        if (round > 3) Util::reset();
        else reachedGoal = true;
    }
    else if (x == 0 && y == 0 && round > 1) {
        reachedGoal = false;
        round++;
        Logger::blockAllUnseenWalls();
    }

    floodFillWithTime(!reachedGoal);
    return findBestDir();
}