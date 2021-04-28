/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharpercent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 23:25:44 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/09 16:58:23 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putcharpcntleft(t_flags *flags)
{
	while (flags->i < (flags->width - 1))
	{
		ft_putchar_fd(' ', 1);
		flags->i++;
		flags->count++;
	}
}

void	ft_putcharpercent(t_flags *flags, int *pos)
{
	flags->i = 0;
	if ((flags->haswidth == 1 && flags->hasleft == 0))
	{
		while (flags->i < (flags->width - 1))
		{
			if (flags->haszero == 1)
			{
				ft_putchar_fd('0', 1);
				flags->i++;
				flags->count++;
			}
			else
			{
				ft_putchar_fd(' ', 1);
				flags->i++;
				flags->count++;
			}
		}
	}
	ft_putchar_fd('%', 1);
	flags->count++;
	if (flags->haswidth == 1 && flags->hasleft == 1)
		ft_putcharpcntleft(flags);
	(*pos)++;
}
