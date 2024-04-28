#include "API.h"
#include "Util.h"
#include "FloodFill.h"

void Util::moveForward(char dist) {
    API::moveForward(dist);

    switch (dir) {
        case 0: x += dist; return;
        case 1: y -= dist; return;
        case 2: x -= dist; return;
        case 3: y += dist; return;
    }
}

void Util::turnLeft() {
    (void)API::turnLeft(90);
    dir = (dir+3)%4;
}

void Util::turnRight() {
    (void)API::turnRight(90);
    dir = (dir+1)%4;
}

void Util::turnAround() {
    (void)API::turnRight(180);
    dir = (dir+2)%4;
}

int Util::turnToDir(char desired) {
    if (dir == desired) {
        return 0;
    }
    else if ((dir - desired + 4)%4 == 2) {
        turnAround();
        return 1;
    }
    else if ((dir - desired + 4)%4 == 1) {
        turnLeft();
        return 2;
    }
    else {
        turnRight();
        return 3;
    }
}

void Util::reset() {
    // do something
    x = 0, y = 0, dir = 3;
}

bool Util::wallInDir(unsigned char info, char dir) {
    return (info & (1<<dir)) != 0;
}

unsigned char Util::id(char x, char y) {
    return y*16+x;
}

char Util::extractDir(unsigned char info) {
    return (info & 0x30) >> 4;
}

char Util::extractSLDist(unsigned char info) {
    return (info & 0xc0) >> 6;
}

char Util::dirToChar(char dir) {
    switch (dir) {
        case 0: return 'e';
        case 1: return 's';
        case 2: return 'w';
        default: return 'n';
    }
}

char Util::min(char in1, char in2) {
    return in1<in2?in1:in2;
}