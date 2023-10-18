#include <iostream>

#include "include/vec3.h"
#include "include/colour.h"

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

int main() {

    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        progress_bar((image_height-j), image_height);
        std::clog.clear();
        for (int i = 0; i < image_width; ++i) {
            auto pixel_colour = colour(double(i)/(image_width-1), double(j)/(image_height-1), 0);

            write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "\rDone.                 \n";
}
