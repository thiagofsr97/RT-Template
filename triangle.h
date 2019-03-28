#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Triangle : public Primitive {
public:
    Triangle( void );

    Triangle( const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &color, const Material* material );
    Triangle( const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &color);

    bool intersect( const Ray &ray, IntersectionRecord &intersection_record) const; 
                    

    glm::vec3 v0 = { 0.0f, 0.0f, 0.0f };
    glm::vec3 v1 = { 0.0f, 0.0f, 0.0f };
    glm::vec3 v2 = { 0.0f, 0.0f, 0.0f };
    glm::vec3 color = { 0.0f, 0.0f, 0.0f };
};

#endif /* TRIANGLE_H_ */
