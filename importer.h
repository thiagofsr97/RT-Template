#ifndef RT_TEMPLATE_IMPORTER_H
#define RT_TEMPLATE_IMPORTER_H

#include <iostream>
#include <vector>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "primitive.h"
#include "triangle.h"


class Importer
{
public:

    Importer( const std::string );

    ~Importer( void );

    void load( std::vector< Primitive::PrimitiveUniquePtr > *primitives_ );

    std::string filename;
    Assimp::Importer importer;
    int R;
    int G;
    int B;

};


#endif //RT_TEMPLATE_IMPORTER_H
