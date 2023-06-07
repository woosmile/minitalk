/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:44:17 by woosekim          #+#    #+#             */
/*   Updated: 2023/04/09 12:01:50 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_bit(pid_t pid, char *str)
{
	int	bit;
	int	bit_idx;

	bit = 0;
	while (*str != 0)
	{
		bit_idx = 7;
		while (bit_idx >= 0)
		{
			bit = (*str >> bit_idx) & 1;
			if (bit == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			bit_idx--;
		}
		str++;
	}
}

int	main(int ac, char *av[])
{
	pid_t	pid;

	if (ac != 3)
	{
		ft_printf("Invalid number of arguments.");
		return (0);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 100 || pid >= 99999)
	{
		ft_printf("Invalid PID.\n");
		return (0);
	}
	send_bit(pid, av[2]);
	return (0);
}
