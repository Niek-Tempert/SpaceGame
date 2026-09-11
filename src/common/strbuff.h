#ifndef COMMON_STRBUFF_H
#define COMMON_STRBUFF_H

#include "math.h"
#include "error.h"
#include <stdlib.h>

typedef struct {
    char* str;
    size_t len;
    size_t cap;
} StrBuff;

NODISCARD code strBuffInit(StrBuff* buff, size_t size);
NODISCARD code strBuffCat(StrBuff* buff, const char* str, size_t strSize);
NODISCARD code strBuffInsert(StrBuff* buff, const char* str, size_t strSize, size_t idx);
NODISCARD code strBuffReplace(StrBuff* buff, const char* str, size_t strSize, size_t idxStart, size_t idxEnd);
NODISCARD code strBuffCut(StrBuff* buff, size_t idxStart, size_t idxEnd);
NODISCARD code strBuffShrink(StrBuff* buff);

#endif
