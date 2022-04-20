#pragma once

#include <stdarg.h>

int util_vsprintf(char *buf, const char *fmt, va_list args);
int util_sprintf(char *buf, const char *fmt, ...);