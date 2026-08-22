#include <lvgl.h>

#define USE_TFT_ESPI_LIBRARY
#include "lv_xiao_round_screen.h"
#include "AgentsDashboard.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200 );  //prepare for possible serial debug 
  Serial.println( "XIAO round screen - LVGL_Arduino" );

  lv_init();
  #if LVGL_VERSION_MAJOR == 9
  lv_tick_set_cb(millis);
  #endif
    
  lv_xiao_disp_init();
  lv_xiao_touch_init();
  initializeDashboard();
}

void loop() {
  // put your main code here, to run repeatedly:
  lv_timer_handler();  //let the GUI do its work 
  //delay( 5 );
}
