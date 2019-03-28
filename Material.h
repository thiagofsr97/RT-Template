//
// Created by thiagofsr on 27/03/19.
//

#ifndef RT_TEMPLATE_MATERIAL_H
#define RT_TEMPLATE_MATERIAL_H


#include <glm/vec3.hpp>
constexpr auto PI = 3.14159265359f;
class Material {

public:
    Material();
    Material(glm::vec3 color, float emission_intensity);
    ~Material();
    glm::vec3 BRDF()const;
    glm::vec3 getColor() const;
    float getEmission() const;

//    void setEmission(float emission_intensity);
//    void setColor(glm::vec3 color);


private:
    glm::vec3 color_material;
    float intensity_emission;



};


#endif //RT_TEMPLATE_MATERIAL_H
