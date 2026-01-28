/*
 * Logging functions used by Xwayback and wayback-session.
 *
 * SPDX-License-Identifier: MIT
 */

#include "wayback_log.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static enum wayback_log_level logging_max_verbosity = LOG_INFO;
static char *logging_context = "wayback";
static bool logging_use_color = true;

static const char *log_colors[] = {
	[LOG_ERROR] = "\x1b[1;31m",
	[LOG_WARN] = "\x1b[1;33m",
	[LOG_INFO] = "\x1b[1;37m",
	[LOG_DEBUG] = "\x1b[1;39m]",
};

static const char *log_prefix[] = {
	[LOG_ERROR] = "[ERROR]",
	[LOG_WARN] = "[WARN]",
	[LOG_INFO] = "[INFO]",
	[LOG_DEBUG] = "[DEBUG]",
};

static void default_log_func(enum wayback_log_level verbosity, const char *fmt, va_list args)
{
	if (verbosity > logging_max_verbosity)
		return;

	unsigned verbosity_lvl = (verbosity < LOG_LAST) ? verbosity : LOG_LAST - 1;

	if (logging_use_color)
		fprintf(stderr, "%s", log_colors[verbosity_lvl]);

	fprintf(stderr, "%s (%s): ", log_prefix[verbosity_lvl], logging_context);

	vfprintf(stderr, fmt, args);

	if (logging_use_color)
		fprintf(stderr, "\x1b[0m");

	fprintf(stderr, "\n");
}

static wayback_log_func_t logging_func = default_log_func;

void wayback_log_init(char *ctx,
                      enum wayback_log_level max_verbosity,
                      wayback_log_func_t log_function)
{
	if (ctx)
		logging_context = ctx;

	logging_max_verbosity = max_verbosity;

	if (log_function)
		logging_func = log_function;

	char *no_color = getenv("NO_COLOR");
	if ((no_color != NULL && no_color[0] != '\0') || !isatty(STDERR_FILENO))
		logging_use_color = false;
}

void wayback_log_verbosity(enum wayback_log_level max_verbosity)
{
	logging_max_verbosity = max_verbosity;
}

void wayback_vlog(enum wayback_log_level verbosity, const char *format, va_list args)
{
	logging_func(verbosity, format, args);
}

void wayback_log(enum wayback_log_level verbosity, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	logging_func(verbosity, format, args);
	va_end(args);
}
