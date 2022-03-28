#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"

struct hit_record {
	point3 p;
	vec3 normal;
	double t;
	bool front_face;

	// front-facing means that the ray and it's normal point do not face against each other geometrically
	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction, outward_normal) < 0; // note: 1 line function
		normal = front_face ? outward_normal : -outward_normal; // note: "normal" is defined in hit_record
	}
};

class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};


#endif