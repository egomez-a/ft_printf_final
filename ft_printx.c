/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 19:09:32 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/27 18:02:13 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pxprecision(t_flags *flags, char **temp, char **str)
{
	if (flags->hasprecision == 1)
	{
		if (flags->precision > ft_strlen(*str))
		{
			flags->d = flags->precision - ft_strlen(*str);
			if ((*str)[0] == '-')
				flags->d++;
		}
		else
			flags->d = 0;
		flags->spaces = ft_calloc(flags->d, sizeof(char));
		ft_memset(flags->spaces, '0', (flags->d));
		flags->spaces[flags->d] = '\0';
		(*temp) = ft_strjoin(flags->spaces, (*str));
		free(flags->spaces);
	}
	else
	{
		(*temp) = ft_calloc(ft_strlen(*str), sizeof(char));
		ft_memcpy((*temp), (*str), ft_strlen(*str));
		(*temp)[ft_strlen(*str)] = '\0';
	}
}

void	ft_pxwidth2(t_flags *flags, char **temp, char **tempw)
{
	if (flags->width > ft_strlen(*temp))
	{
		flags->d = flags->width - ft_strlen(*temp);
		flags->spaces = ft_calloc(flags->d, sizeof(char));
		if ((flags->haszero == 1) && ((flags->hasprecision == 0)
				|| ((flags->hasprecision == 1)
					&& (flags->precision > flags ->width))))
			ft_memset(flags->spaces, '0', flags->d);
		else
			ft_memset(flags->spaces, ' ', flags->d);
		flags->spaces[(flags->d)] = '\0';
		(*tempw) = ft_strjoin(flags->spaces, *(temp));
	}
	else
		(*tempw) = ft_strjoin("", *temp);
}

void	ft_pxwidth(t_flags *flags, char **temp, char **tempw)
{
	if (flags->hasleft == 0)
		ft_pxwidth2(flags, temp, tempw);
	else if (flags->hasleft == 1)
	{
		if (flags->width > ft_strlen(*temp))
		{
			flags->d = flags->width - ft_strlen(*temp);
			flags->spaces = ft_calloc(flags->d, sizeof(char));
			if ((flags->width >= flags->precision) || (flags->haszero == 0))
				ft_memset(flags->spaces, ' ', flags->d);
			else
				ft_memset(flags->spaces, '0', flags->d);
			flags->spaces[(flags->d)] = '\0';
			(*tempw) = ft_strjoin(*(temp), flags->spaces);
		}
		else
			(*tempw) = ft_strjoin("", *temp);
	}
}

static void	ft_ptfxnull(t_flags *flags, char **str)
{
	if (flags->d == 0)
	{
		if (flags->hasprecision == 1)
			(*str) = ft_calloc(sizeof(char), 1);
		else
		{
			(*str) = ft_calloc(sizeof(char), 2);
			(*str)[0] = '0';
		}
	}
	else
		(*str) = ft_uitohex(flags->d);
}

void	ft_printx(va_list args, t_flags *flags, int *pos)
{
	char	*str;
	char	*temp;
	char	*tempw;

	temp = NULL;
	tempw = NULL;
	flags->d = va_arg(args, unsigned int);
	ft_ptfxnull(flags, &str);
	ft_pxprecision(flags, &temp, &str);
	if (flags->haswidth == 1)
		ft_pxwidth(flags, &temp, &tempw);
	else
		(tempw) = ft_strjoin("", (temp));
	if (flags->hasxcaps == 1)
		(tempw) = ft_strtoupper(tempw);
	ft_putstr_fd(tempw, 1);
	(flags->count) += ft_strlen(tempw);
	free(temp);
	free(tempw);
	free(str);
	(*pos)++;
}
