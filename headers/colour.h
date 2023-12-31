// NOT MY CODE, COPY/PASTED FROM THE BOOK

#ifndef colour_H
#define colour_H

#include "vec3.h"

#include <iostream>

using colour = vec3;

void write_colour(std::ostream &out, colour pixel_colour) {
    // Write the translated [0,255] value of each colour component.
    out << static_cast<int>(255.999 * pixel_colour.x()) << ' '
        << static_cast<int>(255.999 * pixel_colour.y()) << ' '
        << static_cast<int>(255.999 * pixel_colour.z()) << '\n';
}

#endif
