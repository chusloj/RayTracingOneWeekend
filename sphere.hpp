#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable {
public:
	sphere() {}
	sphere(point3 cen, double r) : center(cen), radius(r) {};

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    
    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) { // no solution
    	return false;
    }
    auto sqrtd = sqrt(discriminant);

    // Find whether the positive or negative root lies within [t_min, t_max]
    auto root = (-half_b - sqrtd) / a; // 1st root uses negative sqrtd
    if (root < t_min || root > t_max) {
    	root = (-half_b + sqrtd) / a; // 2nd root uses positive sqrtd
    	if (root < t_min || root > t_max) {
    		return false; // if neither are in range, then no hit
    	}
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
}



#endif
