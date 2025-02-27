#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#include <stdbool.h>


typedef struct position {
    int file;
    int line;
    int col;
} Position;

typedef struct positionList {
    struct position     p;
    struct positionList *next;
} PositionList;


extern Position makePosition(int file, int line, int col);
extern void fillPositionList(PositionList *positionList, Position p, PositionList *next);
extern bool onSameLine(Position pos1, Position pos2);

extern Position addPositions(Position p1, Position p2);
extern Position subtractPositions(Position minuend, Position subtrahend);
extern bool positionsAreEqual(Position p1, Position p2);
extern bool positionsAreNotEqual(Position p1, Position p2);
extern bool positionIsLessThan(Position p1, Position p2);
extern bool positionIsLessOrEqualTo(Position p1, Position p2);
extern bool positionIsBetween(Position p1, Position p, Position p2);

#endif
