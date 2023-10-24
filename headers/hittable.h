#ifndef RAYTRACING_IOW_HITTABLE_H
#define RAYTRACING_IOW_HITTABLE_H

#include "ray.h"

class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;

    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // outward normal is assumed to be a unit vector

        this->front_face = dot(r.direction(), outward_normal) < 0;
        this->normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable{ // virtual keyword lets you redefine the member in a derived class
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif //RAYTRACING_IOW_HITTABLE_H
