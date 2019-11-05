// implemtation

#include "macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <openssl/err.h>

void error_log(const char *file, int lineno)
{
  ERR_print_errors_fp(stderr);
}

