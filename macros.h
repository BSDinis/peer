/*
 * useful macros (and small funcs)
 */
#pragma once


#include <stdlib.h>

void error_log(const char *file, int lineno);

#define LOG(...) \
  {\
    fprintf(stderr, "%s:%d: ", __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n"); \
    error_log(__FILE__, __LINE__);\
  }

#define LOG_KILL(...) \
  {\
    fprintf(stderr, "%s:%d: ", __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n"); \
    error_log(__FILE__, __LINE__);\
    exit(EXIT_FAILURE);\
  }

#define DEFAULT_BUF_SIZE (1<<10)
