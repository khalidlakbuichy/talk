/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:13:05 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/26 16:24:04 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		write(1, "Message has been sucessfully send!\n", 36);
}

void	set_signal_action_client(void)
{
	struct sigaction sa;

	sa.sa_handler = &sig_handler;
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