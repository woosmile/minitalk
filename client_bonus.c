/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:44:17 by woosekim          #+#    #+#             */
/*   Updated: 2023/04/09 11:56:25 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_sig	g_client;

void	send_bit(pid_t pid, char *str)
{
	int		bit;
	int		bit_idx;

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
	bit_idx = 0;
	while (bit_idx++ < 8)
	{
		kill(pid, SIGUSR2);
		usleep(100);
	}
}

void	connection_end(int signo, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signo == SIGUSR2)
	{
		ft_printf("[Message Transmission : SUCCEED]\n");
		exit(0);
	}
	else
	{
		ft_printf("[Message Transmission : FAILED]\n");
		exit(1);
	}
}

void	connection_start(int signo, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signo == SIGUSR1)
	{
		ft_printf("[Connection to Server : SUCCEED]\n");
		g_client.sigact.sa_sigaction = connection_end;
		sigaction(SIGUSR1, &g_client.sigact, NULL);
		sigaction(SIGUSR2, &g_client.sigact, NULL);
		send_bit(g_client.pid, g_client.str);
		pause();
	}
	else
	{
		ft_printf("[Connection to Server : FAILED]\n");
		exit(1);
	}
}

int	main(int ac, char *av[])
{
	pid_t	server_pid;
	int		count;

	count = 0;
	if (ac != 3)
	{
		ft_printf("[Invalid number of arguments.]\n");
		exit(1);
	}
	ft_printf("[Client PID : %d]\n", getpid());
	server_pid = ft_atoi(av[1]);
	if (server_pid <= 100 || server_pid >= 99999)
	{
		ft_printf("[Invalid PID.]\n");
		exit(1);
	}
	initial_signal_handler(&g_client, server_pid, av[2], connection_start);
	while (1)
	{
		kill(server_pid, SIGUSR1);
		ft_printf("\n[Wait Count : %d]\n", count++);
		sleep(1);
	}
	pause();
	return (0);
}
