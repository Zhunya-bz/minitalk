#include "utils_minitalk.h"

static void sig_take(int sig, siginfo_t *info, void *ucontext)
{
	static int c = 0; // статические так как функция вызывается несколько раз и нужно запомнить предыдущее знаение
	static int count = 0;

	(void)info;
	(void)ucontext;
	if (sig == SIGUSR1)
		c += 1 << (7 - count); // сдвигаем единицу вперед и ставим в нужное место
	count++;
	if (count == 8) // если пришло все 8 символов (в 2 коде), то печатаем символ
	{
		ft_putchar_fd(c, 1);
		if (c == 0)
		{
			ft_putstr_fd("\n", 1);
			kill(info->si_pid, SIGUSR2); // info - узнает какой pid на клиенте, откуда пришел сигнал. Мы передаем 2сигнал к клиенту
		}
		count = 0;
		c = 0;
	}

}

int main(int argc, char **argv)
{
	pid_t	pid;
	struct sigaction	act; // структура для принятия сигналов

	(void)argv;
	if (argc == 1)
	{
		ft_putstr_fd("Server start\n", 1);
		pid = getpid(); // получаем пид текущего процесса
		ft_putstr_fd("PID: ", 1);
		ft_putnbr_fd(pid, 1);
		ft_putstr_fd("\n", 1);

		act.sa_flags = SA_SIGINFO; // это (флаг) сигнал на принятие от клиента
		act.sa_sigaction = sig_take; // функция, которая выполняется, если сигнал пришел
		sigaction(SIGUSR1, &act, 0); // чтобы принять 1 сигнал
		sigaction(SIGUSR2, &act, 0); // чтобы принять 2 сигнал

		while (1); // сервер ждет, пока не прийдет новый сигнал, если пришел то заходит в sig_take
	}
	else
		ft_putstr_fd("There should be no parameters\n", 1);
	return (0);
}
