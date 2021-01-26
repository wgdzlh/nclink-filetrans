#ifndef __MM_H__
#define __MM_H__

#define nclink_malloc  NCLinkMMMalloc
#define nclink_calloc  NCLinkMMCalloc
#define nclink_realloc NCLinkMMRealloc
#define nclink_free    NCLinkMMFree
#define nclink_strdup  NCLinkMMStrdup


#ifdef __cpluscplus
extern "C"{
#endif

#include <stddef.h>
int NCLinkMMInit(void);

void NCLinkMMDeinit(void);

void *NCLinkMMMalloc(size_t size);

void *NCLinkMMCalloc(size_t nmemb, size_t size);

void *NCLinkMMRealloc(void *ptr, size_t size);

void NCLinkMMFree(void *mem);

char *NCLinkMMStrdup(const char *s);

#ifdef __cpluscplus
}
#endif
#endif
