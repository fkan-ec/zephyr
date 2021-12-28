#ifndef __PLATFORM_TIMERS_H
#define __PLATFORM_TIMERS_H

#include <threads.h>

int app_get_timer_next_free_sig_id(uint32_t app_thread_id);
void app_timer_init(struct k_timer * my_timer, uint32_t app_thread_id, uint32_t timer_sig_id);

#define APP_TIMER_DEFINE(my_timer) struct k_timer my_timer
/* We can also implicitly derive the thread_id but that would restrict all timers to be initialized
 * and started from the destination thread.
 */
void setup_timer(struct k_timer *my_timer, uint32_t app_thread_id, Eapp_sig_hdlr_status_t (*expiry_fn)(), void *args);
#endif
