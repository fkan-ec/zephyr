#include <stdio.h>
#include <stdlib.h>
#include <zephyr.h>
#include <threads.h>
#include <shell/shell.h>

extern void threads_init(void);

int main()
{
	printf("Entered Main \n");
	printf("Initializing threads\n");
	threads_init();

	while(1) {
		int i;
		for (i = 0; i < 3; i++) {
			struct k_poll_signal *my_signal = &g_threads[i].signal_list[0];
			if (k_poll_signal_raise(my_signal, 0) != 0)
				printk("signal raise failed \n");
			g_threads[i].send_signals += 1;
		}
	};
	printk("main routine exited\n");
	return 0;
}

static int cmd_timer_info(const struct shell *shell, size_t argc, char **argv)
{
	int i;
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	printk("Timer Info:\n");
	for (i = 0; i < 3; i++) {
		printk("%d: send %d, recv %d\n", i, g_threads[i].send_signals, g_threads[i].recv_signals);
	}
	return 0;
}

#define TIMER_INFO_CMD "Timer Info"

SHELL_STATIC_SUBCMD_SET_CREATE(sub_thread,
			       SHELL_CMD_ARG(info, NULL, TIMER_INFO_CMD, cmd_timer_info, 1, 0),
			       SHELL_SUBCMD_SET_END /* Array terminated. */
);

SHELL_CMD_REGISTER(timer, &sub_thread, "Timer related commands.", NULL);