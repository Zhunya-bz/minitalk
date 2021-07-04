#include "utils_minitalk.h"

static void	sig_take(int sig, siginfo_t *info, void *ucontext)
{
	static int	c = 0;
	static int	count = 0;

	(void)info;
	(void)ucontext;
	if (sig == SIGUSR1)
		c += 1 << (7 - count);
	count++;
	if (count == 8)
	{
		ft_putchar_fd(c, 1);
		if (c == 0)
		{
			ft_putstr_fd("\n", 1);
			kill(info->si_pid, SIGUSR2);
		}
		count = 0;
		c = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	act;

	(void)argv;
	if (argc == 1)
	{
		ft_putstr_fd("Server start\n", 1);
		pid = getpid();
		ft_putstr_fd("PID: ", 1);
		ft_putnbr_fd(pid, 1);
		ft_putstr_fd("\n", 1);
		act.sa_flags = SA_SIGINFO;
		act.sa_sigaction = sig_take;
		sigaction(SIGUSR1, &act, 0);
		sigaction(SIGUSR2, &act, 0);
		while (1)
			;
	}
	else
		ft_putstr_fd("There should be no parameters\n", 1);
	return (0);
}
