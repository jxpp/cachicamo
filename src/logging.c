#include "logging.h"

enum logging_level logging_logLevel = WARNING;

void init_logging(void) {
}

void logging_log(enum logging_level log_level, const char* module, const char* str) {
  if (log_level < logging_logLevel) {
    return;
  }
  switch(log_level) {
    case DEBUG: fprintf(stdout, DEBUG_LOG_STYLE, module, str); break;
    case INFO: fprintf(stdout, INFO_LOG_STYLE, module, str); break;
    case WARNING: fprintf(stdout, WARNING_LOG_STYLE, module, str); break;
    case CRITICAL: fprintf(stdout, WARNING_LOG_STYLE, module, str); break;
  }
}
