/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:28:49 by woosekim          #+#    #+#             */
/*   Updated: 2023/03/09 14:17:50 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	initial_signal_handler(t_sig *sig, pid_t pid, char *str, \
								void (*func)(int, siginfo_t *, void *))
{
	sig->sigact.sa_flags = SA_SIGINFO;
	sig->sigact.sa_sigaction = func;
	if (sigaction(SIGUSR1, &(sig->sigact), NULL) == -1)
	{
		ft_printf("[SIGNAL(SIGUSR1) ERROR!]\n");
		exit(1);
	}
	if (sigaction(SIGUSR2, &(sig->sigact), NULL) == -1)
	{
		ft_printf("[SIGNAL(SIGUSR2) ERROR!]\n");
		exit(1);
	}
	sig->pid = pid;
	sig->str = str;
	sigemptyset(&(sig->sigact.sa_mask));
}
