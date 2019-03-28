# Perspective Camera Implementation

The project is about the implementation of the perspective camera (pinhole), complementing the 
Ray Tracer project forked at https://github.com/capagot/RT-Template

- Students that worked on this project:
     - [Name] - [Registration Number]
    - Thiago Filipe Soares da Rocha - 11502567 
    - Fernando Máximo Alves - 11500204

# Algorithm Used 

The implementation of the perspective camera was made based on the content presented on the website https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.
The resulting code of the camera implementation is the given below:

```cpp

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
    float y_value = ((height/2) -  (height*(pixel_coord[1]/static_cast< float >(resolution_[1])))) * tan(fov_degrees_ * 0.5f * PerspectiveCamera::kDegreesToRadians_);
    
    glm::vec3 ray_local_dir{ x_value , y_value , -1.0f};

    return Ray{ position_, glm::normalize( onb_.getBasisMatrix() * ray_local_dir ) };
}

```

# Model Samples 

Below are some of model samples that were loaded and rendered using the Ray Tracer with Perspective Camera.

- **All the models are in the format .blend (Blender), using triangular faces and standard coordinate system.**

- **All the images presents a resolution of 512x512.**

## Model 1 - Monkeys Tree

- Time to load and render model: 52.6757 seconds.
- Number of primitives used: 10637.
- Image description: 11 monkey heads of the same size located in different positions so as to form a design similar to a tree, presenting in its constitution random colors.

![Alt text](models/model2/output_image.jpg?raw=true "Title")

## Model 2 - The four monkeys

- Time to load and render model: 25.7383 seconds.
- Number of primitives used: 3868.
- Image description: 4 monkey heads of the same size located in different positions, presenting in their constitution random colors, demonstrating well the concept of camera perspective.

![Alt text](models/model3/output_image.jpg?raw=true "Title")

## Model 3 - The 10 Colored Men

- Time to load and render model: 105.276 seconds.
- Number of primitives used: 19680.
- Image description: set of several models of a human being positioned in several different positions, all being the same size.

![Alt text](models/model4/output_image.jpg?raw=true "Title")



