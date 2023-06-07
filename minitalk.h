/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woosekim <woosekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:34:20 by woosekim          #+#    #+#             */
/*   Updated: 2023/04/09 11:46:40 by woosekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "./ft_printf/ft_printf.h"

typedef struct s_wordinfo
{
	char	bit_data;
	int		bit_idx;
}	t_wordinfo;

#endif