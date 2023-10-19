#include <iostream>

#include "headers/vec3.h"
#include "headers/colour.h"
#include "headers/ray.h"

void progress_bar(int remaining, int total) {

    std::string bar = "\r[";

    const int PROGRESS_BAR_SECTIONS = 20;

    int percent = (int) round(100 - (((float) remaining/ (float) total)*100));

    for (int i = 0; i < round(percent/(100/PROGRESS_BAR_SECTIONS)); i++) {
        bar += '#';
    }

    for (int i = 0; i < PROGRESS_BAR_SECTIONS - round(percent/(100/PROGRESS_BAR_SECTIONS)); i++) {
        bar += '-';
    }
    bar += ( "] " + std::to_string(percent) + "%" + " | Remaining: " + std::to_string(remaining) + "\n");

    std::clog << bar << ' ' << std::flush;
}


double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    //double a = dot(r.direction(), r.direction());
    //double b = 2.0 * dot(oc, r.direction());
    //double c = dot(oc, oc) - pow(radius, 2);

    //double discriminant = pow(b, 2) - 4*a*c;

    double a = r.direction().length_squared(); // v.v = |v^2|
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - pow(radius, 2);

    auto discriminant = pow(half_b, 2) - a*c;

    //return (discriminant < 0) ? -1.0 : (-b - sqrt(discriminant) / (2.0*a));
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

colour ray_colour(const ray& r) {
    double t = hit_sphere(point3(0, 0, -1), 0.5, r);

    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*colour(N.x()+1, N.y()+1, N.z()+1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5*(unit_direction.y() + 1.0);

    return (1.0-a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
}

int main() {

    // vp = viewport

    // Image
    auto aspect_ratio = 16.0 / 9.0;

    int image_width = 400;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    // view port
    double vp_height = 2.0;
    auto vp_width = vp_height * (static_cast<double>(image_width)/image_height);

    double focal_length = 1.0;
    point3 camera_center = point3(0, 0, 0);

    vec3 vp_u = vec3(vp_width, 0, 0);
    vec3 vp_v = vec3(0, -vp_height, 0); // the vp height is negative because the y increases as we go down the vp, which we don't want

    vec3 pixel_delta_u = vp_u / image_width; // distance between horizontal pixels
    vec3 pixel_delta_v = vp_v / image_height; // distance between vertical pixels

    vec3 vp_upper_left = camera_center - vec3(0, 0, focal_length) - vp_u/2 - vp_v/2;
    vec3 pixel00_location = vp_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        progress_bar((image_height-j), image_height);
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;

            ray r(camera_center, ray_direction);
            colour pixel_colour = ray_colour(r);

            write_colour(std::cout, pixel_colour);
        }
        std::clog.clear();
    }

    std::clog << "\rDone.                 \n";
}

// 6.3 An Abstraction for Hittable Objects
