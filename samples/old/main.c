#include <stdio.h>
#include <stdlib.h>
#include <zephyr.h>
#include <threads.h>
#include <timers.h>

extern void threads_init(void);

APP_TIMER_DEFINE(g_thread_a_timer);
APP_TIMER_DEFINE(g_thread_a_timer2);
APP_TIMER_DEFINE(g_thread_b_timer);
APP_TIMER_DEFINE(g_thread_b_timer2);
APP_TIMER_DEFINE(g_thread_c_timer);
APP_TIMER_DEFINE(g_thread_c_timer2);
APP_TIMER_DEFINE(g_thread_d_timer);
APP_TIMER_DEFINE(g_thread_d_timer2);
APP_TIMER_DEFINE(g_thread_e_timer);
APP_TIMER_DEFINE(g_thread_e_timer2);

/** @brief  Zephyr main thread.
 *
 *  @details
 * This thread performs kernel initialization, then calls the application’s main() function.
 *
 * By default, the main thread uses the highest configured preemptible thread priority (i.e. 0). 
 * If the kernel is not configured to support preemptible threads, the main thread uses the lowest 
 * configured cooperative thread priority (i.e. -1).
 *
 * The main thread is an essential thread while it is performing kernel initialization or executing the 
 * application’s main() function; this means a fatal system error is raised if the thread aborts. If main() 
 * is not defined, or if it executes and then does a normal return, the main thread terminates normally 
 * and no error is raised.
 */
_Atomic uint32_t g_count;
Eapp_sig_hdlr_status_t thread_timeout_handler(void * arg)
{
    return e_sig_hdlr_complete;
}

int main()
{
    printf("Entered Main \n");
	printf("Initializing threads\n");
	threads_init();

    /* Launch timers for each of the thread */
    APP_TIMER_INIT(&g_thread_a_timer, e_app_threads_a, thread_timeout_handler, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_a_timer, 2000 /* 2 millisecond */);


    APP_TIMER_INIT(&g_thread_b_timer, e_app_threads_b, thread_timeout_handler, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_b_timer, 2000 /* 2 millisecond */);


    APP_TIMER_INIT(&g_thread_c_timer, e_app_threads_c, thread_timeout_handler, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_c_timer, 2000 /* 2 millisecond */);


    APP_TIMER_INIT(&g_thread_d_timer, e_app_threads_d, thread_timeout_handler, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_d_timer, 2000 /* 2 millisecond */);


    APP_TIMER_INIT(&g_thread_e_timer, e_app_threads_e, thread_timeout_handler, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_e_timer, 2000 /* 2 millisecond */);

    return 0;
}
