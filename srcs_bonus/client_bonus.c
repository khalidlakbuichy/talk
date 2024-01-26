/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:36:35 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/26 11:41:03 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	ft_send_bit(unsigned char c, pid_t pid)
{
	unsigned char	bit;

	bit = 0;
	bit = c & 1;
	if (bit == 1)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_putendl_fd("Error sending SIGUSR1 signal", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_putendl_fd("Error sending SIGUSR2 signal", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	usleep(50);
}

static void	ft_send_byte(unsigned char c, pid_t pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		ft_send_bit((c >> i & 1), pid);
		i--;
	}
}

static void	ft_send_string(char *str, pid_t pid)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		ft_send_byte(str[i], pid);
	ft_send_byte('\n', pid);
}
static void	ft_args_check(int ac, char **av)
{
	int	i;

	if (ac != 3)
	{
		ft_putendl_fd("Error: wrong format.", STDOUT_FILENO);
		ft_putendl_fd("[Example: ./client <PID> <MESSAGE>", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	if (*av[2] == '\0')
	{
		ft_putendl_fd("Error: message can not be empty!", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (av[1][++i] != '\0')
	{
		if (ft_isdigit(av[1][i]) == 0)
		{
			ft_putendl_fd("Error: wrong pid", STDOUT_FILENO);
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int ac, char **av)
{
	ft_args_check(ac, av);
	set_signal_action_client();
	ft_send_string(av[2], ft_atoi(av[1]));
}
