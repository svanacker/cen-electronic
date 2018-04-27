#include "teamColor.h"

char* getTeamColorAsString(enum TeamColor teamColor) {
  switch (teamColor) {
    case TEAM_COLOR_ORANGE: return "SIDE ORANGE";
    case TEAM_COLOR_GREEN: return "SIDE GREEN";
    default: return "SIDE ????";
  }
}