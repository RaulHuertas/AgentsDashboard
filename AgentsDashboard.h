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

struct Agent{
  bool working;
  char name[9];
  Agent();
};

void changeAgentStatus(int index, bool working, const char* newName);
void setStatusCircleLabel(uint8_t circle_index, const char *text);



#endif //_AGENTS_DASHBOARD_H 
