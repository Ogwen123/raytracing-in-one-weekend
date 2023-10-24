#ifndef RAYTRACING_IOW_SPHERE_H
#define RAYTRACING_IOW_SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere: public hittable {
public:
    sphere(point3 _centre, double _radius) : centre(_centre), radius(_radius) {}

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        vec3 oc = r.origin() - centre;
        double a = r.direction().length_squared(); // v.v = |v^2|
        double half_b = dot(oc, r.direction());
        double c = oc.length_squared() - pow(radius, 2);

        auto discriminant = pow(half_b, 2) - a*c;

        if (discriminant < 0) return false;

        double sqrtd = sqrt(discriminant);

        // find the nearest root within the acceptable range
        double root = (-half_b - sqrtd) / a;
        if (root <= ray_tmin || root >= ray_tmax) {
            root = (-half_b + sqrtd) / a;
            if (root <= ray_tmin || root >= ray_tmax) return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - centre) / radius;
        // makes sure the normal is in the opposite direction to the ray
        // to differentiate between rays hitting the inside and outside
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    point3 centre;
    double radius;
};

#endif //RAYTRACING_IOW_SPHERE_H
