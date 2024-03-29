#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);
  Eigen::Vector3d v, l, ii, kd, ks, ka, Ia, h;
  double m1, m2,px, tt;
  Ray shadowRay;

  int shadow_hit = 0;
  double shadow_t;
  Eigen::Vector3d shadow_n;

  kd = objects[hit_id]->material->kd;
  ks = objects[hit_id]->material->ks;
  ka = objects[hit_id]->material->ka;
  px = objects[hit_id]->material->phong_exponent;

   for (int i = 0; i < lights.size(); i++) {
	  lights[i]->direction(ray.origin + t * ray.direction, l, tt);

	  shadowRay.origin = ray.origin + t * ray.direction;
	  shadowRay.direction = l;

	  if (!first_hit(shadowRay, 0.1,objects, shadow_hit, shadow_t, shadow_n)) {
			  v = ray.direction / sqrt(ray.direction.dot(ray.direction));
			  h = -v + l;
			  h = h / sqrt(h.dot(h));
			  m1 = n.dot(l) > 0 ? n.dot(l) : 0;
			  m2 = n.dot(h) > 0 ? n.dot(h) : 0;

			  ii = lights[i]->I;
			  rgb(0) = rgb(0) + m1 * ii(0)*kd(0) + pow(m2, px)*(ks(0) * ii(0));
			  rgb(1) = rgb(1) + m1 * ii(1)*kd(1) + pow(m2, px)*(ks(1) * ii(1));
			  rgb(2) = rgb(2) + m1 * ii(2)*kd(2) + pow(m2, px)*(ks(2) * ii(2));

	  }
	  else if (shadow_t > tt) {
		  v = ray.direction / sqrt(ray.direction.dot(ray.direction));
		  h = -v + l;
		  h = h / sqrt(h.dot(h));
		  m1 = n.dot(l) > 0 ? n.dot(l) : 0;
		  m2 = n.dot(h) > 0 ? n.dot(h) : 0;

		  ii = lights[i]->I;
		  rgb(0) = rgb(0) + m1 * ii(0)*kd(0) + pow(m2, px)*(ks(0) * ii(0));
		  rgb(1) = rgb(1) + m1 * ii(1)*kd(1) + pow(m2, px)*(ks(1) * ii(1));
		  rgb(2) = rgb(2) + m1 * ii(2)*kd(2) + pow(m2, px)*(ks(2) * ii(2));
	  }
  } 

  return rgb;

  ////////////////////////////////////////////////////////////////////////////
}
