/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:44:13 by woosekim          #+#    #+#             */
/*   Updated: 2023/04/09 11:46:42 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	process_signal(int signo)
{
	static t_wordinfo	word;

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
	signal(SIGUSR1, process_signal);
	signal(SIGUSR2, process_signal);
	while (1)
		pause();
	return (0);
}
