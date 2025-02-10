#include <iostream>

#include "color.h"
#include "vec3.h"
#include "ray.h"

double hitSphere(const point3& center, double radius, const ray& r) // center is center of a sphere
{
	vec3 oc = center - r.origin();
	auto a = r.direction().lenghtSquared();
	auto h = dot(r.direction(), oc);
	auto c = oc.lenghtSquared() - radius*radius;
	auto discriminant = h*h - a*c;
	
	if(discriminant < 0)
	{
		return -1.0;
	} else
	{
		return (h - std::sqrt(discriminant)) / a;
	}
}

color rayColor(const ray& r)
{
	auto t = hitSphere(point3(0, 0, -1), 0.5, r);
	if(t > 0)
	{
		vec3 N = unitVector(r.at(t) - vec3(0, 0, -1));
		return 0.5*color(N.x() + 1, N.y() + 1, N.z() + 1);
	}

	vec3 unitDirection = unitVector(r.direction());
	auto a = 0.5*(unitDirection.y() + 1.0);
	return (1.0 - a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main()
{

        // Image

        auto aspectRatio = 16.0/9.0;
        int imageWidth = 400;

	int imageHeight = int(imageWidth / aspectRatio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	// camera
	
	auto focalLength = 1.0;
	auto viewportHeight = 2.0;
	auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
	auto cameraCenter = point3(0, 0, 0);

	// calculate vectors by which is viewport offset by from camera
	
	auto viewportU = vec3(viewportWidth, 0, 0);
	auto viewportV = vec3(0, -viewportHeight, 0);

	// distance between pixels
	
	auto pixelDeltaU = viewportU/imageWidth;
	auto pixelDeltaV = viewportV/imageHeight;

	// find upper left pixel
	
	auto viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength) - viewportU/2 - viewportV/2;
	auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

        // Render

        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

        for (int j = 0; j < imageHeight; j++)
	{
		std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;

            	for (int i = 0; i < imageWidth; i++)
		{
			auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
			auto rayDirection = pixelCenter - cameraCenter;
			ray r(cameraCenter, rayDirection);

			color pixelColor = rayColor(r);
			writeColor(std::cout, pixelColor);
		}
        }
	std::clog << "\rdone.                 \n";
}
