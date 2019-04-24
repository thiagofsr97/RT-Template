#include "main.h"
#include "time.h"
#include "pathtracer.h"

int main( void )
{
    unsigned int x_resolution = 512;
    unsigned int y_resolution = 512;
    clock_t begin = std::clock();
    time_t inicio, fim;
    inicio = time(NULL);
    float camera_size = 1.25f;

    OrthographicCamera camera{ -camera_size,
                                camera_size,
                               -camera_size,
                                camera_size,
                                glm::ivec2{ x_resolution, y_resolution }, 
                                glm::vec3{ 0.0f, 0.0f,  1.0f },     // position
                                glm::vec3{ 0.0f, 0.0f,  0.0f },     // up
                                glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at

    PerspectiveCamera camera1{ 
                              glm::ivec2{ x_resolution, y_resolution },
                              glm::vec3{ 0.0f, 0.0f,  4.0f },     // position
                              glm::vec3{ 0.0f, -1.0f,  0.0f },     // up
                              glm::vec3{ 0.0f, 0.0f, -1.0f },
                              -camera_size,
                                camera_size,
                               -camera_size,
                                camera_size,
                              (static_cast<float>(x_resolution)/y_resolution),
                              45.0f};
    Scene scene{};
    
    scene.load();

    Buffer rendering_buffer{ x_resolution, y_resolution };
    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };

    // Set up the renderer.
    RayTracer rt( camera1,
                  scene,
                  background_color,
                  rendering_buffer );

    PathTracer pt(camera1,scene, background_color, rendering_buffer, 1000, 5);
    //rt.integrate();
    pt.integrate();
//
 //   rt.integrate(); // Renders the final image.
	fim = time(NULL);
	fprintf(stdout, "O tempo de execucao em segundos é %f\n", difftime(fim, inicio));
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "The elapsed to load and render the model was " << elapsed_secs << " seconds." << std::endl; 
    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "output_image.ppm" );

    return EXIT_SUCCESS;
}

