#ifndef HITTABLELIST_H
#define HITTABLELIST_H
//#include "rtweekend.h"
#include "hittable.h"

#include <vector>

class hittableList : public hittable
{
	public:
		std::vector<shared_ptr<hittable>> objects;

		hittableList() {}
		hittableList(shared_ptr<hittable> object) { add(object); }

		void clear() { objects.clear(); }

		void add(shared_ptr<hittable> object)
		{
			objects.push_back(object);
		}

		bool hit(const ray& r, interval rayT, hitRecord& rec) const override
		{
			hitRecord tmpRec;
			bool hitAnything = false;
			auto closestSoFar = rayT.max;

			for(const auto& object : objects)
			{
				if(object->hit(r, interval(rayT.min, closestSoFar), tmpRec))
				{
					hitAnything = true;
					closestSoFar = tmpRec.t;
					rec = tmpRec;
				}
			}
			return hitAnything;
		}
};

#endif
