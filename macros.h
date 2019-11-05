/*
 * useful macros (and small funcs)
 */
#pragma once


#include <stdarg.h>
#include <stdlib.h>

void error_log(const char *file, int lineno, const char *fmt, ...);

#define LOG(...) error_log(__FILE__, __LINE__, __VA_ARGS__)

#define LOG_KILL(...) \
  {\
    error_log(__FILE__, __LINE__, __VA_ARGS__);\
    exit(EXIT_FAILURE);\
  }

#define DEFAULT_BUF_SIZE (1<<10)
