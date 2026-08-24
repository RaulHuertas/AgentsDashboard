#include <lvgl.h>

#define USE_TFT_ESPI_LIBRARY
#include "lv_xiao_round_screen.h"
#include "AgentsDashboard.h"
#include "ATCommandScanner.h"

static bool initialStatusesApplied = false;
static unsigned long startupMs = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200 );  //prepare for possible serial debug 
  //Serial.println( "XIAO round screen - LVGL_Arduino" );

  lv_init();
  lv_xiao_disp_init();
  lv_xiao_touch_init();
  initializeDashboard();
  initATCommandScanner(Serial);
  startupMs = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  pollATCommandScanner();
  lv_timer_handler();  //let the GUI do its work 
  unsigned long now = millis();
  if (!initialStatusesApplied && (now - startupMs >= 2000)) {
    
    initialStatusesApplied = true;
    //Serial.println("Status update");
  }

  delay( 5 );

}
