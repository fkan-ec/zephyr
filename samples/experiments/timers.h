#ifndef __PLATFORM_TIMERS_H
#define __PLATFORM_TIMERS_H

#include <threads.h>

int app_get_timer_next_free_sig_id(uint32_t app_thread_id);
void app_timer_init(struct k_timer * my_timer, uint32_t app_thread_id, uint32_t timer_sig_id);
uint32_t app_get_current_time_32_us();
uint32_t app_get_current_time_32_ns();
uint64_t app_get_current_time_64_us();

#define APP_TIMER_DEFINE(my_timer) struct k_timer my_timer
/* We can also implicitly derive the thread_id but that would restrict all timers to be initialized
 * and started from the destination thread.
 */
/* May be make all of these as functions */
#define APP_TIMER_INIT(my_timer, app_thread_id, expiry_fn, args) \
    do { \
        int timer_sig_id = app_get_timer_next_free_sig_id((app_thread_id)); \
        app_timer_init((my_timer), (app_thread_id), (timer_sig_id)); \
        APP_REGISTER_SIG_HDLR(&g_threads[(app_thread_id)], (timer_sig_id), (expiry_fn), (args)); \
       } \
    while (0)

#define APP_TIMER_PERIODIC_START_US(my_timer, period_in_us) \
            k_timer_start(my_timer, K_USEC(period_in_us), K_USEC(period_in_us))

#define APP_TIMER_ONE_SHOT_START_US(my_timer, period_in_us) \
            k_timer_start(my_timer, K_USEC(period_in_us), K_NO_WAIT)

#define APP_TIMER_STOP(my_timer) k_timer_stop(my_timer)

#endif
