#include "triangle.h"
#include <iostream>
#define THOMAS 1

Triangle::Triangle( void )
{}

Triangle::Triangle( const glm::vec3 &v0, const glm::vec3 &v1,
                    const glm::vec3 &v2, const glm::vec3 &color, const Material* material ):
                    Primitive(material),
          v0{ v0 },
          v1{ v1 },
          v2{ v2 },
          color{ color }
{}

Triangle::Triangle( const glm::vec3 &v0, const glm::vec3 &v1,
                    const glm::vec3 &v2, const glm::vec3 &color ):
        Primitive(),
        v0{ v0 },
        v1{ v1 },
        v2{ v2 },
        color{ color }
{}

bool Triangle::intersect( const Ray &ray,
                          IntersectionRecord &intersection_record ) const
{
    if (THOMAS) {

        glm::vec3 AB = v1 - v0;
        glm::vec3 AC = v2 - v0;
        float u, v;
        glm::vec3 p_point;
        glm::vec3 q_point;

        p_point = glm::cross(ray.direction_, AC);

        float determinant = glm::dot(AB, p_point);

        if (determinant > -0.000001f && determinant < 0.000001f) {
            return false;
        }

        float det_invert = 1.0 / determinant;

        glm::vec3 t_vector = ray.origin_ - v0;

        u = glm::dot(t_vector, p_point) * det_invert;

        if (u < 0.0 || u > 1.0)
            return false;


        q_point = glm::cross(t_vector, AB);

        v = glm::dot(ray.direction_, q_point) * det_invert;

        if (v < 0.0 || u + v > 1.0)
            return false;

        intersection_record.t_ = glm::dot(AC, q_point) * det_invert;
        //std::cout << intersection_record.t_ << std::endl;
        intersection_record.position_ = ray.origin_ + intersection_record.t_ * ray.direction_;
        intersection_record.normal_ = glm::cross(AB, AC);
        intersection_record.color_ = color;
        return true;
    }
    else {
        float a, b, c, d, e, f, g, h, i, j, k, l;
        a = v0[0] - v1[0];
        b = v0[1] - v1[1];
        c = v0[2] - v1[2];
        d = v0[0] - v2[0];
        e = v0[1] - v2[1];
        f = v0[2] - v2[2];
        g = ray.direction_[0];
        h = ray.direction_[1];
        i = ray.direction_[2];
        j = v0[0] - ray.origin_[0];
        k = v0[1] - ray.origin_[1];
        l = v0[2] - ray.origin_[2];

        float akjb, jcal, blkc, eihf, gfdi, dheg;
        akjb = (v0[0] - v1[0]) * (v0[1] - ray.origin_[1]) - (v0[0] - ray.origin_[0]) * (v0[1] - v1[1]);
        jcal = (v0[0] - ray.origin_[0]) * (v0[2] - v1[2]) - (v0[0] - v1[0]) * (v0[2] - ray.origin_[2]);
        blkc = (v0[1] - v1[1]) * (v0[2] - ray.origin_[2]) - (v0[1] - ray.origin_[1]) * (v0[2] - v1[2]);
        eihf = (v0[1] - v2[1]) * (ray.direction_[2]) - (ray.direction_[1]) * (v0[2] - v2[2]);
        gfdi = (ray.direction_[0]) * (v0[2] - v2[2]) - (v0[0] - v2[0]) * (ray.direction_[2]);
        dheg = (v0[0] - v2[0]) * (ray.direction_[1]) - (v0[1] - v2[1]) * (ray.direction_[0]);

        float M = a*eihf + b*gfdi + c*dheg;
        float t = -((f*akjb + e*jcal + d*blkc)/M);
        float v = (i*akjb + h*jcal + g*blkc)/M;
        float u = (j*eihf + k*gfdi + l*dheg)/M;

        if (t < 0)
            return false;

        if (v < 0 or v > 1)
            return false;

        if (u < 0 or u > 1 - v)
            return false;

        intersection_record.t_ = t;
        intersection_record.position_ = ray.origin_ + intersection_record.t_ * ray.direction_;
        intersection_record.normal_ = glm::cross( v1 - v0, v2 - v0);
        return true;
    }
}


