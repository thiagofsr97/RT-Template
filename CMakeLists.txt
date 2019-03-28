cmake_minimum_required(VERSION 3.13)
project(RT_Template)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RT_Template
        buffer.cpp
        buffer.h
        camera.cpp
        camera.h
        importer.cpp
        importer.h
        intersection_record.h
        main.cpp
        main.h
        onb.cpp
        onb.h
        orthographic_camera.cpp
        orthographic_camera.h
        pathtracer.cpp
        pathtracer.h
        perspective_camera.cpp
        perspective_camera.h
        primitive.cpp
        primitive.h
        ray.cpp
        ray.h
        raytracer.cpp
        raytracer.h
        scene.cpp
        scene.h
        sphere.cpp
        sphere.h
        triangle.cpp
        triangle.h Material.cpp Material.h)
