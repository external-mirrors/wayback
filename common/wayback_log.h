/*
 * Logging functions used by all wayback executables.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef WAYBACK_LOG_IMPORTED
#define WAYBACK_LOG_IMPORTED

#include <stdarg.h>

enum wayback_log_level
{
	LOG_ERROR,
	LOG_WARN,
	LOG_INFO,
	LOG_DEBUG,
	LOG_LAST,
};

typedef void (*wayback_log_func_t)(enum wayback_log_level verbosity, const char *fmt, va_list args);

void wayback_log_init(char *ctx,
                      enum wayback_log_level max_verbosity,
                      wayback_log_func_t log_function);

void wayback_log_verbosity(enum wayback_log_level max_verbosity);
void wayback_vlog(enum wayback_log_level verbosity, const char *format, va_list args);
void wayback_log(enum wayback_log_level verbosity, const char *format, ...);

#endif
