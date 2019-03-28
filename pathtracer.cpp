#include "pathtracer.h";

PathTracer::PathTracer(Camera &camera, const Scene &scene, const glm::vec3 background_color, Buffer &buffer,
                       int number_of_samples, int depth_level_limit):
                       camera_(camera),
                       scene_(scene),
                       background_color_(background_color),
                       buffer_(buffer),
                       number_of_samples_(number_of_samples),
                       depth_level_limit_(depth_level_limit){}


void PathTracer::integrate() {
    IntersectionRecord intersectionRecord;

    for (std::size_t y = 0; y < buffer_.v_resolution_; y++) {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw(6)
                        << std::setprecision(2)
                        << 100.0 * y / (buffer_.v_resolution_ - 1)
                        << "%";

        std::clog << progress_stream.str();
        for (std::size_t x = 0; x < buffer_.h_resolution_; x++) {
            generateSamples();
            for (long unsigned int samp = 0; samp < samples_.size(); samp++) {
                intersectionRecord.t_ = std::numeric_limits< double >::max();
                Ray ray{ camera_.getWorldSpaceRay(glm::vec2{ x + 0.5f + samples_[samp].x, y + 0.5f + samples_[samp].y }) };
                buffer_.buffer_data_[x][y] += LightResultedRecursive(ray, 0);

            }
            buffer_.buffer_data_[x][y] /= samples_.size();
        }
    }

    std::clog << std::endl;
}
void PathTracer::generateSamples() {

    // this samples generated are related to the rays that are going to be casted through a given pixel
    // uniform distribution is used
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto real_rand = std::bind(std::uniform_real_distribution<double>(0, 1), std::mt19937(seed));
    this->samples_.clear();
    this->samples_.resize(this->number_of_samples_);
    for(int i = 0; i < this->number_of_samples_; ++i){
        double x_rand = real_rand() - 0.5f;
        double y_rand = real_rand() - 0.5f;
        this->samples_[i] = glm::vec2{x_rand, y_rand};
    }
}

glm::vec3 PathTracer::LightResultedRecursive(const Ray &ray, int current_depth) {
    IntersectionRecord intersectionRecord;
    glm::vec3 output_light{0,0,0};
    float two_pi = 2.0f * PI;

    if(current_depth >= this->depth_level_limit_){
        return output_light;
    }

    intersectionRecord.t_ = std::numeric_limits<float>::max();

    if(!this->scene_.intersect(ray, intersectionRecord)){
        if(current_depth == 0) {
            //it means that at first there was no intersection
            // with any object, so background will be returned
            return this->background_color_;
        }
        return output_light;
    }

    //----------------------generating a new ray from intersection point-------------------------

    ONB onb;
    onb.setFromV(intersectionRecord.normal_);
    auto local_coord_system = onb.getBasisMatrix();
    auto local_to_universe_system = glm::transpose(local_coord_system);
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto real_rand = std::bind(std::uniform_real_distribution<double>(0, 1), std::mt19937(seed));
    double r1 = real_rand();
    double r2 = real_rand();
    double theta = glm::acos(1 - r1);
    double phi = 2 * PI * r2;

    //converting from spherical to xyz coordinates
    /*
     * x = r * sin(theta) * cos(phi)
     * y = r * sin*theta * sin(phi)
     * z = r * cos(theta)
     *
     * where r = 1 (direction vector)
     */
    glm::vec3 direction = glm::normalize(glm::vec3(glm::sin(theta)*glm::cos(phi), glm::sin(theta)*glm::sin(phi), glm::cos(theta)));
    direction = onb.getBasisMatrix() * direction;
    //converting back to world space system
    direction = local_to_universe_system * direction;
    Ray output_ray = Ray(intersectionRecord.position_ + (intersectionRecord.normal_*0.001f), direction);

    //----------------------generating a new ray from intersection point-------------------------

    // taking abs from cos cause it might be negative, not desirable in the calculation of the output light
    float cos = fabs(glm::dot(intersectionRecord.normal_, output_ray.direction_));
//    if(cos < 0.0){
//        std::cout << cos << std::endl;
//        cos = fabs(cos);
//        output_ray.direction_ = -output_ray.direction_;
//    }
    //missing emitted light
    output_light = intersectionRecord.material->getEmission() + (two_pi * intersectionRecord.material->BRDF() * LightResultedRecursive(output_ray, ++current_depth) * cos);

    return output_light;

}
