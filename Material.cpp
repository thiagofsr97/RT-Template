//
// Created by thiagofsr on 27/03/19.
//

#include "Material.h"


Material::Material() {
    this->color_material = glm::vec3{0,0,0};
    this->intensity_emission = 0;
}

Material::Material(glm::vec3 color, float emission_intensity) {
    this->color_material = color;
    this->intensity_emission = emission_intensity;
}

Material::~Material() {

}

glm::vec3 Material::BRDF() const {
    return this->color_material/PI;
}

glm::vec3 Material::getColor() const {
    return this->color_material;
}

float Material::getEmission() const{
    return this->intensity_emission;
}

//void Material::setEmission(float emission_intensity) {
//    this->intensity_emission = emission_intensity;
//
//}
//
//void Material::setColor(glm::vec3 color) {
//    this->color_material = color;
//}

