#ifndef REFACTORINGS_H_INCLUDED
#define REFACTORINGS_H_INCLUDED

typedef enum Refactorings {
    AVR_NO_REFACTORING = 0,
    AVR_RENAME_SYMBOL = 10,
    AVR_RENAME_CLASS = 20,
    AVR_RENAME_PACKAGE = 30,
    AVR_ADD_PARAMETER = 40,
    AVR_DEL_PARAMETER = 50,
    AVR_MOVE_PARAMETER = 60,
    AVR_MOVE_STATIC_FIELD = 70,
    AVR_MOVE_STATIC_METHOD = 80,
    AVR_MOVE_FIELD = 90,
    AVR_TURN_DYNAMIC_METHOD_TO_STATIC = 100,
    AVR_TURN_STATIC_METHOD_TO_DYNAMIC = 110,
    AVR_PULL_UP_FIELD = 120,
    AVR_PULL_UP_METHOD = 130,
    AVR_PUSH_DOWN_FIELD = 140,
    AVR_PUSH_DOWN_METHOD = 150,
    AVR_MOVE_CLASS = 160,
    AVR_MOVE_CLASS_TO_NEW_FILE = 170,
    AVR_MOVE_ALL_CLASSES_TO_NEW_FILE = 180,
    AVR_ENCAPSULATE_FIELD = 190,
    AVR_SELF_ENCAPSULATE_FIELD = 200,
    AVR_ADD_TO_IMPORT = 210,
    AVR_EXTRACT_METHOD = 220,
    AVR_EXTRACT_FUNCTION = 230,
    AVR_EXTRACT_MACRO = 240,
    AVR_REDUCE_NAMES = 250,
    AVR_EXPAND_NAMES = 260,
    AVR_ADD_ALL_POSSIBLE_IMPORTS = 270,
    AVR_SET_MOVE_TARGET = 280,
    AVR_UNDO = 290,
    AVR_MAX_AVAILABLE_REFACTORINGS = 300
} Refactorings;

#endif
