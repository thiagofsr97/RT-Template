#include "perspective_camera.h"

const float PerspectiveCamera::kDegreesToRadians_ = static_cast< float >( M_PI ) / 180.0f;

PerspectiveCamera::PerspectiveCamera( void )
{ }

PerspectiveCamera::PerspectiveCamera( 
                                      const glm::ivec2 &resolution,
                                      const glm::vec3 &position,
                                      const glm::vec3 &up_vector,
                                      const glm::vec3 &look_at,
                                      const float min_x,
                                      const float max_x,
                                      const float min_y,
                                      const float max_y,
                                      float aspect,
                                      float fov_degrees ) :
        Camera::Camera{ resolution,
                        position,
                        up_vector,
                        look_at },
        min_x_{ min_x },
        max_x_{ max_x },
        min_y_{ min_y },
        max_y_{ max_y },
        aspect_{ aspect },
        fov_degrees_{ fov_degrees }
{ }

Ray PerspectiveCamera::getWorldSpaceRay( const glm::vec2 &pixel_coord ) const
{
    float witdh  = max_x_ - min_x_;
    float height = max_y_ - min_y_;

    float x_value = ((witdh * pixel_coord[0]/static_cast< float >(resolution_[0])) - (witdh/2) ) * aspect_ * tan(fov_degrees_ * 0.5f * PerspectiveCamera::kDegreesToRadians_);
//    float x_value = ((8 * pixel_coord[0]/static_cast< float >(resolution_[0])) - 4 ) * aspect_ * tan(fov_degrees_ * 0.5f * PerspectiveCamera::kDegreesToRadians_);
    float y_value = ((witdh/2) -  (witdh*(pixel_coord[1]/static_cast< float >(resolution_[1])))) * tan(fov_degrees_ * 0.5f * PerspectiveCamera::kDegreesToRadians_);
//    float y_value = (4 -  (8*(pixel_coord[1]/static_cast< float >(resolution_[1])))) * tan(fov_degrees_ * 0.5f * PerspectiveCamera::kDegreesToRadians_);

    glm::vec3 ray_local_dir{ x_value , y_value , -1.0f};

    return Ray{ position_, glm::normalize( onb_.getBasisMatrix() * ray_local_dir ) };
}