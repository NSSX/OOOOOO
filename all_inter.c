/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 16:57:53 by avella            #+#    #+#             */
/*   Updated: 2016/05/27 16:35:30 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

double		inter_sphere(t_obj *obj, t_env *e)
{
	t_vec3d		eo;
	double		a;
	double		b;
	double		c;
	t_vec3d		ray_dir;

	ray_dir = (t_vec3d){e->ray_dir.x, e->ray_dir.y, e->ray_dir.z};
	eo = eye_or(e->ray_origin, obj->pos);
	a = mult(&(ray_dir), &(ray_dir));
	b = mult(&eo, &(ray_dir));
	c = mult(&eo, &eo) - obj->size * obj->size;
    	e->det = b * b - a * c;
	if (e->det < 0.0001)
		return (-1);
	double back = (-b + sqrt(e->det)) / a;
	double front = (-b - sqrt(e->det)) / a;
	try_obj_neg(e);
	if(front >= e->front && front <= e->back)
	  {
	    if(back >= e->front && back <= e->back)
	      return(-1);
	    return(back);
	  }
       	if(front >= e->front2 && front <= e->back2)
          {
            if(back >= e->front2 && back <= e->back2)
              return(-1);
            return(back);
	    }
	if(front < 0)
	  {
	    if(back >= e->front && back <= e->back)
              return(-1);
	    if(back >= e->front2 && back <= e->back2)
              return(-1);
	    return(back);
	  }
	else
	    return(front);
}

typedef struct s_plan {
  double a;
  double b;
  double c;
  double d;
} t_plan;

double          geo_scalar_produce(t_vec3d u, t_vec3d v)
{
  return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3d        geo_vector_normal_vv(t_vec3d u, t_vec3d v)
{
  return ((t_vec3d){u.y * v.z - v.y * u.z,
	u.z * v.x - v.z * u.x,
	u.x * v.y - v.x * u.y});
}

t_vec3d        geo_vector_pp(t_vec3d a, t_vec3d b)
{
  return ((t_vec3d) {b.x - a.x, b.y - a.y, b.z - a.z});
}

t_plan  geo_plan(double a, double b, double c, double d)
{
    return ((t_plan) {a, b, c, d});
}

t_plan  geo_plan_pv(t_vec3d o, t_vec3d n)
{
  return (geo_plan(n.x, n.y, n.z, -n.x * o.x - n.y * o.y - n.z * o.z));
}

t_plan  geo_plan_pvv(t_vec3d p, t_vec3d u, t_vec3d v)
{
  return (geo_plan_pv(p, geo_vector_normal_vv(u, v)));
}

t_plan  geo_plan_ppp(t_vec3d a, t_vec3d b, t_vec3d c)
{
  return (geo_plan_pvv(a, geo_vector_pp(a, b), geo_vector_pp(a, c)));
}
//norme_vector
double inter_triangle(t_obj *obj, t_env *e)
{
  /*  t_vec3d a1 = (t_vec3d){0,1,0};
  t_vec3d a2 = (t_vec3d){0,5,0};
  t_vec3d a3 = (t_vec3d){3,3,0};*/
  t_vec3d a1 = obj->tab_pos[0];
  t_vec3d a2 = obj->tab_pos[1];
  t_vec3d a3 = obj->tab_pos[2];
 t_plan pl;
  double t;
  t_vec3d i;
  t_vec3d j;
  t_vec3d p;
  t_vec3d ray_origin = (t_vec3d){e->ray_origin.x, e->ray_origin.y, e->ray_origin.z};

  pl = geo_plan_ppp(a1, a2, a3);
  e->effect.vec = (t_vec3d){pl.a,pl.b,pl.c};
  //Pour la normal, pl.a pl.b pl.c  pl.x pl.y pl.z NORMAL TRIANGLE //A1 CEnter A2 haut A3 droite A2 et A3 deux point sur le cercle
  if ((t = pl.a * e->ray_dir.x + pl.b * e->ray_dir.y + pl.c * e->ray_dir.z) != 0)
    {
      t = (-pl.d - pl.a * ray_origin.x - pl.b * ray_origin.y - pl.c * ray_origin.z) / t;
      ray_origin = (t_vec3d){ray_origin.x + e->ray_dir.x * t, ray_origin.y + e->ray_dir.y * t, ray_origin.z + e->ray_dir.z * t};
      t *= norme_vector(&(e->ray_dir));
    }
  if (t < 0.0001)
    return (-1);
  i = geo_vector_pp(a1, a2);
  j = geo_vector_pp(a1, a3);
  p.x = (j.y * (ray_origin.x - a1.x) - j.x * (ray_origin.y - a1.y))
    / (j.y * i.x - j.x * i.y);
  p.y = (i.y * (ray_origin.x - a1.x) - i.x * (ray_origin.y - a1.y))
    / (i.y * j.x - i.x * j.y);
  //  if (p.x + p.y < 1 && p.x > 0 && p.y > 0)  
  //if (p.x < 1 && p.y < 1 && p.x > 0 && p.y > 0)
    if (p.x * p.x + p.y * p.y < 1)
  {
      return (t);
    }
  else
    return (-1);
}

