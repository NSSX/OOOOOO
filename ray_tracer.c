/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 17:41:04 by avella            #+#    #+#             */
/*   Updated: 2016/06/09 12:59:29 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//Penser a faire une barre de chargement
#include "my_h.h"

#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define TAILLE 512
// On définit le nombre d'octaves.
#define OCTAVES 8
// On définit le pas.
#define PAS 128
// On définit la persistance.
#define PERSISTANCE 0.5
const double pi = 3.14159265;

static int pas1D = 0;
static int nombre_octaves1D = 0;
static int taille = 0;
static double* valeurs1D;

static int pas2D = 0;
static int nombre_octaves2D = 0;
static int hauteur = 0;
static int longueur = 0;
static int longueur_max = 0;
static double* valeurs2D;

void initBruit1D(int t, int p, int n) {
  nombre_octaves1D = n;
  if(taille != 0)
    free(valeurs1D);
  taille = t;
  pas1D = p;

  valeurs1D = (double*) malloc(sizeof(double) * (int) ceil(taille * pow(2, nombre_octaves1D  - 1)  / pas1D));

  srand(time(NULL));
  int i;
  for(i = 0; i < ceil(taille *  pow(2, nombre_octaves1D  - 1)  / pas1D); i++)
    valeurs1D[i] = (double) rand() / RAND_MAX;
}

void destroyBruit1D() {
  if(taille != 0)
    free(valeurs1D);
  taille = 0;
}

static double bruit1D(int i) {
  return valeurs1D[i];
}

static double interpolation_cos1D(double a, double b, double x) {
  double k = (1 - cos(x * pi)) / 2;
  return a * (1 - k) + b * k;
}

static double fonction_bruit1D(double x) {
  int i = (int) (x / pas1D);
  return interpolation_cos1D(bruit1D(i), bruit1D(i + 1), fmod(x / pas1D, 1));
}


double bruit_coherent1D(double x, double persistance) {
  double somme = 0;
  double p = 1;
  int f = 1;
  int i;

  for(i = 0 ; i < nombre_octaves1D ; i++) {
    somme += p * fonction_bruit1D(x * f);
    p *= persistance;
    f *= 2;
  }
  return somme * (1 - persistance) / (1 - p);
}

void initBruit2D(int l, int h, int p, int n) {
  nombre_octaves2D = n;
  if(taille != 0)
    free(valeurs2D);
  longueur = l;
  hauteur = h;
  pas2D = p;
  longueur_max = (int) ceil(longueur * pow(2, nombre_octaves2D  - 1)  / pas2D);
  int hauteur_max = (int) ceil(hauteur * pow(2, nombre_octaves2D  - 1)  / pas2D);

  valeurs2D = (double*) malloc(sizeof(double) * longueur_max * hauteur_max);

  srand(time(NULL));
  int i;
  for(i = 0; i < longueur_max * hauteur_max; i++)
    valeurs2D[i] = ((double) rand()) / RAND_MAX;
}

void destroyBruit2D() {
  if(longueur != 0)
    free(valeurs2D);
  longueur = 0;
}

static double bruit2D(int i, int j) {
  return valeurs2D[i * longueur_max + j];
}

static double interpolation_cos2D(double a, double b, double c, double d, double x, double y) {
  double y1 = interpolation_cos1D(a, b, x);
  double y2 = interpolation_cos1D(c, d, x);
  return  interpolation_cos1D(y1, y2, y);
}

static double fonction_bruit2D(double x, double y) {
  int i = (int) (x / pas2D);
  int j = (int) (y / pas2D);
  return interpolation_cos2D(bruit2D(i, j), bruit2D(i + 1, j), bruit2D(i, j + 1), bruit2D(i + 1, j + 1), fmod(x / pas2D, 1), fmod(y / pas2D, 1));
}

double bruit_coherent2D(double x, double y, double persistance) {
  double somme = 0;
  double p = 1;
  int f = 1;
  int i;

  for(i = 0 ; i < nombre_octaves2D ; i++) {
    somme += p * fonction_bruit2D(x * f, y * f);
    p *= persistance;
    f *= 2;
  }
  return somme * (1 - persistance) / (1 - p);
}

static t_vec3d c1 = {0.8, 0, 0}; // gris clair
static t_vec3d c2 = {0, 0, 0.8}; // blanc
static int lignes = 30;
static double perturbation = 0.25;

t_vec3d obtenirPixel(int x, int y) {

  double valeur = (1 - cos(lignes * 2 * M_PI * ((double)x / TAILLE + perturbation * bruit_coherent2D(x, y, PERSISTANCE)))) / 2;

  t_vec3d resultat;
  resultat.x = c1.x * (1 - valeur) + c2.x * valeur;
  resultat.y = c1.y * (1 - valeur) + c2.y * valeur;
  resultat.z = c1.z * (1 - valeur) + c2.z * valeur;
  return ((t_vec3d){resultat.x, resultat.y, resultat.z});
}

void	eye_pos_dir(t_env *e, double x, double y)
{
	double	cw;
	double	ch;

	cw = (e->width - x * 2) / e->height;
	ch = (e->height - y * 2) / e->height;
	e->ray_dir.x = -cos(e->v2) * sin(e->v)
		+ cw * cos(e->v) + ch * sin(e->v2) * sin(e->v);
	e->ray_dir.y = sin(e->v2) + ch * cos(e->v2);
	e->ray_dir.z = cos(e->v2) * cos(e->v)
		+ cw * sin(e->v) - ch * sin(e->v2) * cos(e->v);
	ajust(&(e->ray_dir));
	e->ray_dir.x = -e->ray_dir.x;
	e->ray_dir.z = -e->ray_dir.z;
	e->ray_origin = e->eye_pos;
	e->obj_tmp = NULL;
}

void	give_my_pos(t_env *e)
{
  e->pos.x = e->ray_origin.x + e->value * e->ray_dir.x;
  e->pos.y = e->ray_origin.y + e->value * e->ray_dir.y;
  e->pos.z = e->ray_origin.z + e->value * e->ray_dir.z;
  all_effect(e);
}

t_vec3d  ft_reflex(t_vec3d *incident, t_vec3d *n)
{
  t_vec3d  v;
  
  v.x = incident->x - 2.0 * mult(n, incident) * n->x;
  v.y = incident->y - 2.0 * mult(n, incident) * n->y;
  v.z = incident->z - 2.0 * mult(n, incident) * n->z;
  return (v);
}

/*
Données requises :
- l'indice de réfraction du premier matériel : probablement l'air, donc 1.
- l'indice de réfraction du second matériel : fixé dans les données entrées (entre 1 et 2.5).
- le vecteur du rayon émis par la source touchant le matériel 2.
- le vecteur de la normale de l'objet.

Donnée sortante :
- le vecteur dévié par l'indice de réfraction de l'objet percuté,
pouvant désormais toucher un nouvel objet et s'imprégner de sa couleur.

Condition :
- sin(angle d'incidence) <= (indice de réfraction2 / indice de réfraction1)
*/

