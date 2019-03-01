#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "camera.h"
#include "ray.h"


class PerspectiveCamera : public Camera
{
public:

    PerspectiveCamera( void );

    PerspectiveCamera( const glm::ivec2 &resolution,
                       const glm::vec3 &position,
                       const glm::vec3 &up_vector,
                       const glm::vec3 &look_at,
                       float aspect,
                       float fov_degrees );

    Ray getWorldSpaceRay( const glm::vec2 &pixel_coord ) const;

//void printInfo( void ) const;

    float aspect_;

    float fov_degrees_;

private:

    static const float kDegreesToRadians_;
};


#endif //RT_TEMPLATE_PERSPECTIVE_CAMERA_H
