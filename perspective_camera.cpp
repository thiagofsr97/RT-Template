#include "perspective_camera.h"

const float PerspectiveCamera::kDegreesToRadians_ = static_cast< float >( M_PI ) / 180.0f;

PerspectiveCamera::PerspectiveCamera( void )
{ }

PerspectiveCamera::PerspectiveCamera( const glm::ivec2 &resolution,
                                      const glm::vec3 &position,
                                      const glm::vec3 &up_vector,
                                      const glm::vec3 &look_at,
                                      float aspect,
                                      float fov_degrees ) :
        Camera::Camera{ resolution,
                        position,
                        up_vector,
                        look_at },
        aspect_{ aspect },
        fov_degrees_{ fov_degrees }
{ }

Ray PerspectiveCamera::getWorldSpaceRay( const glm::vec2 &sample_coord ) const
{
    glm::vec3 ray_local_dir{  sample_coord.x * aspect_ * tan ( fov_degrees_ * 0.5f * PerspectiveCamera::kDegreesToRadians_ ),
                              -sample_coord.y * tan ( fov_degrees_ * 0.5f * PerspectiveCamera::kDegreesToRadians_ ),
                              -1.0f };

    return Ray{ position_, glm::normalize( onb_.getBasisMatrix() * ray_local_dir ) };
}