#include <lvgl.h>

#define USE_TFT_ESPI_LIBRARY
#include "lv_xiao_round_screen.h"
#include "AgentsDashboard.h"

static bool initialStatusesApplied = false;
static unsigned long startupMs = 0;

static void applyInitialAgentStatuses() {
  setStatusCircleAnimation(2, true);
  setStatusCircleLabel(0, "IntelliJ");
  setStatusCircleLabel(1, "Nvim");
  setStatusCircleLabel(2, "OpenCode");
  setStatusCircleLabel(3, "VSCode");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200 );  //prepare for possible serial debug 
  Serial.println( "XIAO round screen - LVGL_Arduino" );

  lv_init();
  lv_xiao_disp_init();
  lv_xiao_touch_init();
  initializeDashboard();
  startupMs = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  lv_timer_handler();  //let the GUI do its work 
  unsigned long now = millis();
  if (!initialStatusesApplied && ( - startupMs >= 2000)) {
    applyInitialAgentStatuses();
    initialStatusesApplied = true;
    Serial.println("Status update");
  }

  delay( 5 );

}
