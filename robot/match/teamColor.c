#include "teamColor.h"

char* getTeamColorAsString(enum TeamColor teamColor) {
  switch (teamColor) {
    case COLOR_ORANGE: return "SIDE ORANGE";
    case COLOR_GREEN: return "SIDE GREEN";
    default: return "SIDE ????";
  }
}