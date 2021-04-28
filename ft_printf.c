/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:05:26 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/22 17:06:21 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check(const char *str, int *pos, t_flags *flags, va_list args)
{
	while (str[*pos] != '\0')
	{
		if (str[*pos] == '%' && str[*pos])
		{
			ft_flagsreset(flags);
			(*pos)++;
			ft_ckflags(args, str, flags, &(*pos));
			if (str[(*pos)] == 'c')
				ft_printchar(args, flags, &(*pos));
			else if (str[(*pos)] == 's')
				ft_printstring(args, flags, &(*pos));
			else if (str[(*pos)] == 'p')
				ft_printpointer(args, flags, &(*pos));
			else if ((str[(*pos)] == 'd') || (str[*pos] == 'i'))
				ft_printdecint(args, flags, &(*pos));
			else if (str[(*pos)] == 'u')
				ft_printu(args, flags, &(*pos));
			else if ((str[(*pos)] == 'x') || (str[(*pos)] == 'X'))
				ft_printx(args, flags, &(*pos));
			else if (str[(*pos)] == '%')
				ft_putcharpercent(flags, &(*pos));
		}
		else
			ft_putcharfdflags(str[(*pos)], 1, &(*pos), flags);
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		pos;
	t_flags	flags;

	pos = 0;
	flags.count = 0;
	va_start(args, str);
	ft_check(str, &pos, &flags, args);
	return (flags.count);
}
