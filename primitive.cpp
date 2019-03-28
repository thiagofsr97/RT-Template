#include "primitive.h"

Primitive::Primitive( void )
{}

Primitive::~Primitive( void )
{}

Primitive::Primitive(const Material *material) {
    this->material = material;
}

const Material *Primitive::getMaterial() {
    return this->material;
}



