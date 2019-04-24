#ifndef PATHTRACER_H_
#define PATHTRACER_H_

#include <vector>;
#include <glm/glm.hpp>
#include <sstream>
#include "camera.h";
#include "scene.h";
#include "buffer.h";
#include <random>;
#include <chrono>;
#include <functional>

constexpr auto PI_ = 3.14159265359f;
class PathTracer{

public:

    PathTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer, int number_of_samples, int depth_level_limit );

    void integrate( void );

private:
    
    //methods
    void generateSamples();
    glm::vec3 LightResultedRecursive(const Ray& ray, int current_depth);

    //properties

    int number_of_samples_;

	int depth_level_limit_;

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

};



#endif
