#include <timers.h>

struct app_timer_ctxt {
	uint32_t in_use[APP_THREADS_MAX_TIMERS]; /**< Always the first 0 to N signal id in a thread */
};
struct app_timer_ctxt g_app_timer_ctxt[e_app_threads_max];

uint32_t timer_info[e_app_threads_max];

int app_get_timer_next_free_sig_id(uint32_t app_thread_id)
{
	struct app_timer_ctxt *timer_ctxt = &g_app_timer_ctxt[app_thread_id];

	for (uint32_t i = 0; i < APP_THREADS_MAX_TIMERS; ++i) {
		if (timer_ctxt->in_use[i] == 0) {
			timer_ctxt->in_use[i] = 1;
			return i;
		}
	}

	__ASSERT_NO_MSG(0); /* We should not run out of timers */

	return -1;
}

void app_timer_expiry_fn(struct k_timer *my_timer)
{
	/* This will be called in the system timer ISR. Just signal the BH using the kernel signal object */
	uint32_t *thread_id = k_timer_user_data_get(my_timer); 
	struct k_poll_signal *my_signal = &g_threads[*thread_id].signal_list[0];
	if (k_poll_signal_raise(my_signal, 0) != 0)
		printk("signal raise failed \n");
	g_threads[*thread_id].send_signals += 1;	
}

extern threads_ctxt_t g_threads[e_app_threads_max];

void app_timer_init(struct k_timer *my_timer, uint32_t app_thread_id, uint32_t timer_sig_id)
{
	/* Get the kernel signal object that we would want to use for this timer */
	k_timer_init(my_timer, app_timer_expiry_fn, NULL /* Stop function */);

	/* Stash the signal object in the timer user data and use it to call the corresponding BH */
	timer_info[app_thread_id] = app_thread_id;
	printk("Init timer in thread %d with %d\n", app_thread_id, timer_sig_id);
	k_timer_user_data_set(my_timer, &timer_info[app_thread_id]);
}

void setup_timer(struct k_timer *my_timer, uint32_t app_thread_id,
		 Eapp_sig_hdlr_status_t (*expiry_fn)(), void *args)
{
	int timer_sig_id = app_get_timer_next_free_sig_id((app_thread_id));

	app_timer_init(my_timer, app_thread_id, timer_sig_id);
	g_threads[app_thread_id].sig_hdlr[timer_sig_id].hdlr_fn = expiry_fn;
	g_threads[app_thread_id].sig_hdlr[timer_sig_id].arg = args;
}
