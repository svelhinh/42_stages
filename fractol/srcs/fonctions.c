/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 10:53:35 by svelhinh          #+#    #+#             */
/*   Updated: 2016/01/18 18:05:17 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		var_init(t_fract *e)
{
	if (!ft_strcmp(e->fract, "mandelbrot"))
	{
		e->x1 = -2.2;
		e->x2 = 0.8;
		e->y1 = -1.2;
		e->y2 = 1.2;
	}
	if (!ft_strcmp(e->fract, "julia"))
	{
		e->x1 = -1.5;
		e->x2 = 1.5;
		e->y1 = -1.5;
		e->y2 = 1.5;
	}
	e->coeffx = 0;
	e->coeffy = 0;
	e->fractx = WIDTH - 100 / (2000 / WIDTH);
	e->fracty = HEIGHT - 100 / (1500 / HEIGHT);
	e->y = 0;
	e->i_max = 50;
}
