/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:44:09 by svelhinh          #+#    #+#             */
/*   Updated: 2015/12/03 17:12:49 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	int				i;

	i = 0;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	while (n)
	{
		if (csrc[i] == (unsigned char)c)
			return (&((char *)cdst)[i + 1]);
		cdst[i] = csrc[i];
		n--;
		i++;
	}
	return (NULL);
}
