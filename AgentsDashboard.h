#ifndef _AGENTS_DASHBOARD_H
#define _AGENTS_DASHBOARD_H

#include <stdint.h>

enum DashboardStatusColor {
    STATUS_HIVIZ_YELLOW = 0,
    STATUS_PURPLE,
    STATUS_RED,
    STATUS_BLUE
};

void initializeDashboard();
void setStatusCircleColor(uint8_t circle_index, DashboardStatusColor color);
void setStatusCircleAnimation(uint8_t circle_index, bool enable);
#define NSTATUS  4
#define AGENTS_NAME_MAX_LEN 8
struct Agent{
  bool working;
  char name[AGENTS_NAME_MAX_LEN+1];
  Agent();
};

void changeAgentStatus(int index, bool working, const char* newName);
bool updateOrPlaceAgentStatus(const char* name, bool working);
void setStatusCircleLabel(uint8_t circle_index, const char *text);



#endif //_AGENTS_DASHBOARD_H 
