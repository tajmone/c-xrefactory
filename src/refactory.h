#ifndef REFACTORY_H
#define REFACTORY_H

#include "proto.h"

enum trivialPreChecks {
    TPC_NONE,                   /* Must be 0 because of initOpt in globals.h */
    TPC_MOVE_FIELD,
    TPC_RENAME_PACKAGE,
    TPC_RENAME_CLASS,
    TPC_MOVE_CLASS,
    TPC_MOVE_STATIC_FIELD,
    TPC_MOVE_STATIC_METHOD,
    TPC_TURN_DYN_METHOD_TO_STATIC,
    TPC_TURN_STATIC_METHOD_TO_DYN,
    TPC_PULL_UP_METHOD,
    TPC_PUSH_DOWN_METHOD,
    TPC_PUSH_DOWN_METHOD_POST_CHECK,
    TPC_PULL_UP_FIELD,
    TPC_PUSH_DOWN_FIELD,
    TPC_GET_LAST_IMPORT_LINE, // not really a check
};

extern void refactoryAskForReallyContinueConfirmation(void);
extern void refactoryDisplayResolutionDialog(char *message,int messageType, int continuation);
extern void editorApplyUndos(S_editorUndo *undos, S_editorUndo *until, S_editorUndo **undoundo, int gen);
extern void editorUndoUntil(S_editorUndo *until, S_editorUndo **undoUndo);
extern void mainRefactory(int argc, char **argv);
extern int tpCheckSourceIsNotInnerClass(void);
extern int tpCheckMoveClassAccessibilities(void);
extern int tpCheckSuperMethodReferencesForDynToSt(void);
extern int tpCheckOuterScopeUsagesForDynToSt(void);
extern int tpCheckMethodReferencesWithApplOnSuperClassForPullUp(void);
extern int tpCheckSuperMethodReferencesForPullUp(void);
extern int tpCheckSuperMethodReferencesAfterPushDown(void);
extern void tpCheckFillMoveClassData(S_tpCheckMoveClassData *dd, char *spack, char *tpack);
extern int tpCheckTargetToBeDirectSubOrSupClass(int flag, char *subOrSuper);
extern int tpPullUpFieldLastPreconditions(void);
extern int tpPushDownFieldLastPreconditions(void);

#endif
