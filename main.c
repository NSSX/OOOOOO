/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:10:06 by avella            #+#    #+#             */
/*   Updated: 2016/06/09 13:56:59 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

void	give_effect(t_env *e)
{
	e->effect.vec = give_vec(e->obj_tmp, e);
	e->effect.shadow = give_shadow(e);
	if(e->effect.shadow != 1)
	  {
	    e->effect.shadow = e->effect.shadow;//transparence
	  }
	e->effect.light = my_light(e);
	e->effect.bri = light_effect(e);
	//e->effect.light = mult_value(&(e->effect.light), e->effect.shadow);
	e->effect.bri = a_x_b(&(e->effect.bri), &(e->effect.light));
}

void	all_effect(t_env *e)
{
	give_effect(e);
	e->pixel_color = plus(&(e->pixel_color), &(e->effect.bri));
       	limit_for_vec(&(e->pixel_color), 0, 1);
	e->pixel_color = a_x_b(&(e->pixel_color), &(e->effect.light));
}

void	move_cam(t_env *e, int keycode)
{
	double a;
	double b;
	double val1;
	double val2;

	a = cos(e->v);
	b = sin(e->v);
	val1 = a * 5;
	val2 = b * 5;
	if (keycode == 13)
	{
		e->eye_pos.z -= val1;
		e->eye_pos.x += val2;
	}
	if (keycode == 1)
	{
		e->eye_pos.z += val1;
		e->eye_pos.x -= val2;
	}
}

int		event_mlx(int keycode, t_env *e)
{
	static int etat;

	if (!etat)
		etat = 0;
	if(keycode == 24)
	  {
	    //haut
	    e->eye_pos.y += 2;
	  }
	if(keycode == 27)
          {
            //bas
	    e->eye_pos.y -= 2;
          }

	another_keycode(keycode, e);
	move_cam(e, keycode);
	if(keycode == 8)
	  {
	    e->create++;
	    if(e->create > 4)
	      e->create = 0;
	    printf("CREATE ELEMENT : %f\n",e->create);
	    return(1);
	  }
	if (keycode == 49)
	{
		if (etat == 3)
			etat = 0;
		else
			etat++;
		ft_putstr("Etat Numero : ");
		ft_putnbr(etat);
		print_obj(etat);
	}
	movable(keycode, e, etat);
	/*15
5
11*/
	if(keycode == 15)
	  e->ambient_light.x += 0.1;
	if(keycode == 5)
          e->ambient_light.y += 0.1;
	if(keycode == 11)
          e->ambient_light.z += 0.1;
	if(keycode == 15 || keycode == 5 || keycode == 11)
	  printf("%f %f %f\n", e->ambient_light.x, e->ambient_light.y, e->ambient_light.z);
	ray_tracer(e);
	return (1);
}

void    ray_tracer_sub(t_env *e, int xref, int yref)
{
  int x;
  int y;

  init_image(e);
  y = 0;
  while (y < e->height)
    {
      e->y = y;
      x = 0;
      while (x < e->width)
	{
	  e->s = 0;
	  e->x = x;
	  e->pixel_color = give_color_to_pixel(e, x, y);
	  if(e->no == 0)
	    pixel_put_to_img(e, x, y);
	  e->no = 0;
	  x++;
	}
      y++;
    }
  mlx_put_image_to_window(e->mlx, e->win, e->img->img_ptr, 0, 0);
}




int mouse_mlx(int a, int x, int y, t_env *e)
{
  if(a == 5)
    {
      printf("DELETE\n");
      e->pixel_color = give_color_to_pixel(e, x, y);
      if(e->obj_tmp)
	{
	  t_obj *my_obj;
	  
	  my_obj = e->obj;
	  while(my_obj)
	    {
	      if(my_obj == e->obj_tmp)
		my_obj->type = 45;
	      my_obj = my_obj->next;
	    }
	}
      ray_tracer(e);
    }
  if(a == 1)
    {
      int i = 0;
      printf("molette\n");
      t_obj *my_obj;
      
      my_obj = e->obj;
      while(my_obj->next)
	{
      	  my_obj = my_obj->next;
	  i++;
	}
      my_obj->next = create();
      eye_pos_dir(e, x, y);
      t_vec3d var1 = mult_value(&(e->ray_dir),10);
      var1.x += e->ray_origin.x;
      var1.y += e->ray_origin.y;
      var1.z += e->ray_origin.z;
      my_obj->next->pos = (t_vec3d){var1.x,var1.y,var1.z};
      my_obj->next->type = e->create;
      ray_tracer(e);
    }
  return(1);
}


int		main(int ac, char **av)
{
	t_env e;

	init_env(&e);
	parsing(&e, ac, av[1]);
	init_eye(&e);
	get_lightspot_number(&e);
	init_viewpoint(&e);
	e.create = 1;
	e.v = 0;
	e.v2 = 0;
	e.nl = 1 / e.nl;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, e.width, e.height, e.name);
	ray_tracer(&e);
	//evenement souris//
	mlx_mouse_hook (e.win, mouse_mlx, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_key_hook(e.win, event_mlx, &e);
	mlx_loop(e.mlx);
	return (0);
}