t_vec3d   refract(t_env *e, t_vec3d *normal)//t_vec3d *ray, t_vec3d *normal)
{
  double  n;
  double  cosi;
  double  sint2;
  double  cost;
  t_vec3d   result;
  double n1 = 1;//no idea;
  double n2 = 1.05;//no idea;//1 = toute la sphere
 
  n = n1 / n2;
  cosi = -1 * mult(normal, &(e->ray_dir));
  sint2 = n * n * (1.0 - cosi * cosi);
   if (sint2 > 1.0)
     return(e->ray_dir);
   cost = sqrt(1.0 - sint2);
   result.x = n * e->ray_dir.x + (n * cosi - cost) * normal->x;
   result.y = n * e->ray_dir.y + (n * cosi - cost) * normal->y;
   result.z = n * e->ray_dir.z + (n * cosi - cost) * normal->z;
   return(result);
}
//POUR LE SOL
	  /*if(e->obj_tmp->type == 10)
	    {
	      int x = e->x + ((e->v / 0.2) * 50);
	      int y = e->y - ((e->v2 / 0.2) * 50);
	      y -=  e->eye_pos.z * 3;
	      if(x<0)
		x = -x;
	      if(y<0)
		y = -y;
	      int color1 = e->sol->data[y * e->sol->sizeline + x * e->sol->bpp / 8];
	      int color2 = e->sol->data[y * e->sol->sizeline + x * e->sol->bpp / 8 + 1];
	      int color3 = e->sol->data[y * e->sol->sizeline + x * e->sol->bpp / 8 + 2];
	      e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8] = color1;
	      e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8 + 1] = color2;
	      e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8 + 2] = color3;
	      e->no = 1;
	    }
	    else*/

  //POUR LE CIEL
  /*else
	  {
	    e->no = 1;
	    int x = e->x + ((e->v / 0.2) * 50);
	    int y = e->y + ((e->v2 / 0.2) * 20);
	    if(x<0)
	      x = -x;
	    if(y<0)
	      y = -y;
	    int color1 = e->skybox->data[y * e->skybox->sizeline + x * e->skybox->bpp / 8];
	    int color2 = e->skybox->data[y * e->skybox->sizeline + x * e->skybox->bpp / 8 + 1];
	    int color3 = e->skybox->data[y * e->skybox->sizeline + x * e->skybox->bpp / 8 + 2];
	    e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8] = color1;
	    e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8 + 1] = color2;
	    e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8 + 2] = color3;
	    }*/


