#include <pebble.h>

static Window *s_window;
static TextLayer *s_text_layer;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // A single click has just occured
    Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
	
  	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Select clicked!");
  
  // Create a text layer and set the text
	s_text_layer = text_layer_create(bounds);
	text_layer_set_text(s_text_layer, "Single click!");
  
        // Set the font and text alignment
	text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  
  	// Add the text layer to the window
	layer_add_child(window_get_root_layer(s_window), text_layer_get_layer(s_text_layer));

}

static void down_repeating_click_handler(ClickRecognizerRef recognizer, void *context) {
  // A single click has just occured
    Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
	
  	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Select repeatedly clicked!");
  
  // Create a text layer and set the text
	s_text_layer = text_layer_create(bounds);
	text_layer_set_text(s_text_layer, "Repeating click!");
  
    // Set the font and text alignment
	text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  
  	// Add the text layer to the window
	layer_add_child(window_get_root_layer(s_window), text_layer_get_layer(s_text_layer));

}

static void long_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  // A single click has just occured
    Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
	
  	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Select long clicked!");
  
  // Create a text layer and set the text
	s_text_layer = text_layer_create(bounds);
	text_layer_set_text(s_text_layer, "long click!");
  
    // Set the font and text alignment
	text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  
  	// Add the text layer to the window
	layer_add_child(window_get_root_layer(s_window), text_layer_get_layer(s_text_layer));

}

static void back_click_handler(ClickRecognizerRef recognizer, void *context) {
  // A single click has just occured
   // Layer *window_layer = window_get_root_layer(s_window);
  //GRect bounds = layer_get_bounds(window_layer);
  //s_text_layer = text_layer_create(bounds);
  //child = text_layer_get_layer(window_layer);
  //layer_remove_from_parent(s_text_layer);
  text_layer_destroy(s_text_layer);

}

static void click_config_provider(void *context) {
  // Subcribe to button click events here
    ButtonId id = BUTTON_ID_SELECT;  // The Select button

  window_single_click_subscribe(id, select_click_handler);
   window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
  
    uint16_t repeat_interval_ms = 200;  // Fire every 200 ms while held down

    window_long_click_subscribe(id, repeat_interval_ms, long_down_click_handler, 0);
  
  //window_single_repeating_click_subscribe(id, repeat_interval_ms,
  //                                              down_repeating_click_handler);

}

static void prv_on_health_data(HealthEventType type, void *context) {
  // If the update was from the Heart Rate Monitor, query it
  if (type == HealthEventHeartRateUpdate) {
    HealthValue value = health_service_peek_current_value(HealthMetricHeartRateBPM);
    // Display the heart rate
    Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
	static char str[100];
    snprintf(str, sizeof(str), "Heart rate is now %lu", (uint32_t)value);
  	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Heart rate update");
    APP_LOG(APP_LOG_LEVEL_DEBUG, str);
  
  // Create a text layer and set the text
	s_text_layer = text_layer_create(bounds);
	text_layer_set_text(s_text_layer, str);
  
          // Set the font and text alignment
	text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
    
  	// Add the text layer to the window
	layer_add_child(window_get_root_layer(s_window), text_layer_get_layer(s_text_layer));
    
  }
}

static void init(void) {
	// Create a window and get information about the window
	s_window = window_create();
  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);
	
    // Create a text layer and set the text
	s_text_layer = text_layer_create(bounds);
	//text_layer_set_text(s_text_layer, "Hi, I'm a Pebble!");
      static char s_hrm_buffer[100];
  //Get current HR value
  HealthServiceAccessibilityMask hr = health_service_metric_accessible(HealthMetricHeartRateBPM, time(NULL), time(NULL));
if (hr & HealthServiceAccessibilityMaskAvailable) {
  HealthValue val = health_service_peek_current_value(HealthMetricHeartRateBPM);
  //if(val > 0) {
    // Display HRM value

    snprintf(s_hrm_buffer, sizeof(s_hrm_buffer), "Hey there, your current HR is %lu BPM", (uint32_t)val);
    text_layer_set_text(s_text_layer, s_hrm_buffer);
 // }
}
  
  // Set the font and text alignment
	text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);

	// Add the text layer to the window
	layer_add_child(window_get_root_layer(s_window), text_layer_get_layer(s_text_layer));
  
  // Enable text flow and paging on the text layer, with a slight inset of 10, for round screens
  text_layer_enable_screen_text_flow_and_paging(s_text_layer, 10);

	// Push the window, setting the window animation to 'true'
	window_stack_push(s_window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
  
  // Use this provider to add button click subscriptions
window_set_click_config_provider(s_window, click_config_provider);
    // Subscribe to health event handler
  health_service_events_subscribe(prv_on_health_data, NULL);
}

static void deinit(void) {
	// Destroy the text layer
	text_layer_destroy(s_text_layer);
	
	// Destroy the window
	window_destroy(s_window);
}


int main(void) {
	init();
	app_event_loop();
	deinit();
}
