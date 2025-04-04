#include "common/rc.h"

const char *strrc(RC rc)
{
#define DEFINE_RC(name) \
  case RC::name: {      \
    return #name;       \
  } break;

  switch (rc) {
    DEFINE_RCS;
    default: {
      return "unknown";
    }
  }
#undef DEFINE_RC
}

bool RM_SUCC(RC rc) { return rc == RC::SUCCESS; }

bool RM_FAIL(RC rc) { return rc != RC::SUCCESS; }