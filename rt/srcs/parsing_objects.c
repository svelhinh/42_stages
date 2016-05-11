/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:29:15 by svelhinh          #+#    #+#             */
/*   Updated: 2016/05/11 15:07:37 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parsing_materials(t_material *materials, char *material)
{
	if (!ft_strcmp(material, "glass"))
	{
		materials->specular = 500;
		materials->specular_power = 200;
		materials->shiny = 1;
		materials->reflection = 0.5;
	}
	else if (!ft_strcmp(material, "metal"))
	{
		materials->specular = 500;
		materials->specular_power = 200;
		materials->shiny = 0;
		materials->reflection = 0;
	}
}

static void	parsing_options(char **tab, t_env *rt, int i)
{
	if (!ft_strcmp(tab[0], "radius"))
		rt->object[i].radius = ft_atof(tab[2]);
	else if (!ft_strcmp(tab[0], "pos"))
	{
		rt->object[i].center.x = ft_atof(tab[2]);
		rt->object[i].center.y = ft_atof(tab[3]);
		rt->object[i].center.z = ft_atof(tab[4]);
	}
	else if (!ft_strcmp(tab[0], "color"))
	{
		check_color(ft_atof(tab[2]), ft_atof(tab[3]), ft_atof(tab[4]));
		rt->object[i].color.r = ft_atof(tab[2]);
		rt->object[i].color.g = ft_atof(tab[3]);
		rt->object[i].color.b = ft_atof(tab[4]);
	}
	else if (!ft_strcmp(tab[0], "angle"))
	{
		rt->object[i].angle.x = ft_atof(tab[2]);
		rt->object[i].angle.y = ft_atof(tab[3]);
		rt->object[i].angle.z = ft_atof(tab[4]);
	}
	else if (!ft_strcmp(tab[0], "material"))
		parsing_materials(&rt->object[i].material, tab[2]);
	else if (!ft_strcmp(tab[0], "separation"))
		rt->object[i].separation = ft_atof(tab[2]);
	else if (!ft_strcmp(tab[0], "size"))
		rt->object[i].size = ft_atof(tab[2]);
}

void		parsing_objects(int fd, char *object, t_env *rt)
{
	char		*line;
	char		**tab;

	while (get_next_line(fd, &line) > 0 && line[0])
	{
		tab = ft_strsplit(line, ' ');
		if (!tab[2])
			ft_exit("\033[31mMissing parameter for an object\n");
		if (!ft_strcmp(object, "sphere"))
			rt->object[rt->i_obj].name = SPHERE;
		else if (!ft_strcmp(object, "plane"))
			rt->object[rt->i_obj].name = PLANE;
		else if (!ft_strcmp(object, "cylinder"))
			rt->object[rt->i_obj].name = CYLINDER;
		else if (!ft_strcmp(object, "cone"))
			rt->object[rt->i_obj].name = CONE;
		else if (!ft_strcmp(object, "disk"))
			rt->object[rt->i_obj].name = DISK;
		else if (!ft_strcmp(object, "half_sphere"))
			rt->object[rt->i_obj].name = HALF_SPHERE;
		else if (!ft_strcmp(object, "light"))
			rt->object[rt->i_obj].name = LIGHT;
		parsing_options(tab, rt, rt->i_obj);
		tab_free(tab);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	rt->i_obj++;
}
