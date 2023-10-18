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


colour ray_colour(const ray& r) {
    return colour(0, 0, 0);
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
        std::clog.clear();
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;

            ray r(camera_center, ray_direction);

            colour pixel_colour = ray_colour(r);

            write_colour(std::cout, pixel_colour);
            //auto pixel_colour = colour(double(i)/(image_width-1), double(j)/(image_height-1), 0);
            //write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.                 \n";
}

// upto just after listing 9 under subtitle "sending rays into the scene"
