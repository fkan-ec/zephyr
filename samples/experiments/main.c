#include <shell/shell.h>
#include <debug/thread_analyzer.h>
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
    uint32_t start, end; 
    
    //start = app_get_current_time_32_ns();
    g_count++;
    static uint64_t load = 0;
    for(uint32_t i = 0; i < 100000; ++i)
    {
        load *= 0.7678;
    }
    //end = app_get_current_time_32_ns();
    //printf("it takes this long %d\n", end-start);
    return e_sig_hdlr_complete;
}

Eapp_sig_hdlr_status_t thread_timeout_handler_a(void * arg)
{
    static uint64_t load = 0;
    for(uint32_t i = 0; i < 100000; ++i)
    {
        load *= 0.7678;
    }
    return e_sig_hdlr_complete;
}

Eapp_sig_hdlr_status_t thread_timeout_handler_b(void * arg)
{
    static uint64_t load = 0;
    for(uint32_t i = 0; i < 100000; ++i)
    {
        load *= 0.7678;
    }
    return e_sig_hdlr_complete;
}

Eapp_sig_hdlr_status_t thread_timeout_handler_c(void * arg)
{
    static uint64_t load = 0;
    for(uint32_t i = 0; i < 100000; ++i)
    {
        load *= 0.7678;
    }
    return e_sig_hdlr_complete;
}

Eapp_sig_hdlr_status_t thread_timeout_handler_d(void * arg)
{
    static uint64_t load = 0;
    for(uint32_t i = 0; i < 100000; ++i)
    {
        load *= 0.7678;
    }
    return e_sig_hdlr_complete;
}

Eapp_sig_hdlr_status_t thread_timeout_handler_e(void * arg)
{
    g_count++;
    static uint64_t load = 0;
    for(uint32_t i = 0; i < 100000; ++i)
    {
        load *= 0.7678;
    }
    return e_sig_hdlr_complete;
}

#define FKAN_THREADS 1
int main()
{
    printf("Entered Main \n");
    printf("Initializing threads\n");
    threads_init();

    /* Launch timers for each of the thread */
    APP_TIMER_INIT(&g_thread_a_timer, e_app_threads_a, thread_timeout_handler_a, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_a_timer, 2000 /* 2 millisecond */);

#ifdef FKAN_THREADS
    APP_TIMER_INIT(&g_thread_a_timer2, e_app_threads_a, thread_timeout_handler, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_a_timer2, 2000 /* 2 millisecond */);
#endif

    APP_TIMER_INIT(&g_thread_b_timer, e_app_threads_b, thread_timeout_handler_b, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_b_timer, 2000 /* 2 millisecond */);

#ifdef FKAN_THREADS
    APP_TIMER_INIT(&g_thread_b_timer2, e_app_threads_b, thread_timeout_handler, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_b_timer2, 2000 /* 2 millisecond */);
#endif

    APP_TIMER_INIT(&g_thread_c_timer, e_app_threads_c, thread_timeout_handler_c, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_c_timer, 2000 /* 2 millisecond */);

#ifdef FKAN_THREADS
    APP_TIMER_INIT(&g_thread_c_timer2, e_app_threads_c, thread_timeout_handler, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_c_timer2, 2000 /* 2 millisecond */);
#endif

    APP_TIMER_INIT(&g_thread_d_timer, e_app_threads_d, thread_timeout_handler_d, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_d_timer, 2000 /* 2 millisecond */);

#ifdef FKAN_THREADS
    APP_TIMER_INIT(&g_thread_d_timer2, e_app_threads_d, thread_timeout_handler, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_d_timer2, 2000 /* 2 millisecond */);
#endif

    APP_TIMER_INIT(&g_thread_e_timer, e_app_threads_e, thread_timeout_handler_e, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_e_timer, 2000 /* 2 millisecond */);

#ifdef FKAN_THREADS
    APP_TIMER_INIT(&g_thread_e_timer2, e_app_threads_e, thread_timeout_handler, NULL);
    APP_TIMER_PERIODIC_START_US(&g_thread_e_timer2, 2000 /* 2 millisecond */);
#endif

    return 0;
}

#ifdef CONFIG_THREAD_ANALYZER
static int cmd_thread_info(const struct shell *shell, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	thread_analyzer_print();

	return 0;
}

#define THREAD_INFO_CMD "Thread Info"

SHELL_STATIC_SUBCMD_SET_CREATE(sub_thread,
	SHELL_CMD_ARG(info, NULL, THREAD_INFO_CMD, cmd_thread_info, 1, 0),
	SHELL_SUBCMD_SET_END /* Array terminated. */
);

SHELL_CMD_REGISTER(thread, &sub_thread, "Thread related commands.", NULL);
#endif
