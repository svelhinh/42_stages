/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 14:43:55 by svelhinh          #+#    #+#             */
/*   Updated: 2016/03/31 17:14:11 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "../libft/includes/get_next_line.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# define ESC 53

typedef struct	s_vector3d
{
	float		x;
	float		y;
	float		z;
}				t_vector3d;
typedef struct	s_rot
{
	float		x;
	float		y;
	float		z;
}				t_rot;
typedef struct	s_color
{
	float		red;
	float		green;
	float		blue;
}				t_color;
typedef struct	s_light
{
	t_vector3d	pos;
	t_color		intensity;
}				t_light;
typedef struct	s_sphere
{
	t_vector3d	pos;
	float		radius;
	t_color		color;
}				t_sphere;
typedef struct	s_plane
{
	t_vector3d	norm;
	t_color		color;
	t_rot		rot;
	float		height;
}				t_plane;
typedef struct	s_cylinder
{
	t_vector3d	vec;
	t_vector3d	start;
	float		height;
	float		radius;
	t_rot		rot;
	t_color		color;
}				t_cylinder;
typedef struct	s_cone
{
	t_vector3d	pos;
	float		radius;
	t_rot		rot;
	t_color		color;
}				t_cone;
typedef struct	s_ray
{
	t_vector3d	start;
	t_vector3d	dir;
}				t_ray;
typedef struct	s_rt
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			endian;
	int			bpp;
	int			size_line;
	int			background_color;
	int			nbs;
	int			nbp;
	int			nbc;
	int			nbco;
	int			nbl;
	int			currentobj;
	int			pixel_color;
	float		w;
	float		h;
	float		t;
	float		angle;
	float		m;
	t_vector3d	tmp;
	t_vector3d	tmp2;
	t_sphere	*s;
	t_plane		*p;
	t_cylinder	*c;
	t_cone		*co;
	t_ray		r;
	t_vector3d	campos;
	t_light		light;
	t_color		global_color;
	t_rot		rotcam;
}				t_rt;

/*
** ----------------------------- mlx -------------------------------------
*/
void			ft_exit(char *s);
void			mlx_pixel_put_to_image(int color, t_rt *v, int x, int y);
int				expose(t_rt *rt);
int				key_press(int keycode, t_rt *rt);
int				key_release(int keycode, t_rt *rt);
/*
** ------------------------------------------------------------------------
*/

/*
** --------------------------- render -------------------------------------
*/
void			render(t_rt *rt);
int				sphere(t_ray *r, t_sphere *s, float *t);
int				plane(t_ray *r, t_plane *p, float *t);
int				cylinder(t_ray *r, t_cylinder *c, float *t);
int				cone(t_ray *r, t_cone *co, float *t);
char			*intersect(t_rt *rt, int *currentobj, char *object);
t_vector3d		rotations(t_vector3d normal, float x, float y, float z);
/*
** ------------------------------------------------------------------------
*/

/*
** -------------------------- light ---------------------------------------
*/
void			light_sphere(t_rt *rt, float t, float tmp, int currentobj);
void			light_plane(t_rt *rt, float t, int currentobj);
void			light_cylinder(t_rt *rt, float t, int currentobj);
void			light_cone(t_rt *rt, float t, float tmp, int currentobj);
int				shadows(t_rt *rt, t_ray *light, float t);
/*
** ------------------------------------------------------------------------
*/

/*
** ------------------------ vectors ---------------------------------------
*/
t_vector3d		vectorsub(t_vector3d *v1, t_vector3d *v2, int i);
float			vectordot(t_vector3d *v1, t_vector3d *v2, int i);
t_vector3d		vectorscale(float c, t_vector3d *v);
t_vector3d		vectoradd(t_vector3d *v1, t_vector3d *v2);
t_vector3d		normalize(t_vector3d *v1);
/*
** ------------------------------------------------------------------------
*/

/*
** ------------------------ parsing ---------------------------------------
*/
void			global_parser(char *file, t_rt *rt);
void			parsing_camera(int fd, t_rt *rt);
void			parsing_light(int fd, t_rt *rt);
void			parsing_plane(int fd, t_rt *rt);
void			parsing_sphere(int fd, t_rt *rt);
void			parsing_cylinder(int fd, t_rt *rt);
void			parsing_cone(int fd, t_rt *rt);
void			parsing_rotations(t_rt *rt, int j, int i, char **line2);
void			parsing_color(t_rt *rt, int j, int i, char **line2);
/*
** -----------------------------------------------------------------------
*/

/*
** ------------------------ initialisation -------------------------------
*/
void			init_all(char *file, t_rt *rt);
void			count_objects(t_rt *rt, char *file);
void			init_light(t_rt *rt);
void			init_camera(t_rt *rt);
void			init_sphere(t_rt *rt);
void			init_plane(t_rt *rt);
void			init_cylinder(t_rt *rt);
void			init_cone(t_rt *rt);
/*
** ------------------------------------------------------------------------
*/

/*
** ------------------------ others ---------------------------------------
*/
void			line2_free(char **line2);
void			check_color(float r, float g, float b);
void			color(t_rt *rt, float red, float green, float blue);
void			missing_parameter(char **line2);
/*
** -------------------------------------------------------------------------
*/
#endif
