#include <threads.h>
#include <stdio.h>

threads_ctxt_t g_threads[e_app_threads_max];

app_sig_hdlr_ctxt_t g_thread_a_sig_hdlr[e_thread_a_sig_id_max] = { 0 };
struct k_poll_signal g_thread_a_signals[e_thread_a_sig_id_max] = { 0 };
struct k_poll_event g_thread_a_events[e_thread_a_sig_id_max] = { 0 };
uint32_t app_max_thread_a_events = e_thread_a_sig_id_max;
K_KERNEL_STACK_DEFINE(g_thread_a_stack, APP_THREADS_STACK_SIZE);

void setup_thread_a()
{
    threads_ctxt_t *plat_ctxt = &g_threads[e_app_threads_a];
    plat_ctxt->app_thread_id = e_app_threads_a;
    strncpy(plat_ctxt->thread_name, "THREAD_A", MAX_APP_THREAD_NAME);
    plat_ctxt->prio         = -2;
    plat_ctxt->event_list   = g_thread_a_events;
    plat_ctxt->signal_list  = g_thread_a_signals;
    plat_ctxt->num_events   = &app_max_thread_a_events;
    plat_ctxt->sig_hdlr     = g_thread_a_sig_hdlr;
    plat_ctxt->options      = K_ESSENTIAL;
    plat_ctxt->cpu_mask     = APP_THREAD_ALL_CPU;
    plat_ctxt->entry_func   = thread_event_loop;
    plat_ctxt->tid_stack    = g_thread_a_stack;
    plat_ctxt->stack_size   = K_KERNEL_STACK_SIZEOF(g_thread_a_stack);
}

app_sig_hdlr_ctxt_t g_thread_b_sig_hdlr[e_thread_b_sig_id_max] = { 0 };
struct k_poll_signal g_thread_b_signals[e_thread_b_sig_id_max] = { 0 };
struct k_poll_event g_thread_b_events[e_thread_b_sig_id_max] = { 0 };
uint32_t app_max_thread_b_events = e_thread_b_sig_id_max;
K_KERNEL_STACK_DEFINE(g_thread_b_stack, APP_THREADS_STACK_SIZE);

void setup_thread_b()
{
    threads_ctxt_t *plat_ctxt = &g_threads[e_app_threads_b];
    plat_ctxt->app_thread_id = e_app_threads_b;
    strncpy(plat_ctxt->thread_name, "THREAD_B", MAX_APP_THREAD_NAME);
    plat_ctxt->prio         = 0;
    plat_ctxt->event_list   = g_thread_b_events;
    plat_ctxt->signal_list  = g_thread_b_signals;
    plat_ctxt->num_events   = &app_max_thread_b_events;
    plat_ctxt->sig_hdlr     = g_thread_b_sig_hdlr;
    plat_ctxt->options      = K_ESSENTIAL;
    plat_ctxt->cpu_mask     = APP_THREAD_ALL_CPU;
    plat_ctxt->entry_func   = thread_event_loop;
    plat_ctxt->tid_stack    = g_thread_b_stack;
    plat_ctxt->stack_size   = K_KERNEL_STACK_SIZEOF(g_thread_b_stack);
}

app_sig_hdlr_ctxt_t g_thread_c_sig_hdlr[e_thread_c_sig_id_max] = { 0 };
struct k_poll_signal g_thread_c_signals[e_thread_c_sig_id_max] = { 0 };
struct k_poll_event g_thread_c_events[e_thread_c_sig_id_max] = { 0 };
uint32_t app_max_thread_c_events = e_thread_c_sig_id_max;
K_KERNEL_STACK_DEFINE(g_thread_c_stack, APP_THREADS_STACK_SIZE);

void setup_thread_c()
{
    threads_ctxt_t *plat_ctxt = &g_threads[e_app_threads_c];
    plat_ctxt->app_thread_id = e_app_threads_c;
    strncpy(plat_ctxt->thread_name, "THREAD_C", MAX_APP_THREAD_NAME);
    plat_ctxt->prio         = 1;
    plat_ctxt->event_list   = g_thread_c_events;
    plat_ctxt->signal_list  = g_thread_c_signals;
    plat_ctxt->num_events   = &app_max_thread_c_events;
    plat_ctxt->sig_hdlr     = g_thread_c_sig_hdlr;
    plat_ctxt->options      = K_ESSENTIAL;
    plat_ctxt->cpu_mask     = APP_THREAD_ALL_CPU;
    plat_ctxt->entry_func   = thread_event_loop;
    plat_ctxt->tid_stack    = g_thread_c_stack;
    plat_ctxt->stack_size   = K_KERNEL_STACK_SIZEOF(g_thread_c_stack);
}

app_sig_hdlr_ctxt_t g_thread_d_sig_hdlr[e_thread_d_sig_id_max] = { 0 };
struct k_poll_signal g_thread_d_signals[e_thread_d_sig_id_max] = { 0 };
struct k_poll_event g_thread_d_events[e_thread_d_sig_id_max] = { 0 };
uint32_t app_max_thread_d_events = e_thread_d_sig_id_max;
K_KERNEL_STACK_DEFINE(g_thread_d_stack, APP_THREADS_STACK_SIZE);

void setup_thread_d()
{
    threads_ctxt_t *plat_ctxt = &g_threads[e_app_threads_d];
    plat_ctxt->app_thread_id = e_app_threads_d;
    strncpy(plat_ctxt->thread_name, "THREAD_D", MAX_APP_THREAD_NAME);
    plat_ctxt->prio         = 1;
    plat_ctxt->event_list   = g_thread_d_events;
    plat_ctxt->signal_list  = g_thread_d_signals;
    plat_ctxt->num_events   = &app_max_thread_d_events;
    plat_ctxt->sig_hdlr     = g_thread_d_sig_hdlr;
    plat_ctxt->options      = K_ESSENTIAL;
    plat_ctxt->cpu_mask     = APP_THREAD_ALL_CPU;
    plat_ctxt->entry_func   = thread_event_loop;
    plat_ctxt->tid_stack    = g_thread_d_stack;
    plat_ctxt->stack_size   = K_KERNEL_STACK_SIZEOF(g_thread_d_stack);
}

