#ifndef CACHICAMO_LOGGING_H
#define CACHICAMO_LOGGING_H

#include <stdio.h>

enum LOGGING_LEVEL {DEBUG, INFO, WARNING, CRITICAL};

void init_logging(void);
void logging_log(enum LOGGING_LEVEL, const char*, const char*);

#endif
