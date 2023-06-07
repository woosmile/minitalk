/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:34:20 by woosekim          #+#    #+#             */
/*   Updated: 2023/03/09 15:46:10 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include "./ft_printf/ft_printf.h"

typedef struct sigaction	t_sigaction;

typedef struct s_sig
{
	t_sigaction	sigact;
	int			pid;
	char		*str;
}	t_sig;

typedef struct s_wordinfo
{
	char	bit_data;
	int		bit_idx;
}	t_wordinfo;

void	initial_signal_handler(t_sig *sig, pid_t pid, char *str, \
								void (*func)(int, siginfo_t *, void *));

#endif
