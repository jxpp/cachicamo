#include "logging.h"

void init_logging(void) {

}

void logging_log(enum LOGGING_LEVEL log_level, const char* module, const char* str) {
  static const char DEBUG_LOG_STYLE[] = "\033[34m[DEBUG][%s]: %s\033[0m\n";
  static const char WARNING_LOG_STYLE[] = "\033[32m[WARNING][%s]: %s\033[0m\n";

  switch(log_level) {
    case DEBUG: printf(DEBUG_LOG_STYLE, module, str); break;
    case WARNING: printf(WARNING_LOG_STYLE, module, str); break;
    default: break;
  }
}
