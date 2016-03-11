/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:41:50 by svelhinh          #+#    #+#             */
/*   Updated: 2016/03/11 11:41:24 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	*intersect_sphere(char *object)
{
	if (!ft_strstr(object, "sphere"))
	{
		(object) ? (ft_strdel(&object)) : (0);
		object = ft_strdup("sphere");
	}
	return (object);
}

static char	*intersect_plane(char *object)
{
	if (!ft_strstr(object, "plane"))
	{
		(object) ? (ft_strdel(&object)) : (0);
		object = ft_strdup("plane");
	}
	return (object);
}

char		*intersect(t_rt *rt, int *currentobj, char *object)
{
	int		i;
	float	t;
	int		imax;

	i = 0;
	t = 20000;
	*currentobj = -1;
	imax = (rt->nbp > rt->nbs) ? (rt->nbp) : (rt->nbs);
	while (i < imax)
	{
		if (i < rt->nbs && sphere(&rt->r, &rt->s[i], &t))
		{
			*currentobj = i;
			object = intersect_sphere(object);
		}
		if (i < rt->nbp && plane(&rt->r, &rt->p[i], &t))
		{
			*currentobj = i;
			object = intersect_plane(object);
		}
		i++;
	}
	return (object);
}