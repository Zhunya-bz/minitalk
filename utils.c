#include "utils_minitalk.h"

int	ft_atoi(char *str)
{
	unsigned int	i;
	int				sign;
	unsigned long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (((str[i] > 8) && (str[i] < 14)) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] && str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if ((sign == -1) && (res > 9223372036854775808u))
		return (0);
	if ((sign == 1) && (res >= 9223372036854775808u))
		return (-1);
	return (sign * res);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static void	go_nbr(long nb, char a, char *arr, int fd)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	if (nb == 0)
		ft_putchar_fd('0', fd);
	while (nb != 0)
	{
		a = nb % 10 + '0';
		nb = nb / 10;
		arr[i] = a;
		i++;
	}
	arr[i] = '\0';
}

void	ft_putnbr_fd(int n, int fd)
{
	char	arr[11];
	char	a;
	int		i;

	i = 0;
	a = '\0';
	go_nbr((long)n, a, arr, fd);
	while (arr[i])
		i++;
	i--;
	while (i >= 0)
	{
		write(fd, &arr[i], 1);
		i--;
	}
}
