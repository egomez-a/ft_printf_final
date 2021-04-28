/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 12:51:30 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/27 18:09:21 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pstwidth(t_flags *flags, char **pointer, char **tempw)
{
	if (flags->width > ft_strlen(*pointer))
		flags->w = (flags->width - ft_strlen(*pointer));
	else
		flags->w = 0;
	flags->spaces = ft_calloc(flags->w + 1, sizeof(char));
	if (flags->hasleft == 0)
	{
		if (flags->haszero == 1)
			ft_memset(flags->spaces, '0', flags->w);
		else
			ft_memset(flags->spaces, ' ', flags->w);
		flags->spaces[flags->w] = '\0';
		(*tempw) = ft_strjoin(flags->spaces, (*pointer));
		free(flags->spaces);
	}
	else if (flags->hasleft == 1)
	{
		ft_memset(flags->spaces, ' ', flags->w);
		flags->spaces[flags->w] = '\0';
		(*tempw) = ft_strjoin((*pointer), flags->spaces);
		free(flags->spaces);
	}
}

void	ft_pstnullprec(t_flags *flags, char *s, char **pointer)
{
	if (s == NULL)
	{
		(*pointer) = ft_strjoin("(null)", "");
		if (flags->hasprecision == 1)
			(*pointer)[flags->precision] = '\0';
	}
	else if ((flags->hasprecision == 1) && (flags->precision < ft_strlen(s)))
	{
		(*pointer) = ft_calloc((flags->precision + 1), sizeof(char));
		ft_memcpy((*pointer), s, flags->precision);
		(*pointer)[flags->precision + 1] = '\0';
	}
	else
	{
		(*pointer) = ft_calloc(ft_strlen(s) + 1, sizeof(char));
		ft_memcpy((*pointer), s, ft_strlen(s));
		(*pointer)[ft_strlen(s)] = '\0';
	}
}

void	ft_printstring(va_list args, t_flags *flags, int *pos)
{
	char	*s;
	char	*pointer;
	char	*tempw;

	s = va_arg(args, char *);
	tempw = NULL;
	ft_pstnullprec(flags, s, &pointer);
	if (flags->haswidth == 1)
		ft_pstwidth(flags, &pointer, &tempw);
	else
		(tempw) = ft_strjoin("", &(*pointer));
	ft_putstr_fd(tempw, 1);
	(flags->count) += ft_strlen(tempw);
	free(pointer);
	free(tempw);
	(*pos)++;
}
