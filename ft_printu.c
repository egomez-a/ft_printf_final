/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:40:40 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/27 18:05:04 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Include in the temp1 the result of the pointer, after allocating memory for it
*/
static void	ft_ptfu1(t_flags *flags, char **temp, char **str)
{
	if (flags->hasprecision == 1)
	{
		if (flags->precision > ft_strlen(*str))
			flags->d = flags->precision - ft_strlen(*str);
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
		(*temp)[ft_strlen((*str))] = '\0';
	}
}

static void	ft_ptfuwidth2(t_flags *flags, char **temp, char **tempw)
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
}

/*
** Take into account width elements, considering where to put spaces
*/
static void	ft_ptfuwidth(t_flags *flags, char **temp, char **tempw)
{
	if (flags->hasleft == 0)
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
	else if (flags->hasleft == 1)
	{
		if (flags->width > ft_strlen(*temp))
			ft_ptfuwidth2(flags, &(*temp), &(*tempw));
		else
			(*tempw) = ft_strjoin("", *temp);
	}
}

void	ft_printu(va_list args, t_flags *flags, int *pos)
{
	char	*str;
	char	*temp;
	char	*tempw;

	temp = NULL;
	tempw = NULL;
	flags->u = va_arg(args, unsigned int);
	if (flags->u == 0 && flags->hasprecision == 1)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	else
		str = ft_utoa(flags->u);
	ft_ptfu1(flags, &temp, &str);
	if (flags->haswidth == 1)
		ft_ptfuwidth(flags, &temp, &tempw);
	else
		(tempw) = ft_strjoin("", (temp));
	ft_putstr_fd(tempw, 1);
	(flags->count) += ft_strlen(tempw);
	free(temp);
	free(tempw);
	free(str);
	(*pos)++;
}
