#ifndef HITTABLE_H
#define HITTABLE_H

class material;

class hitRecord
{
	public:
		point3 p;
		vec3 normal;
		shared_ptr<material> mat;
		double t;
		bool frontFace;

		void setFaceNormal(const ray& r, const vec3& outwardNormal)
		{
			// sets if it hit it from front facing
			// outwardNormal is unit lenght and facing away from the object

			frontFace = (dot(r.direction(), outwardNormal) < 0);
			normal = frontFace ? outwardNormal : -outwardNormal;
		}
};

class hittable
{
	public:
		virtual ~hittable() = default;

		virtual bool hit(const ray& r, interval rayT, hitRecord& rec) const = 0;
};

#endif