app_sig_hdlr_ctxt_t g_thread_e_sig_hdlr[e_thread_e_sig_id_max] = { 0 };
struct k_poll_signal g_thread_e_signals[e_thread_e_sig_id_max] = { 0 };
struct k_poll_event g_thread_e_events[e_thread_e_sig_id_max] = { 0 };
uint32_t app_max_thread_e_events = e_thread_e_sig_id_max;
K_KERNEL_STACK_DEFINE(g_thread_e_stack, APP_THREADS_STACK_SIZE);

void setup_thread_e()
{
    threads_ctxt_t *plat_ctxt = &g_threads[e_app_threads_e];
    plat_ctxt->app_thread_id = e_app_threads_e;
    strncpy(plat_ctxt->thread_name, "THREAD_E", MAX_APP_THREAD_NAME);
    plat_ctxt->prio         = 2;
    plat_ctxt->event_list   = g_thread_e_events;
    plat_ctxt->signal_list  = g_thread_e_signals;
    plat_ctxt->num_events   = &app_max_thread_e_events;
    plat_ctxt->sig_hdlr     = g_thread_e_sig_hdlr;
    plat_ctxt->options      = K_ESSENTIAL;
    plat_ctxt->cpu_mask     = APP_THREAD_ALL_CPU;
    plat_ctxt->entry_func   = thread_event_loop;
    plat_ctxt->tid_stack    = g_thread_e_stack;
    plat_ctxt->stack_size   = K_KERNEL_STACK_SIZEOF(g_thread_e_stack);
}

void threads_init(void)
{
	setup_thread_a();
	setup_thread_b();
	setup_thread_c();
	setup_thread_d();
	setup_thread_e();

	/* Create all threads registered with platform */
	for(uint32_t i = 0; i <  sizeof(g_threads)/sizeof(threads_ctxt_t); ++i)
	{
		for(uint32_t j = 0; j < *(g_threads[i].num_events); ++j)
		{
			k_poll_signal_init(&g_threads[i].signal_list[j]);	
			k_poll_event_init(&g_threads[i].event_list[j],
                                K_POLL_TYPE_SIGNAL,
                                K_POLL_MODE_NOTIFY_ONLY,
                              &g_threads[i].signal_list[j]);

			/* Store the signal id in the event to use it for handler lookup */
			g_threads[i].event_list[j].tag = j;
		}

		k_tid_t tid = k_thread_create(&g_threads[i].thread, 
				g_threads[i].tid_stack,
				g_threads[i].stack_size,
				g_threads[i].entry_func,
				g_threads[i].event_list,
				g_threads[i].num_events, 
				&g_threads[i].app_thread_id,
				g_threads[i].prio, 
				g_threads[i].options, 
				K_FOREVER);

		k_thread_name_set(tid, g_threads[i].thread_name);

		k_thread_start(tid);
	}
}


static void process_events(struct k_poll_event *ev, int count, uint32_t app_thread_id)
{
    app_sig_hdlr_ctxt_t * sig_hdlr = g_threads[app_thread_id].sig_hdlr;
    Eapp_sig_hdlr_status_t status = 0;
    count = 2;

	/* We can get fancy here to decide which events to prioritize. For now RR scheduling */
    for (; count; ev++, count--) {
        switch (ev->state) {
		case K_POLL_STATE_SIGNALED:
			/* Handle Signal */
			if(sig_hdlr[ev->tag].hdlr_fn)
			{
				/* TODO: add profiler for signal handlers */
				/* Reset signal first - this may race with producers trying to set it.
				 * This should be okay, as we call the handler after signalled is cleared.
				 * All handlers should run to completion else return e_plat_sig_hdlr_continue.
				 */
				status = sig_hdlr[ev->tag].hdlr_fn(sig_hdlr[ev->tag].arg);
				ev->signal->signaled = 0;  
				ev->state = K_POLL_STATE_NOT_READY;
			} else {
				printk("no thread handler found\n");
			}
			break;
		case K_POLL_STATE_NOT_READY:
			/* TODO */
			break;
		default:
			printk("Unexpected k_poll event state %u", ev->state);
			break;
	}
    }
}

void thread_event_loop(void *event_list, void *n_events, void *thread_id)
{
	k_tid_t tid = k_current_get();	
	struct k_poll_event *events = event_list;
	uint32_t num_events = *(uint32_t*)n_events;
	uint32_t app_thread_id = *(uint32_t*)thread_id;
	int rc;

	printk("Thread %s launched with %d events and app_thread_id %d\n",
			k_thread_name_get(tid), num_events, app_thread_id);

	while (1)
	{

		/* The k_poll() function returns as soon as one of the conditions it is waiting for is fulfilled. 
		 * It is possible for more than one to be fulfilled when k_poll() returns, if they were fulfilled before 
		 * k_poll() was called, or due to the preemptive multi-threading nature of the kernel. 
		 * The caller must look at the state of all the poll events in the array to figured out which ones were fulfilled and what actions to take.
		 */
		rc = k_poll(events, num_events, K_FOREVER);

		if(rc == 0) {
			process_events(events, num_events, app_thread_id);
		} else {
			/* TODO: Dont know how to handle this */
			printk("Thread timedout %d\n", rc);
		} 
	}
}
