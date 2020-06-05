#ifndef _FILEITEM_H
#define _FILEITEM_H

#include <time.h>
#include <stdbool.h>


typedef struct fileItem {	/* to be renamed to constant pool item */
    char *name;
    time_t lastModified;
    time_t lastInspected;
    time_t lastUpdateMtime;
    time_t lastFullUpdateMtime;
    struct fileItemBits {
        bool cxLoading : 1;
        bool cxLoaded : 1;
        bool cxSaved : 1;
        bool commandLineEntered : 1;
        bool scheduledToProcess : 1;
        bool scheduledToUpdate : 1;
        bool fullUpdateIncludesProcessed : 1;
        bool isInterface : 1;        // class/interface for .class
        bool isFromCxfile : 1;       // is this file indexed in XFiles
        unsigned sourceFileNumber : 20;    // file number containing the class definition
    } b;
    struct classHierarchyReference	*superClasses; /* super-classes references */
    struct classHierarchyReference	*inferiorClasses; /* sub-classes references   */
    int directEnclosingInstance;  /* for Java Only  */
    struct fileItem *next;
} FileItem;


extern void fillFileItem(FileItem *item, char *name, bool fromCommandLine);

#endif
