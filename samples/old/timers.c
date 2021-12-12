#include <timers.h>

//#define TIMER_PROFILE

#ifdef TIMER_PROFILE
#include <stdio.h>
#include <timing/timing.h>
#endif

struct app_timer_ctxt
{
    uint32_t in_use[APP_THREADS_MAX_TIMERS]; /**< Always the first 0 to N signal id in a thread */
};
struct app_timer_ctxt g_app_timer_ctxt[e_app_threads_max];

int app_get_timer_next_free_sig_id(uint32_t app_thread_id)
{

    struct app_timer_ctxt * timer_ctxt = &g_app_timer_ctxt[app_thread_id];

    for(uint32_t i = 0; i < APP_THREADS_MAX_TIMERS; ++i)
    {
        if(timer_ctxt->in_use[i] == 0)
        {
            timer_ctxt->in_use[i] = 1;
            return i;
        }
    }

    __ASSERT_NO_MSG(0); /* We should not run out of timers */

    return -1;
}

void app_timer_expiry_fn(struct k_timer * my_timer)
{
#ifdef TIMER_PROFILE
    static timing_t prev_time = 0;
    uint64_t cycles = 0;
    uint64_t time_diff_ns = 0;
    timing_t curr_time = timing_counter_get();
    cycles = timing_cycles_get(&prev_time, &curr_time);
    time_diff_ns = timing_cycles_to_ns(cycles);
    printf("Called with time difference %ld ns\n", time_diff_ns);
#endif
    /* This will be called in the system timer ISR. Just signal the BH using the kernel signal object */
    struct k_poll_signal* my_signal = k_timer_user_data_get(my_timer);
    k_poll_signal_raise(my_signal, 0);
#ifdef TIMER_PROFILE
    prev_time = timing_counter_get();
#endif
}

extern threads_ctxt_t g_threads[e_app_threads_max];

void app_timer_init(struct k_timer * my_timer, uint32_t app_thread_id, uint32_t timer_sig_id)
{
    /* Get the kernel signal object that we would want to use for this timer */
    struct k_poll_signal* my_signal = &g_threads[app_thread_id].signal_list[timer_sig_id];
    k_timer_init(my_timer, app_timer_expiry_fn, NULL /* Stop function */);
    /* Stash the signal object in the timer user data and use it to call the corresponding BH */
    k_timer_user_data_set(my_timer, my_signal);
}