double		inter_plan(t_obj *obj, t_env *e)
{
	double value;

	value = -((mult(&obj->rot, &(e->ray_origin)) - mult(&obj->rot, &obj->pos)) \
			/ mult(&obj->rot, &(e->ray_dir)));
	if (value < 0.0001)
		return (-1);
	return (value);
}

double		inter_cyl(t_obj *obj, t_env *e)
{
	t_vec3d		eo;
	double		a;
	double		b;
	double		c;
	t_vec3d		ray_dir;
	double t0;
	double t1;
	
       	ray_dir = (t_vec3d){e->ray_dir.x, e->ray_dir.y, e->ray_dir.z};
	eo = eye_or(e->ray_origin, obj->pos);
	rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
	rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
	rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
	rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.x);
	rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.y);
	rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
	a = ray_dir.x * ray_dir.x + ray_dir.z * ray_dir.z;
        b =  (2 * (ray_dir.x * eo.x)) + (2 * (ray_dir.z * eo.z));
        c = eo.x * eo.x + eo.z * eo.z - obj->size * obj->size;
	e->det = b *b - 4*a*c;
	//    e->front = 1000000;//pour avoir seulement le moment 
	//e->back = 1000000;
	if (e->det < 0.0001)
	  return (-1);
	t0 = (-b + sqrt(e->det)) / (2 * a);
	t1 = (-b - sqrt(e->det)) / (2 * a);
	/*	if(obj->neg == 1)
	  {
	    e->front = t1;
	    e->back = t0;
	    }*/
	if(t1 < 0)
	  return(t0);
	else
	  return(t1);

	//limited
		/*		if(t0 > t1)
	  {
	    float tmp = t0;
	    t0 = t1;
	    t1 = tmp;
	  }
		e->t0 = t0;
		e->t1 = t1;
	float y0 = eo.y + t0 * ray_dir.y;
	float y1 = eo.y + t1 * ray_dir.y;
	if (y0<-2)
	  {
	    if (y1<-2)
	      return (-1);
	    else
	      {
		// hit the cap
		float th = t0 + (t1-t0) * (y0+1) / (y0-y1);
		if (th<=0) return (-1);
		return ((-b - sqrt(e->det)) / (2 * a));
	      }
	  }
	else if (y0>=-2 && y0<=8)
	  {
	    // hit the cylinder bit
	    if (t0<=0) return (-1);
	    return ((-b - sqrt(e->det)) / (2 * a));
	  }
	else if (y0>8)
	  {
	    if (y1>8)
	      return (-1);
	    else
	      {
		// hit the cap
		float th = t0 + (t1-t0) * (y0-1) / (y0-y1);
		if (th<=0) return (-2);

		return ((-b - sqrt(e->det)) / (2 * a));
	      }
	  }
	  return (-1);*/
}

