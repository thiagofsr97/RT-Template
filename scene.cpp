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
                tmp_intersection_record.material = primitives_[primitive_id]->getMaterial();
                intersection_record = tmp_intersection_record;

                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}

void Scene::load( void ) 
{

    Importer importer( "start" );
    importer.load( &primitives_ );

    //1
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.5f,  -0.8f }, 0.2f, glm::vec3{200.0f/255,200.0f/255,200.0f/255}, new Material(glm::vec3{200.0f/255,200.0f/255,200.0f/255}, 100.0f) } ) );
//    primitives_.push_back(Primitive::PrimitiveUniquePtr(
//            new Triangle{ glm::vec3{ -0.84770f, -0.67362f, -0.55652f },
//                          glm::vec3{ -0.43468f, -0.67362f, -1.83889f },
//                          glm::vec3{ -0.84770f, 0.67362f, -0.55652f },
//                          glm::vec3{10.0f/255,100.0f/255,10.0f/255},
//                          new Material(glm::vec3{0.0f/255,100.0f/255,0.0f/255}, 0.0f) } ) );
//
//    primitives_.push_back( Primitive::PrimitiveUniquePtr(
//            new Triangle{ glm::vec3{ -0.84770f, 0.67362f, -0.55652f },
//                          glm::vec3{ -0.43468f, 0.67362f, -1.83889f },
//                          glm::vec3{ -0.43468f, -0.67362f, -1.83889f },
//                          glm::vec3{10.0f/255,100.0f/255,10.0f/255},
//                          new Material(glm::vec3{0.0f/255,100.0f/255,0.0f/255}, 0.0f) } ) );
//
//    //2
//    primitives_.push_back( Primitive::PrimitiveUniquePtr(
//            new Triangle{ glm::vec3{ -0.84770f, -0.67362f, -0.55652f },
//                          glm::vec3{ -0.43468f, -0.67362f, -1.83889f },
//                          glm::vec3{ 0.43468f, -0.67362f, -0.14350f },
//                          glm::vec3{10.0f/255,100.0f/255,10.0f/255},
//                          new Material(glm::vec3{0.0f/255,100.0f/255,0.0f/255}, 0.0f) } ) );
//
//    primitives_.push_back( Primitive::PrimitiveUniquePtr(
//            new Triangle{ glm::vec3{ -0.43468f, -0.67362f, -1.83889f },
//                          glm::vec3{ 0.43468f, -0.67362f, -0.14350f },
//                          glm::vec3{ 0.84770f, -0.67362f, -1.42587f },
//                          glm::vec3{10.0f/255,100.0f/255,10.0f/255},
//                          new Material(glm::vec3{0.0f/255,100.0f/255,0.0f/255}, 0.0f) } ) );
//
//    //3
//    primitives_.push_back( Primitive::PrimitiveUniquePtr(
//            new Triangle{ glm::vec3{ 0.43468f, 0.67362f, -0.14350f },
//                          glm::vec3{ 0.84770f, -0.67362f, -1.42587f },
//                          glm::vec3{ 0.43468f, -0.67362f, -0.14350f },
//                          glm::vec3{10.0f/255,100.0f/255,10.0f/255},
//                          new Material(glm::vec3{0.0f/255,100.0f/255,0.0f/255}, 0.0f) } ) );
//
//    primitives_.push_back( Primitive::PrimitiveUniquePtr(
//            new Triangle{ glm::vec3{ 0.84770f, -0.67362f, -1.42587f },
//                          glm::vec3{ 0.43468f, 0.67362f, -0.14350f },
//                          glm::vec3{ 0.84770f, 0.67362f, -1.42587f },
//                          glm::vec3{10.0f/255,100.0f/255,10.0f/255},
//                          new Material(glm::vec3{0.0f/255,100.0f/255,0.0f/255}, 0.0f) } ) );
//
//    //4
//    primitives_.push_back( Primitive::PrimitiveUniquePtr(
//            new Triangle{ glm::vec3{ 0.43468f, 0.67362f, -0.14350f },
//                          glm::vec3{ 0.84770f, 0.67362f, -1.42587f },
//                          glm::vec3{ -0.84770f, 0.67362f, -0.55652f },
//                          glm::vec3{10.0f/255,100.0f/255,10.0f/255},
//                          new Material(glm::vec3{0.0f/255,100.0f/255,0.0f/255}, 0.0f) } ) );
//
//    primitives_.push_back( Primitive::PrimitiveUniquePtr(
//            new Triangle{ glm::vec3{ -0.43468f, 0.67362f, -1.83889f },
//                          glm::vec3{ -0.84770f, 0.67362f, -0.55652f },
//                          glm::vec3{ 0.84770f, 0.67362f, -1.42587f },
//                          glm::vec3{10.0f/255,100.0f/255,10.0f/255},
//                          new Material(glm::vec3{0.0f/255,100.0f/255,0.0f/255}, 0.0f) } ) );
//
//    //5
//    primitives_.push_back( Primitive::PrimitiveUniquePtr(
//            new Triangle{ glm::vec3{ -0.43468f, 0.67362f, -1.83889f },
//                          glm::vec3{ 0.84770f, 0.67362f, -1.42587f },
//                          glm::vec3{ 0.84770f, -0.67362f, -1.42587f },
//                          glm::vec3{10.0f/255,100.0f/255,10.0f/255},
//                          new Material(glm::vec3{0.0f/255,100.0f/255,0.0f/255}, 0.0f) } ) );
//
//    primitives_.push_back( Primitive::PrimitiveUniquePtr(
//            new Triangle{ glm::vec3{ -0.43468f, 0.67362f, -1.83889f },
//                          glm::vec3{ 0.84770f, -0.67362f, -1.42587f },
//                          glm::vec3{ -0.43468f, -0.67362f, -1.83889f },
//                          glm::vec3{10.0f/255,100.0f/255,10.0f/255},
//                          new Material(glm::vec3{0.0f/255,100.0f/255,0.0f/255}, 0.0f) } ) );

//    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 2.0f,  -1.0f }, 0.5f, glm::vec3{100.0f/255,200.0f/255,50.0f/255}, new Material(glm::vec3{0.0f/255,200.0f/255,200.0f/255}, 0.0f) } ) );
//    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 4.0f,  0.0f }, 0.5f, glm::vec3{200.0f/255,200.0f/255,200.0f/255}, new Material(glm::vec3{200.0f/255,200.0f/255,200.0f/255}, 25.5f) } ) );
//    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  2.0f, 0.0f,  0.0f }, 0.5f, glm::vec3{200.0f/255,200.0f/255,200.0f/255}, new Material(glm::vec3{200.0f/255,200.0f/255,200.0f/255}, 0.0f) } ) );
//    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.0f, -1.0f }, 0.2f } ) );
//    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f,-0.5f, -2.0f }, 0.2f } ) );
//    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.5f, -3.0f }, 0.2f } ) );
}

