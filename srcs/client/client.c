/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:32:47 by vicalvez          #+#    #+#             */
/*   Updated: 2024/02/20 00:08:30 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void    send_sig(int pid, int sigint)
{
    int res = kill(-pid, sigint);
    if (res == 0)
		ft_printf("send signal to %d\n", pid);
    else
        ft_printf("%s\n", strerror(errno));
}

void	fill_bin_len(int n, int pid)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 2;
		len++;
	}
	while (len < 8)
	{
		ft_printf("send 0 sig filling\n");
		send_sig(pid, SIGUSR1);
		len++;
	}
}

void	ft_putnbr_base(int nb, char *base, int pid)
{
	int			base_len;
	long int	nbb;

	nbb = (long int) nb;
	base_len = ft_strlen(base);
	usleep(20);
	if (nbb >= 0 && nbb < base_len)
	{
		write(1, &base[nbb], 1);
		if (nbb == 0)
			send_sig(pid, SIGUSR1);
		else
			send_sig(pid, SIGUSR2);
	}
	else
	{
		ft_putnbr_base(nbb / base_len, base, pid);
		ft_putnbr_base(nbb % base_len, base, pid);
	}
}

void    send_byte(unsigned char c, int pid)
{
	fill_bin_len(c, pid);
	usleep(20);
	ft_printf("sending char %c code %d\n", c, c);
    ft_putnbr_base(c, "01", pid);
}

int main(int argc, char **argv)
{
    if (argc < 3)
	{
		return (0);
	}
    int pid = ft_atoi(argv[1]);
    
	int	i;
	i = 0;
    while (argv[2][i])
	{
		send_byte(argv[2][i], pid);
		usleep(20);
		i++;
	}
    return (0);
}