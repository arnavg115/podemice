#include "API.h"
#include "Util.h"
#include "FloodFill.h"

int Util::moveForward(char dist) {
    switch (dir) {
        case 0: x += dist; break;
        case 1: y -= dist; break;
        case 2: x -= dist; break;
        case 3: y += dist; break;
    }

    return 0x8000 | dist;
}

void Util::turnLeft() {
    dir = (dir+3)%4;
}

void Util::turnRight() {
    dir = (dir+1)%4;
}

void Util::turnAround() {
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