/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:32:47 by vicalvez          #+#    #+#             */
/*   Updated: 2024/02/14 11:34:53 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"



int main(int argc, char **argv)
{
    (void) argc;
    int pid = ft_atoi(argv[1]);
    int res = kill(-pid, SIGUSR1);
    if (res == 0)
        ft_printf("send signal to %d\n", pid);
    else
        ft_printf("%s\n", strerror(errno));
    return (0);
}