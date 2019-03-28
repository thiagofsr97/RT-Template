#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Sphere : public Primitive
{
public:

    Sphere( void );

    Sphere( const glm::vec3 &center,
            float radius,const glm::vec3 &color, const Material* material );
    Sphere( const glm::vec3 &center,
            float radius, const glm::vec3 &color);

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    glm::vec3 center_ = { 0.0f, 0.0f, 0.0f };

    float radius_= 1.0f;
    glm::vec3 color{0.0f,0.0f, 0.0f};

private:

    static const float kIntersectionTestEpsilon_;
};

#endif /* SPHERE_H_ */