t_vec3d reflexion_color(t_env *e, t_vec3d normal, t_vec3d color)
{
  double ref;
  t_vec3d col_tmp;
  t_vec3d reflex;

  ref = 1;
  if(e->obj_tmp->ref > 0)
    ref = e->obj_tmp->ref;
  if (ref < 1 && e->nb_ref < REF)
    {
      e->nb_ref += 1;
      reflex = ft_reflex(&(e->ray_dir), &normal );
      ajust(&reflex);
      normal  =  mult_value(&normal , 0.001);
      e->pos = plus(&(e->pos), &normal );
      color =  mult_value(&(color), ref);
      e->ray_origin = e->pos;
      e->ray_dir = reflex;
      col_tmp = final_color(e);
      col_tmp =  mult_value(&col_tmp, 1 - ref);
      color = plus(&(color), &col_tmp);
    }
  return(color);
}

t_vec3d refraction_color(t_env *e, t_vec3d normal, t_vec3d color)
{
  t_vec3d col_tmp;

  if(e->obj_tmp->refraction != 0 && e->myetat == 0)
    {
      e->myetat = 1;
      e->ray_dir = refract(e, &normal);
      ajust(&(e->ray_dir));
      color = mult_value(&(color), 0.8);
      col_tmp = final_color(e);
      col_tmp = mult_value(&col_tmp, 0.5);
      color = plus(&(color), &col_tmp);
    }
  return(color);
}

double arrondi(double value)
{
  //CREEE SOIT MEME FONCTION CEILL
  return(ceil(value));
}

double noise(int t)
{
  t = (t<<13) ^ t;
  t = (t * (t * t * 15731 + 789221) + 1376312589);
  return 1.0 - (t & 0x7fffffff) / 1073741824.0;
}

