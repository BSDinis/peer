// implemtation

#include "macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <openssl/err.h>

void error_log(const char *file, int lineno, const char *fmt, ...)
{
  fprintf(stderr, "%s:%d: ", file, lineno);
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, fmt, ap);
  va_end(ap);
  fputc('\n', stderr);

  ERR_print_errors_fp(stderr);
}

