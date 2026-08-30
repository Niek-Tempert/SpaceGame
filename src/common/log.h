#pragma once

#include <string.h>
#include <stdio.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define logError(str, ...) fprintf(stderr, "Error in %s at line %d: " str "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#define logWarning(str, ...) fprintf(stdout, "Warning in %s at line %d: " str "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#define logInfo(str, ...) fprintf(stdout, "Info in %s at line %d: " str "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
