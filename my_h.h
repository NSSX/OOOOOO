/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_h.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 15:30:13 by avella            #+#    #+#             */
/*   Updated: 2016/06/09 13:56:04 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_H_H
# define MY_H_H
# include "libft/includes/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))
# define WIDTH 500
# define HEIGHT 500
# define CONV_RAD(x)          (x * (M_PI/180))
# define REF 6

typedef struct						s_img
{
	double			cos;
	void			*mlx;
	void			*win;
	unsigned long	img_color;
	char			*data;
	void			*img_ptr;
	int				sizeline;
	int				bpp;
	int				x;
	int				y;
	int				endian;
	void			*mlx_ptr;
}									t_img;

typedef struct						s_vec3d
{
	double x;
	double y;
	double z;
}									t_vec3d;

typedef struct						s_pars
{
	int		i;
	char	*val1;
	char	*val2;
	char	*val3;
}									t_pars;

typedef struct						s_effect
{
	t_vec3d	bri;
	t_vec3d	vec;
	double	shadow;
	t_vec3d	light;
}									t_effect;

typedef struct						s_obj
{
  t_vec3d tab_pos[3];
	t_vec3d			rot;
	t_vec3d			color;
	double			size;
	double			intens;
	int				type;
	t_vec3d			pos;
    double neg;
  double ref;
  double refraction;
	struct s_obj	*next;
}									t_obj;

typedef struct						s_env
{
  t_vec3d ambient_light;
  int sky;
  int no;
	t_vec3d			sl;
	t_vec3d			pos;
	t_effect		effect;
	t_obj			*obj;
  t_img *skybox;
	t_obj			*obj_tmp;
	t_obj			*light;
	double			nl;
	double			value;
  int x;
	char			*name;
	t_img			*img;
	void			*mlx;
  double myv;
	double			det;
  double myetat;
	double			v2;
	double			v;
	void			*win;
	int				height;
	int				width;
  double type_actual;
  int nb_ref;
  int s;
  int y;
	t_vec3d			pixel_color;
  t_img *sol;
	t_vec3d			eye_pos;
	t_vec3d			eye_dir;
	t_vec3d			ray_origin;
	t_vec3d			ray_dir;
  double create;
  double t;
  double t0;
  double front2;
  double back2;
  double front;
  double back;
  double t1;
  double ts;
	double			sz;
}									t_env;

double norme_vector(t_vec3d *vec);
void								all_effect(t_env *e);
void								pixel_put_to_img(t_env *e, int x, int y);
double								give_shadow(t_env *e);
double								inter_shadow(t_env *e, t_vec3d *lpos);
t_obj								*all_inter(t_env *e);
int									event_mlx(int keycode, t_env *e);
t_vec3d								plus(t_vec3d *a, t_vec3d *b);
t_vec3d								mult_value(t_vec3d *a, double value);
void								ajust(t_vec3d *vec);
double								mult(t_vec3d *a, t_vec3d *b);
t_vec3d								a_moin_b(t_vec3d *a, t_vec3d *b);
t_vec3d								x_moin_x(t_vec3d *a, t_vec3d *b);
double								lim(double x, double min, double max);
void								limit_for_vec(t_vec3d *vec,
									double a, double b);
t_vec3d								a_x_b(t_vec3d *a, t_vec3d *b);
void								init_env(t_env *e);
t_vec3d								light_effect(t_env *e);
double								phong_alg(t_obj *obj,
									t_env *e);
t_vec3d								my_light(t_env *e);
t_vec3d								lambert_alg(t_obj *obj, t_env *e);
t_vec3d								give_vec(t_obj *obj, t_env *e);
void								ray_tracer(t_env *e);
void								init_viewpoint(t_env *e);
void								init_eye(t_env *e);
void								get_lightspot_number(t_env *e);
t_vec3d								eye_or(t_vec3d ray_or,
									t_vec3d pos);
void								rotate_z(double *x,
									double *y, double *z, double angle);
void								rotate_x(double *x,
									double *y, double *z, double angle);
void								rotate_y(double *x,
									double *y, double *z, double angle);
void								parsing(t_env *e, int argc, char *av);
void								movable(int keycode, t_env *e, int etat);
void								obj_rot(t_env *e, int action, int etat);
void								norme_obj_rot(int action, t_obj *obj);
void								another_keycode(int keycode, t_env *e);
int									expose_hook(t_env *e);
void								print_obj(int etat);
double								ret_val(double a, double b, double det);
t_vec3d								eye_or(t_vec3d ray_or, t_vec3d pos);
int									ret_val2(double a, double b,
									double det, t_env *e);
char								*chaine2(char *ch);
char								*chaine(char *ch);
t_obj								*add_list(t_env *e);
t_obj								*create(void);
void								err(void);
char								*ft_strjoin_carac(char const *s1, char s2);
void								norme_val1(char *chaine, t_pars *pars);
void								norme_val2(char *chaine, t_pars *pars);
void								norme_val3(char *chaine, t_pars *pars);
t_vec3d								*vec3d(char *chaine);
double								get_single_var(char *chaine);
void								cut_obj(char *temp, t_obj *obj);
void								trait_obj(char *here, t_obj *obj);
void								cut_pov(char *temp, t_obj *obj);
void								trait_pov(char *here, t_obj *obj);
void            my_pixel_put_to_image(t_img *myimg, int x, int y, int color);
void    eye_pos_dir(t_env *e, double x, double y);
t_vec3d final_color(t_env *e);
void    init_image(t_env *e);
t_vec3d give_color_to_pixel(t_env *e, double x, double y);
void try_obj_neg(t_env *e);
#endif
