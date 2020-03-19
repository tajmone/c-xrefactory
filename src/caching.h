#ifndef _CACHING_H_
#define _CACHING_H_

extern int checkFileModifiedTime(int ii);
extern void initCaching(void);
extern void recoverCachePoint(int i, char *readedUntil, int activeCaching);
extern void recoverFromCache(void);
extern void cacheInput(void);
extern void cacheInclude(int fileNum);
extern void placeCachePoint(int inputCacheFlag);
extern void recoverCachePointZero(void);
extern void recoverMemoriesAfterOverflow(char *cxMemFreeBase);

#endif
