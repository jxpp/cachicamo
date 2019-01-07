#ifndef CACHICAMO_LOGGING_H
#define CACHICAMO_LOGGING_H

#include <stdio.h>


enum logging_level {
  DEBUG,
  INFO,
  WARNING,
  CRITICAL
};

extern enum logging_level logging_logLevel;

static const char DEBUG_LOG_STYLE[] = "\033[34m[DEBUG][%s]: %s\033[0m\n";
static const char INFO_LOG_STYLE[] = "\033[36m[INFO][%s]: %s\033[0m\n";
static const char WARNING_LOG_STYLE[] = "\033[32m[WARNING][%s]: %s\033[0m\n";
static const char CRITICAL_LOG_STYLE[] = "\033[31m[CRITICAL][%s]: %s\033[0m\n";

void init_logging(void);
void logging_log(enum logging_level, const char*, const char*);


#endif
