/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:36:38 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/26 15:49:07 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	ft_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
static void	ft_receive(int signal, siginfo_t *info, void *context)
{
	static unsigned char	byte;
	unsigned char			bit;
	static unsigned int		count_bits;

	(void) context;		
	bit = (signal == SIGUSR1);
	count_bits++;
	byte = (byte << 1) | bit;
	if (count_bits  == 8)
	{
		if (byte == '\0')
			kill(info->si_pid, SIGUSR1);
		write(1, &byte, 1);
		byte = 0;
		count_bits = 0;
	}
}

static void	set_signal_action(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ft_receive;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		ft_putendl_fd("Error: initialize and empty a signal set",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putendl_fd("Error: setting up SIGUSR1 handler", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putendl_fd("Error: setting up SIGUSR2 handler", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	ft_putstr_fd("[SERVER] - PID: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putendl_fd("\nWaiting for message...", STDOUT_FILENO);
	set_signal_action();
	while (TRUE)
		pause();
	return (EXIT_SUCCESS);
}
