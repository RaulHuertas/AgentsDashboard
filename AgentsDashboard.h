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

#endif //_AGENTS_DASHBOARD_H 