double		inter_cone(t_obj *obj, t_env *e)
{
	t_vec3d		eo;
	double		a;
	double		b;
	double		c;
	t_vec3d		ray_dir;

	ray_dir = (t_vec3d){e->ray_dir.x, e->ray_dir.y, e->ray_dir.z};
	eo = eye_or(e->ray_origin, obj->pos);
	rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
	rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
	rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
	rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.x);
	rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.y);
	rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
	a = ray_dir.x * ray_dir.x - ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	b = ray_dir.x * eo.x - ray_dir.y * eo.y + ray_dir.z * eo.z;
	c = eo.x * eo.x + eo.z * eo.z - eo.y * eo.y;
	e->det = b * b - a * c;
	if (e->det < 0.0001)
		return (-1);
	return (ret_val(a, b, e->det));
}

double          inter_cyl_neg(t_obj *obj, t_env *e)
{
  t_vec3d         eo;
  double          a;
  double          b;
  double          c;
  t_vec3d         ray_dir;
  double t0;
  double t1;

  ray_dir = (t_vec3d){e->ray_dir.x, e->ray_dir.y, e->ray_dir.z};
  eo = eye_or(e->ray_origin, obj->pos);
  rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
  rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
  rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
  rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.x);
  rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.y);
  rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
  a = ray_dir.x * ray_dir.x + ray_dir.z * ray_dir.z;
  b =  (2 * (ray_dir.x * eo.x)) + (2 * (ray_dir.z * eo.z));
  c = eo.x * eo.x + eo.z * eo.z - obj->size * obj->size;
  e->det = b *b - 4*a*c;
  e->front = 1000000;//pour avoir seulement le moment
  e->back = 1000000;
  if (e->det < 0.0001)
    {    
      return (-1);
    }
  t0 = (-b + sqrt(e->det)) / (2 * a);
  t1 = (-b - sqrt(e->det)) / (2 * a);
  e->front = t1;
  e->back = t0;
  if(t1 < 0)
    return(t0);
  else
    return(t1);
}

void try_obj_neg(t_env *e)
{
  t_obj *my_obj;
  double value;
  double vref;
  double front = 1000000;
  double back = 1000000;
  double front2 = 1000000;
  double back2 = 1000000;

  vref = 10000000;
  value = 10000000;
  my_obj = e->obj;
  while (my_obj)
    {
      if(my_obj->neg == 1)
	{
	  if (my_obj->type == 3)
	    value = inter_cyl_neg(my_obj, e);
	  if(front == 1000000)
	    {
	      front = e->front;
	      back = e->back;
	    }
	  else
	    {
	      front2 = e->front;
	      back2 = e->back;
	    }
	}
      my_obj = my_obj->next;
    }
  e->front = front;
  e->back = back;
  e->front2 = front2;
  e->back2 = back2;
}

/*double          ret_val(double a, double b, double det)
{
        return ((-b - sqrt(det)) / a);
}
*/
t_obj		*all_inter(t_env *e)
{
	t_obj		*my_obj;
	t_obj		*obj;
	double		value;
	double nb;
	double ok;
	
	ok = 0;
	nb = 0;
	obj = NULL;
	my_obj = e->obj;
	value = e->value;
	while (my_obj)
	{
	  if(my_obj->neg == 0)
	    {
		if (my_obj->type == 0)
		  value = inter_plan(my_obj, e);
		else if (my_obj->type == 3)
		  value = inter_cyl(my_obj, e);
		else if (my_obj->type == 1)// && e->type_actual != 1)
		  value = inter_sphere(my_obj, e);
		else if (my_obj->type == 2)
			value = inter_cone(my_obj, e);
		else if(my_obj->type == 4)
		  value = inter_triangle(my_obj, e);
		if ((value > 0.0001 && value < e->value))// && my_obj->neg == 0)
		      {
			if(e->myetat == 1 && e->myv == nb)
			  {
			    
			  }
			else
			  {
			    obj = my_obj;
			    e->value = value;
			    if(e->myetat == 0)
			      e->myv = nb;
			    ok = 0;
			  }
		  }
	    }
	  nb++;
	  my_obj = my_obj->next;
	}
	return (obj);
}
