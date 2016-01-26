/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 11:22:14 by svelhinh          #+#    #+#             */
/*   Updated: 2016/01/26 11:54:23 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	var_init(t_ray *r)
{
	// Position de la camera
	r->posX = 6;
	r->posY = 4;

	// Vecteur de direction
	r->dirX = -1;
	r->dirY = 0;

	// Vecteur du plan de projection
	r->planeX = 0;
	r->planeY = 1;
	r->x = 0;
	r->y = 0;
}

static void	init_rayons(t_ray *r)
{
	/*Le centre de l’écran de projection sur X est égal à 0
	La partie gauche de l’écran est égale à -1
	La partie droite de l’écran est égale à 1
	rayDir = vecteur de direction + (vecteur de l’écran * position de la colonne par rapport au centre de l’écran)*/

	//Position de départ et direction du rayon
	r->cameraX = 2 * r->x / SWIDTH - 1;			// Position de la colonne par rapport au centre de l’écran
	r->rayPosX = r->posX;							// Position de depart du rayon sur X
	r->rayPosY = r->posY;							// Position de depart du rayon sur Y
	r->rayDirX = r->dirX + r->planeX * r->cameraX;	// Direction du rayon sur X
	r->rayDirY = r->dirY + r->planeY * r->cameraX;	// Direction du rayon sur Y
}

static void	vector_calcul(t_ray *r)
{
	//calcule le vecteur de direction et la longueur entre deux segments
	if (r->rayDirX < 0)
	{
		r->stepX = -1; // Vecteur de direction
		r->sideDistX = (r->rayPosX - r->mapX) * r->deltaDistX;	//distance : (position actuelle de la caméra - position de la case dans
															//la map) * distance à parcourir entre deux intersections sur cet axe.
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - r->rayPosX) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (r->rayPosY - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - r->rayPosY) * r->deltaDistY;
	}
}

static void	hit_wall(t_ray *r, t_env e)
{
	// tant que le rayon ne rencontre pas de mur
	while (r->hit == 0)
	{
		// Passe à la case suivante sur X ou Y
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;	// agrandis le rayon
			r->mapX += r->stepX;				// prochaine case ou case précédente sur X
			r->side = 0;						// orientation du mur
		}
		else
		{
			r->sideDistY += r->deltaDistY;	// agrandis le rayon
			r->mapY += r->stepY;				// prochaine case ou case précédente sur Y
			r->side = 1;						// orientation du mur
		}

			// Si le rayon rencontre un mur
		if (e.map[r->mapY][r->mapX] > 0)
			r->hit = 1;						// Stoppe la boucle
	}
}

static void	calculs(t_ray *r)
{
	// Calcule la distance corrigée pour la projection
	if (r->side == 0)
		r->perpWallDist = fabs((r->mapX - r->rayPosX + (1 - r->stepX) / 2) / r->rayDirX);
	else
		r->perpWallDist = fabs((r->mapY - r->rayPosY + (1 - r->stepY) / 2) / r->rayDirY);

	// Calcule la hauteur de la ligne à tracer
	r->lineHeight = fabs(SHEIGHT / r->perpWallDist);

	// Calcule les pixels max haut et max bas de la colonne à tracer
	r->drawStart = -r->lineHeight / 2 + SHEIGHT / 2;
	r->drawEnd = r->lineHeight / 2 + SHEIGHT / 2;

	// Limite les zones de tracé a l'ecran
	if (r->drawStart < 0)
		r->drawStart = 0;
	if (r->drawEnd >= SHEIGHT)
		r->drawEnd = SHEIGHT - 1;
}

void		raycasting(t_env e)
{
	t_ray		r;

	var_init(&r);
	// Tant que la position du tracé est inférieure à la taille de l’écran de projection
	while (r.x < SWIDTH)
	{
		init_rayons(&r);
		// Sur quelle case est la camera
		r.mapX = r.rayPosX;
		r.mapY = r.rayPosY;

		// Longueur du rayon entre chaque intersection
		r.deltaDistX = sqrt(1 + pow(r.rayDirY, 2) / pow(r.rayDirX, 2));
		r.deltaDistY = sqrt(1 + pow(r.rayDirX, 2) / pow(r.rayDirY, 2));

		r.hit = 0; // Le rayon touche un mur ou pas

		vector_calcul(&r);
		hit_wall(&r, e);
		calculs(&r);
		r.y = r.drawStart;
		while (r.y < r.drawEnd)
		{
			r.color = 0xf2f2f2;			// Couleur de la ligne pour un mur N/S
			if (r.side == 1)
				r.color = 0xcccccc;		// Couleur de la ligne pour un mur E/O
			mlx_pixel_put(e.mlx, e.win, r.x, r.y, r.color);
			r.y++;
		}
		r.x++;
	}
}