/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:33:42 by vicalvez          #+#    #+#             */
/*   Updated: 2024/02/20 17:38:39 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	signal_handler(int sigint, siginfo_t *info, void *context)
{
	static int	bit;
	static int	i;

	(void) context;
	i = i | (sigint == SIGUSR2);
	bit++;
	if (bit == 8)
	{
		bit = 0;
		if (i == 0)
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR1);
			return ;
		}
		write(1, &i, 1);
		i = 0;
	}
	else
		i = i << 1;
}

int	main(void)
{
	struct sigaction	action;
	sigset_t			sigset;

	ft_printf("PID: %d\n", getpid());
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGTERM);
	action.sa_sigaction = signal_handler;
	action.sa_mask = sigset;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, 0);
	sigaction(SIGUSR2, &action, 0);
	ft_printf("Waiting for signals...\n");
	while (1)
		pause();
	return (0);
}
