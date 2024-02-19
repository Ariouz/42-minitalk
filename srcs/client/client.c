/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:32:47 by vicalvez          #+#    #+#             */
/*   Updated: 2024/02/19 12:17:14 by vicalvez         ###   ########.fr       */
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

int	ft_printlast(long nb, long m, char *base, int pid)
{
	int blen;

	blen = ft_strlen(base);
	if (nb > blen)
    {
		if (m == 0)
			send_sig(pid, SIGUSR1);
		else
			send_sig(pid, SIGUSR2);
		//ft_putchar_fd(base[m], 1);
	}
	else
	{
		//ft_putchar_fd(base[nb], 1);
		if (nb == 0)
			send_sig(pid, SIGUSR1);
		else
			send_sig(pid, SIGUSR2);
	}
	usleep(50);
	return (1);
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
		send_sig(pid, SIGUSR1);
		len++;
	}
}

void	ft_putnbr_base(int nb, char *base, int pid)
{
	long	nl;
	long	m;
	long	blen;

	blen = 0;
	m = 0;
	nl = nb;
	while (base[blen])
		blen++;
	if (blen < 2)
		return ;
	if (nl >= blen)
	{
		m = nl % blen;
		ft_putnbr_base((nl / blen), base, pid);
	}
	ft_printlast(nl, m, base, pid);
}

void    send_byte(unsigned char c, int pid)
{
	fill_bin_len(c, pid);
	usleep(20);
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