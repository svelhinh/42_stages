/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 14:19:17 by svelhinh          #+#    #+#             */
/*   Updated: 2015/12/11 13:45:35 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 4
# include <unistd.h>
# include "libft.h"

int					get_next_line(int const fd, char **line);
typedef struct		s_varg
{
	char			buf[BUFF_SIZE + 1];
	size_t			ret;
	size_t			len;
	size_t			start;
	size_t			result;
}					t_varg;

#endif