t_vec3d	final_color(t_env *e)
{
  t_vec3d normal;
  t_vec3d col_tmp;
  t_vec3d color;
  t_vec3d reflex;

  e->value = 100000000;
  e->obj_tmp = all_inter(e);
  e->pixel_color = (t_vec3d){0,0,0};
  color = (t_vec3d){0,0,0};
  if (e->obj_tmp && e->value > 0.0001)
	{
	  e->pixel_color = (t_vec3d){e->obj_tmp->color.x, e->obj_tmp->color.y, e->obj_tmp->color.z};
	  /*if(e->obj_tmp->type == 0)
	    {
	      t_vec3d mine;

	      e->pos.x = e->ray_origin.x + e->value * e->ray_dir.x;
	      e->pos.y = e->ray_origin.y + e->value * e->ray_dir.y;
	      e->pos.z = e->ray_origin.z + e->value * e->ray_dir.z;
	      if (fabs(e->pos.y) < 0.0001)
		e->pos.y = 0;
	      //CREER NOUS MEME LE FLOORF
	      mine.x = floorf(e->pos.x / 2);//2 longueur carreau 
	      mine.y = floorf(e->pos.y / 2);
	      mine.z = floorf(e->pos.z / 2);
	      if(fmod(mine.x+mine.z+mine.y,2) == 0)
		{
		  e->pixel_color = (t_vec3d){0,0,0};
		}
	      else
		e->pixel_color = (t_vec3d){1,1,1};
	    }*/
	  //texture
	  /*	   if(e->obj_tmp->type == 1)
		    {
	      e->no = 1;
	      double i;
	      double j;
	      double t;
	      double n = 1;
	      double u;
	      double v;
	      t_vec3d nor;

	      nor = give_vec(e->obj_tmp, e);
	      u = asin(-nor.x)/M_PI + 0.5f;
 	      v = asin(-nor.y)/M_PI + 0.5f;
	      u = u * 100;
	      v = v * 100;
	      //      u = (u * 990)/100;
	      // v = (v * 516)/100;
	           u = (u * 236)/100;
		   v = (v * 236)/100;
	
       		 
	      u = floorf(u);
	      v = floorf(v);
	      int color1 = e->skybox->data[(int)v * e->skybox->sizeline + (int)u * e->skybox->bpp / 8];
	      int color2 = e->skybox->data[(int)v * e->skybox->sizeline + (int)u * e->skybox->bpp / 8 + 1];
	      int color3 = e->skybox->data[(int)v * e->skybox->sizeline + (int)u * e->skybox->bpp / 8 + 2];
	      e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8] = color1;
	      e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8 + 1] = color2;
	      e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8 + 2] = color3;
	      }*/
	  /*if(e->obj_tmp->type == 1)
	    e->pixel_color = obtenirPixel(e->x, e->y);*/
	  //lumiere ambiante
	  e->pixel_color = plus(&(e->pixel_color), &(e->ambient_light));
	  if (e->value < 100000000)
	    give_my_pos(e);
	  color = e->pixel_color;
	  normal = give_vec(e->obj_tmp, e);
	  /*	  if(e->obj_tmp->refraction == 0.9 && e->myetat == 0)
	    {
	      e->myetat = 1;
	      color = mult_value(&(color), 0.5);
	      col_tmp = final_color(e);
	      color = plus(&(color), &col_tmp);
	      }*/
	  //color = reflexion_color(e, normal, color);
	  //color = refraction_color(e,normal, color);
	}
  else
    color = e->ambient_light;
  /*    else
    {
      e->no = 1;
      int x = e->x + ((e->v / 0.2) * 50);
      int y = e->y + ((e->v2 / 0.2) * 20);
      if(x<0)
	x = -x;
      if(y<0)
	y = -y;
      int color1 = e->skybox->data[y * e->skybox->sizeline + x * e->skybox->bpp / 8];
      int color2 = e->skybox->data[y * e->skybox->sizeline + x * e->skybox->bpp / 8 + 1];
      int color3 = e->skybox->data[y * e->skybox->sizeline + x * e->skybox->bpp / 8 + 2];
      e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8] = color1;
      e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8 + 1] = color2;
      e->img->data[e->y * e->img->sizeline + e->x * e->img->bpp / 8 + 2] = color3;
      }*/
  return (color);
}

t_vec3d	give_color_to_pixel(t_env *e, double x, double y)
{
	eye_pos_dir(e, x, y);
	e->pixel_color = (t_vec3d){0, 0, 0};
	e->nb_ref = 0;
	e->type_actual = 12;
	e->myetat = 0;
	e->myv = 0;
	e->pixel_color = final_color(e);
	return (e->pixel_color);
}

void	init_image(t_env *e)
{
	int a;
	int b;

	a = 0;
	b = 0;
	e->no = 0;
	e->sky = 0;
	e->img = (t_img *)malloc(sizeof(t_img) * 1);
	e->skybox = (t_img *)malloc(sizeof(t_img) * 1);
	e->sol = (t_img *)malloc(sizeof(t_img) * 1);
	e->img->img_ptr = mlx_new_image(e->mlx, e->width, e->height);
	e->img->data = mlx_get_data_addr(e->img->img_ptr,
	&e->img->bpp, &e->img->sizeline, &e->img->endian);
	e->skybox->img_ptr = mlx_xpm_file_to_image(e->mlx, "poke.xpm", &(a), &(b));
	e->skybox->data = mlx_get_data_addr(e->skybox->img_ptr,
					    &(e->skybox->bpp), &(e->skybox->sizeline), &(e->skybox->endian));
	e->sol->img_ptr = mlx_xpm_file_to_image(e->mlx, "sol.xpm", &(a), &(b));
	e->sol->data = mlx_get_data_addr(e->sol->img_ptr,
	&(e->sol->bpp), &(e->sol->sizeline), &(e->sol->endian));
}

void	ray_tracer(t_env *e)
{
	int x;
	int y;

	init_image(e);
	y = 0;
		  initBruit2D(TAILLE + 1, TAILLE + 1, PAS, OCTAVES);
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
		  destroyBruit2D();
	mlx_put_image_to_window(e->mlx, e->win, e->img->img_ptr, 0, 0);
}
