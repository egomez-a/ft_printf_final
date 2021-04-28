/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:05:41 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/19 16:17:34 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_flags
{
	int				haswidth;
	int				haszero;
	int				hasprecision;
	int				hasleft;
	int				hashex;
	int				hasxcaps;
	size_t			count;
	size_t			width;
	size_t			precision;
	size_t			left;
	size_t			i;
	int				w;
	unsigned int	d;
	unsigned int	u;
	char			*spaces;
}					t_flags;

int					ft_printf(const char *str, ...);
void				ft_flagsreset(t_flags *flags);
void				ft_putcharfdflags(char c, int fd, int *pos, t_flags *flags);
void				ft_printchar(va_list args, t_flags *flags, int *pos);
void				ft_putspace(size_t i, t_flags *flags);
void				ft_printdecint(va_list args, t_flags *flags, int *pos);
void				ft_printu(va_list args, t_flags *flags, int *pos);
void				ft_putcharpercent(t_flags *flags, int *pos);
void				ft_check(const char *str, int *pos, t_flags *flags,
						va_list args);
void				ft_ckflags(va_list args, const char *str, t_flags *flags,
						int *pos);
void				ft_printstring(va_list args, t_flags *flags, int *pos);
void				ft_pstnullprec(t_flags *flags, char *s, char **temp);
void				ft_pstwidth(t_flags *flags, char **temp, char **tempw);
void				ft_printpointer(va_list args, t_flags *flags, int *pos);
char				*ft_uitohex(unsigned int decimalnumber);
char				*ft_ulongtohex(unsigned long decimalnumber);
char				*ft_utoa(unsigned int u);
char				*ft_revstr(char *str);
void				ft_printx(va_list args, t_flags *flags, int *pos);
char				*ft_moveminus(char *s);
char				*ft_strtoupper(char *str);

#endif
