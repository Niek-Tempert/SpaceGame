#include "strbuff.h"

static code sizeCheck(StrBuff* buff, size_t len) {
    if (len <= buff->cap) return CODE_OK;
    size_t newCap = nextPow2(len);
    char* restr = (char*)realloc(buff->str, newCap);
    if (!restr) return CODE_MEM_ERR;
    buff->str = restr;
    buff->cap = newCap;
    return CODE_OK;
}

code strBuffInit(StrBuff* buff, size_t cap) {
    cap = nextPow2(cap);
    char* str = malloc(cap);
    if (!str) return CODE_MEM_ERR;
    buff->str = str;
    buff->len = 0;
    buff->cap = cap;
    return CODE_OK;
}

code strBuffCat(StrBuff* buff, const char* str, size_t strLen) {
    code err = CODE_OK;
    size_t newLen = buff->len + strLen;
    if (err = sizeCheck(buff, newLen)) return err;
    memcpy(buff->str + buff->len, str, strLen);
    buff->len = newLen;
    return err;
}

code strBuffInsert(StrBuff* buff, const char* str, size_t strLen, size_t idx) {
    if (idx > buff->len) return CODE_OUTOFBOUNDS_ERR;
    code err = CODE_OK;
    size_t newLen = buff->len + strLen;
    if (err = sizeCheck(buff, newLen)) return err;
    memmove(buff->str + idx + strLen, buff->str + idx, buff->len - idx);
    memcpy(buff->str + idx, str, strLen);
    buff->len = newLen;
    return err;
}

code strBuffReplace(StrBuff* buff, const char* str, size_t strLen, size_t idxStart, size_t idxEnd) {
    if (idxStart > idxEnd) return CODE_RANGE_ERR; 
    if (idxEnd > buff->len) return CODE_OUTOFBOUNDS_ERR;
    code err = CODE_OK;
    size_t rangeSize = idxEnd - idxStart;
    size_t newLen = buff->len + strLen - rangeSize;
    if (err = sizeCheck(buff, newLen)) return err;
    memmove(buff->str + idxEnd + strLen - rangeSize, buff->str + idxEnd, buff->len - idxEnd);
    memcpy(buff->str + idxStart, str, strLen);
    buff->len = newLen;
    return err;
}

code strBuffCut(StrBuff* buff, size_t idxStart, size_t idxEnd) {
    if (idxStart > idxEnd) return CODE_RANGE_ERR; 
    if (idxEnd > buff->len) return CODE_OUTOFBOUNDS_ERR;
    code err = CODE_OK;
    size_t rangeSize = idxEnd - idxStart;
    size_t newLen = buff->len - rangeSize;
    memmove(buff->str + idxStart, buff->str + idxEnd, buff->len - idxEnd);
    buff->len = newLen;
    return err;
}

code strBuffShrink(StrBuff* buff) {
    char* str = (char*)realloc(buff->str, buff->len);
    if (!str) return CODE_MEM_ERR;
    buff->str = str;
    buff->cap = buff->len;
    return CODE_OK;
}
