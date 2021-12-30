#ifndef __THREADS
#define __THREADS

#include <zephyr.h>
#include <string.h>

/* Stack Size */
#define APP_THREADS_STACK_SIZE 4096

/* MAX timers per thread */
#define APP_THREADS_MAX_TIMERS 1

#define APP_THREAD_ALL_CPU ~0

#define MAX_APP_THREAD_NAME 35 /**< This goes as a prj config into the Zephyr build as well */

typedef enum app_threads {
	e_app_threads_a,
	e_app_threads_b,
	e_app_threads_c,
	e_app_threads_max

} Eapp_threads_t;

typedef enum app_sig_hdlr_status {
	e_sig_hdlr_complete,
	e_sig_hdlr_continue
} Eapp_sig_hdlr_status_t;

typedef struct threads_ctxt {
	/* Make sure the below starts at a different cache line */
	struct k_thread thread;
	char thread_name[MAX_APP_THREAD_NAME];
	int32_t prio;
	k_thread_entry_t thread_entry;
	struct k_poll_event *event_list;
	uint32_t *num_events;
	struct k_poll_signal *signal_list;
	uint32_t *num_signals;
	struct k_msgq *msg_q;
	uint32_t options;
	uint32_t cpu_mask; /**< Used to PIN threads or cluster */
	Eapp_threads_t app_thread_id;
	void *entry_func;
	struct z_thread_stack_element *tid_stack;
	uint32_t stack_size;
	uint32_t send_signals;
	uint32_t recv_signals;
	struct k_sem tsem;
} threads_ctxt_t;

extern threads_ctxt_t g_threads[e_app_threads_max];

void thread_event_loop_poll(void *event_list, void *n_events, void *thread_id);
void thread_event_loop(void *event_list, void *n_events, void *thread_id);

#endif /* __THREADS */
