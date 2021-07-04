#include "utils_minitalk.h"

static void sig_exit(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)sig;
	(void)info;
	ft_putstr_fd("Signal received\n", 1); //подтверждение сигнала, пришедшее к клиенту
}

static void trans(pid_t pid, char ch)
{
	int bit;
	int	k;

	bit = 128; // двоичное представление - 1000 0000
	while (bit > 0)
	{
		if (bit & ch)
			k = kill(pid, SIGUSR1); // отправляем 1
		else
			k = kill(pid, SIGUSR2); // отправляем 0
		if (k < 0) // если kill вернул -1, то сигнал не передался серверу, то есть неверный пид
		{
			ft_putstr_fd("Error pid\n", 1);
			exit(1);
		}
		bit = bit / 2; // (64, 32...) или 0100 0000 ...
		usleep(100); // задержка после каждого сигнала, чтобы сервер смог правильно обработать сигналы
	}
}

static void sig_transfer(pid_t pid, char **argv)
{
	int i;

	i = 0;
	while (argv[2][i])
	{
		trans(pid, argv[2][i]);
		i++;
	}
	trans(pid, '\0');// отправляем символ конца строки, это будет 0
}

int main(int argc, char **argv)
{
	pid_t	pid;
	struct sigaction	act;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid == 0) // если не число атои вернет 0
		{
			ft_putstr_fd("Error pid\n", 1);
			exit(1);
		}
		act.sa_flags = SA_SIGINFO; // это сигнал на принятие от сервера
		act.sa_sigaction = sig_exit; //  функция, которая выполняется, если сигнал пришел
		sigaction(SIGUSR2, &act, 0); // сигнал 2 должен прийти

		sig_transfer(pid, argv); // преобразование строки и отправка серверу



	}
	else if (argc < 3)
		ft_putstr_fd("Not enough parameters\n", 1);
	else
		ft_putstr_fd("Too much parameters\n", 1);
	return (0);
}
