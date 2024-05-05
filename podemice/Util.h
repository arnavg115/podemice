#pragma once

class Util {

public:

    static int moveForward(char dist = 1);
    static void turnLeft();
    static void turnRight();
    static void turnAround();
    static int turnToDir(char desired);
    static void reset();

    static bool wallInDir(unsigned char info, char dir);
    static unsigned char id(char x, char y);
    static char extractDir(unsigned char info);
    static char extractSLDist(unsigned char info);
    static char dirToChar(char dir);
    static char min(char in1, char in2);

};