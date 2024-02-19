/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:33:42 by vicalvez          #+#    #+#             */
/*   Updated: 2024/02/20 00:06:16 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char *c;

int	get_value(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{	
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}


int	ft_atoi_base(char *str, char *base)
{
	int	blen;
	int	char_index;
	int	res;
	int	sign;

	blen = ft_strlen(base);
	res = 0;
	sign = 1;
	char_index = 0;
	
	while (str[char_index])
	{
		res = res * blen + get_value(str[char_index],
				base);
		char_index++;
	}
	return (res * sign);
}

void    parse_char(int val)
{
    int clen;

    clen = ft_strlen(c);
    c[clen] = '0' + val;
    //ft_printf("len %d\n", clen);
    if (ft_strlen(c) == 8)
    {
        // ft_printf("\nc: %s\n", c);
        // ft_printf("char: %d\n", ft_atoi_base(c, "01"));
        ft_printf("%c", ft_atoi_base(c, "01"));
        free(c);
        c = ft_calloc(sizeof(char), 9);
        //ft_printf("len after clear %d\n", ft_strlen(c));
    }
}

void    signal_handler(int sigint)
{
    //ft_printf("received a message on %d\n", sigint);
    if (sigint == SIGUSR1)
        parse_char(0);
    else if (sigint == SIGUSR2)
        parse_char(1);
}

int main()
{
    c = ft_calloc(sizeof(char), 9);
    ft_printf("PID: %d\n", getpid());
    struct sigaction action;
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGTERM);
    
    action.sa_handler = signal_handler;
    action.sa_mask = sigset;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    while (1){
        usleep(1);
    }

    free(c);
    return (0);
}