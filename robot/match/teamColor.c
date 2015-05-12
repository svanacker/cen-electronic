#include "teamColor.h"

char* getTeamColorAsString(enum TeamColor teamColor) {
  switch (teamColor) {
    case COLOR_YELLOW: return "SIDE YELLOW";
    case COLOR_GREEN: return "SIDE GREEN";
    default: return "SIDE ????";
  }
}