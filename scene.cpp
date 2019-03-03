#include "scene.h"


Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    // Loops over the list of primitives, testing the intersection of each primitive against the given ray 
    for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                intersection_record = tmp_intersection_record;
                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}

void Scene::load( void ) 
{

    
//     Assimp::Importer importer;
//     const aiScene *scene_ =  importer.ReadFile( "model3.blend", 
//         aiProcess_CalcTangentSpace       | 
//         aiProcess_Triangulate            |
//         aiProcess_JoinIdenticalVertices  |
//         aiProcess_SortByPType);

    
//     if( !scene_)
//   {
//     std::cout << "Error loading model..." << std::endl;
//     return;
//   }

  
//   for( int i = 0; i < scene_->mNumMeshes; i++){
//       auto vertices = scene_->mMeshes[i]->mVertices;
//       for(int j = 0; j < scene_->mMeshes[i]->mNumFaces; j++ ){
//           auto faces = scene_->mMeshes[i]->mFaces[j];
          
//           primitives_.push_back( Primitive::PrimitiveUniquePtr(
//                new Triangle{ glm::vec3{vertices[faces.mIndices[0]][0], vertices[faces.mIndices[0]][1], vertices[faces.mIndices[0]][2]}, 
//                glm::vec3{vertices[faces.mIndices[1]][0], vertices[faces.mIndices[1]][1], vertices[faces.mIndices[2]][2]},
//                glm::vec3{vertices[faces.mIndices[2]][0], vertices[faces.mIndices[2]][1], vertices[faces.mIndices[2]][2]} } ) );


//         //   std::cout << vertices[faces.mIndices[0]][0] << std::endl;
//         //   std::cout << scene_->mMeshes[i]->mFaces[j].mIndices[1] << std::endl;
//         //   std::cout << scene_->mMeshes[i]->mFaces[j].mIndices[2] << std::endl;

//       }
//   }
    
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f,  0.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.0f, -1.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f,-0.5f, -2.0f }, 0.2f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.5f, -3.0f }, 0.2f } ) );
}

