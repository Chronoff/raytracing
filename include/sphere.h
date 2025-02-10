#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
	public:
		sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

		bool hit(const ray &r, double rayTmin, double rayTmax, hitRecord &rec) const override
		{
			vec3 oc = center - r.origin();
			auto a = r.direction().lenghtSquared();
			auto h = dot(r.direction(), oc);
			auto c = oc.lenghtSquared() - radius*radius;
			auto discriminant = h*h - a*c;
	
			if(discriminant < 0)
			{
				return false;
			}

			auto sqrtd = std::sqrt(discriminant);

			// find root in acceptable range

			auto root = (h - sqrtd) / a;
			if(root <= rayTmin || rayTmax <= root)
			{
				root = (h + sqrtd) / a;
				if(root <= rayTmin || rayTmax <= root) { return false; }
			}

			rec.t = root;
			rec.p = r.at(rec.t);
			vec3 outwardNormal = (rec.p - center) / radius;
			rec.setFaceNormal(r, outwardNormal);

			return true;
		}

	private:
		point3 center;
		double radius;
};

#endif
