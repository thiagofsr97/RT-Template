#include "importer.h"

Importer::Importer(const std::string filename):
          filename{ filename }
{}

Importer::~Importer( void )
{}

void Importer::load( std::vector < Primitive::PrimitiveUniquePtr > *primitives_ )
{
    const aiScene *scene_ =  importer.ReadFile( "models/model9.blend",
            aiProcess_CalcTangentSpace       |
            aiProcess_Triangulate            |
            aiProcess_JoinIdenticalVertices  |
            aiProcess_SortByPType);

    if( !scene_)
    {
        std::cout << "Error loading model..." << std::endl;
        return;
    }

    for( int i = 0; i < scene_->mNumMeshes; i++ )
    {
        auto vertices = scene_->mMeshes[i]->mVertices;
        for( int j = 0; j < scene_->mMeshes[i]->mNumFaces; j++ )
        {
            auto faces = scene_->mMeshes[i]->mFaces[j];
            R = rand() % 255;
            G = rand() % 255;
            B = rand() % 255;
            primitives_->push_back( Primitive::PrimitiveUniquePtr(
                    new Triangle{ glm::vec3{vertices[faces.mIndices[0]][0], vertices[faces.mIndices[0]][1], vertices[faces.mIndices[0]][2]},
                                  glm::vec3{vertices[faces.mIndices[1]][0], vertices[faces.mIndices[1]][1], vertices[faces.mIndices[1]][2]},
                                  glm::vec3{vertices[faces.mIndices[2]][0], vertices[faces.mIndices[2]][1], vertices[faces.mIndices[2]][2]},
                                  glm::vec3{ R / 255.0, G / 255.0, B / 255.0 } } ) );

//            std::cout << vertices[faces.mIndices[0]][0] << " " << vertices[faces.mIndices[0]][1] << " " <<  vertices[faces.mIndices[0]][2] << std::endl;
//            std::cout << vertices[faces.mIndices[1]][0] << " " << vertices[faces.mIndices[1]][1] << " " <<  vertices[faces.mIndices[1]][2] << std::endl;
//            std::cout << vertices[faces.mIndices[2]][0] << " " << vertices[faces.mIndices[2]][1] << " " <<  vertices[faces.mIndices[2]][2] << std::endl;

//            std::cout << vertices[faces.mIndices[0]][0] << std::endl;
//            std::cout << scene_->mMeshes[i]->mFaces[j].mIndices[1] << std::endl;
//            std::cout << scene_->mMeshes[i]->mFaces[j].mIndices[2] << std::endl;

        }
    }
}

