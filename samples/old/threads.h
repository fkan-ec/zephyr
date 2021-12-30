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
	e_app_threads_d,
	e_app_threads_e,
	e_app_threads_max

} Eapp_threads_t;

typedef enum app_sig_hdlr_status {
	e_sig_hdlr_complete,
	e_sig_hdlr_continue
} Eapp_sig_hdlr_status_t;

typedef struct app_sig_hdlr_ctxt {
	Eapp_sig_hdlr_status_t (*hdlr_fn)(void *);
	void *arg;
} app_sig_hdlr_ctxt_t;

typedef enum thread_a_signal_id {
	e_thread_a_timers_sig_id_max = APP_THREADS_MAX_TIMERS - 1,

	e_thread_a_sample_sig_id,

	e_thread_a_sig_id_max

} Ethread_a_signal_id_t;

typedef enum thread_b_signal_id {
	e_thread_b_timers_sig_id_max = APP_THREADS_MAX_TIMERS - 1,

	e_thread_b_sample_sig_id,

	e_thread_b_sig_id_max

} Ethread_b_signal_id_t;

typedef enum thread_c_signal_id {
	e_thread_c_timers_sig_id_max = APP_THREADS_MAX_TIMERS - 1,

	e_thread_c_sample_sig_id,

	e_thread_c_sig_id_max

} Ethread_c_signal_id_t;

typedef enum thread_d_signal_id {
	e_thread_d_timers_sig_id_max = APP_THREADS_MAX_TIMERS - 1,

	e_thread_d_sample_sig_id,

	e_thread_d_sig_id_max

} Ethread_d_signal_id_t;

typedef enum thread_e_signal_id {
	e_thread_e_timers_sig_id_max = APP_THREADS_MAX_TIMERS - 1,

	e_thread_e_sample_sig_id,

	e_thread_e_sig_id_max

} Ethread_e_signal_id_t;

#define CACHE_LINE_SIZE 64
typedef struct threads_ctxt {
	char pad0[CACHE_LINE_SIZE];
	/* Make sure the below starts at a different cache line */
	struct k_thread thread;
	char thread_name[MAX_APP_THREAD_NAME];
	int32_t prio;
	k_thread_entry_t thread_entry;
	struct k_poll_event *event_list;
	uint32_t *num_events;
	struct k_poll_signal *signal_list;
	uint32_t *num_signals;
	app_sig_hdlr_ctxt_t *sig_hdlr;
	struct k_msgq *msg_q;
	uint32_t options;
	uint32_t cpu_mask; /**< Used to PIN threads or cluster */
	Eapp_threads_t app_thread_id;
	void *entry_func;
	struct z_thread_stack_element *tid_stack;
	uint32_t stack_size;
	uint32_t send_signals;
	uint32_t recv_signals;
} threads_ctxt_t;

extern threads_ctxt_t g_threads[e_app_threads_max];

void thread_event_loop_poll(void *event_list, void *n_events, void *thread_id);
void thread_event_loop(void *event_list, void *n_events, void *thread_id);

#endif /* __THREADS */
