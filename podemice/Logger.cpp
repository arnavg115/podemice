#include "API.h"
#include "Util.h"
#include "FloodFill.h"
#include "Logger.h"

char Logger::deltaIdInDir(char dir) {
    if (dir == 0) return 1;
    if (dir == 1) return -16;
    if (dir == 2) return -1;
    else return 16;
}

void Logger::logWalls() {
    unsigned char id = Util::id(x, y);

    if (API::wallFront()) {
        infos[id] |= 1<<dir;

        short int delta = deltaIdInDir(dir);
        if (id + delta >= 0 && id + delta < 256)
            infos[id + delta] |= 1 << (dir+2)%4;
    }

    if (API::wallLeft()) {
        infos[id] |= 1<<(dir+3)%4;

        short int delta = deltaIdInDir((dir+3)%4);
        if (id + delta >= 0 && id + delta < 256)
            infos[id + delta] |= 1 << (dir+1)%4;
    }

    if (API::wallRight()) {
        infos[id] |= 1<<(dir+1)%4;

        short int delta = deltaIdInDir((dir+1)%4);
        if (id + delta >= 0 && id + delta < 256)
            infos[id + delta] |= 1 << (dir+3)%4;
    }
}

void Logger::blockAllUnseenWalls() {
    for (int i=0; i<256; i++) {
        if (!explored[i]) {
            infos[i] |= 0xf;
        }
    }

    for (int i=0; i<256; i++) {
        if (explored[i]) {
            unsigned char info = infos[i];
            if (!Util::wallInDir(info, 0) && i%16 != 15) {
                infos[i+1] &= ~0x4;
            }
            if (!Util::wallInDir(info, 1) && i/16 != 0) {
                infos[i-16] &= ~0x8;
            }
            if (!Util::wallInDir(info, 2) && i%16 != 0) {
                infos[i-1] &= ~0x1;
            }
            if (!Util::wallInDir(info, 3) && i/16 != 15) {
                infos[i+16] &= ~0x2;
            }
        }
    }
}