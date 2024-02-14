/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:33:42 by vicalvez          #+#    #+#             */
/*   Updated: 2024/02/14 11:20:27 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void    receive(int signint)
{
    ft_printf("received a message on %d\n", signint);
}

int main()
{
    
    ft_printf("PID: %d\n", getpid());
    signal(SIGUSR1, receive);

    while (1);

    return (0);
}