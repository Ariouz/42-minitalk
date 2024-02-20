/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:32:47 by vicalvez          #+#    #+#             */
/*   Updated: 2024/02/20 17:45:18 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_sig(int pid, int sigint)
{
	int	res;

	res = kill(pid, sigint);
	if (res != 0)
	{
		ft_printf("Error: %s\n", strerror(errno));
		exit(1);
	}
}

void	send_char(char c, int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		if (c >> i & 1)
			send_sig(pid, SIGUSR2);
		else
			send_sig(pid, SIGUSR1);
		usleep(600);
	}
}

void	handle_sig(int signum)
{
	(void) signum;
	ft_printf("Server successfully received message.\nExiting...\n");
	exit(1);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	signal(SIGUSR1, handle_sig);
	if (argc < 3)
	{
		ft_printf("Error: You must provide a PID and a message to send.\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid == 0)
	{
		ft_printf("Error: Invalid PID\n");
		return (0);
	}
	i = 0;
	while (argv[2][i])
	{
		send_char(argv[2][i], pid);
		i++;
	}
	send_char(0, pid);
	while (1)
		pause();
	return (0);
}
