/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:44:13 by woosekim          #+#    #+#             */
/*   Updated: 2023/03/09 15:48:37 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_sig	g_server;

void	process_bit_signal(int signo, siginfo_t *siginfo, void *context);

void	connection_start(int signo, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (signo == SIGUSR1)
	{
		ft_printf("\n[Connection to Client : SUCCEED]\n");
		ft_printf("[Client PID : %d]\n", siginfo->si_pid);
		g_server.pid = siginfo->si_pid;
		kill(g_server.pid, signo);
		g_server.sigact.sa_sigaction = process_bit_signal;
		sigaction(SIGUSR1, &(g_server.sigact), NULL);
		sigaction(SIGUSR2, &(g_server.sigact), NULL);
	}
	else
		ft_printf("\n[Connection to Client : FAILED]\n");
}

void	connection_end(void)
{
	g_server.sigact.sa_sigaction = connection_start;
	sigaction(SIGUSR1, &(g_server.sigact), NULL);
	sigaction(SIGUSR2, &(g_server.sigact), NULL);
	kill(g_server.pid, SIGUSR2);
}

void	process_bit_signal(int signo, siginfo_t *siginfo, void *context)
{
	static t_wordinfo	word;

	(void)context;
	if (g_server.pid != siginfo->si_pid)
		return ;
	if (signo == SIGUSR1)
	{
		if (word.bit_idx < 8)
			word.bit_data = (word.bit_data << 1) | 1;
	}
	else if (signo == SIGUSR2)
	{
		if (word.bit_idx < 8)
			word.bit_data = (word.bit_data << 1) | 0;
	}
	word.bit_idx++;
	if (word.bit_idx == 8)
	{
		if (word.bit_data == 0)
			connection_end();
		else
			ft_printf("%c", word.bit_data);
		word.bit_idx = 0;
		word.bit_data = 0;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("[Server PID : %d]\n", pid);
	initial_signal_handler(&g_server, 0, NULL, connection_start);
	while (1)
		pause();
	return (0);
}
