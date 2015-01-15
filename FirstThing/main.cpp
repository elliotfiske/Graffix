#include <iostream>
#include <stdio.h>
#include <cassert>
#include "tiny_obj_loader.h"
#include "Camera.h"

int main( int argc, const char* argv[] )
{
    if (argc != 2) {
        printf("Specify an input <.obj> file as a command line argument like: %s cube.obj\n", *argv);
        return 0;
    }
    
    std::string inputfile = argv[1];
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    
    std::string err = tinyobj::LoadObj(shapes, materials, inputfile.c_str());
    
    if (!err.empty()) {
        std::cerr << err << std::endl;
        exit(1);
    }
    
    std::cout << "# of shapes    : " << shapes.size() << std::endl;
    for (size_t i = 0; i < shapes.size(); i++) {
//        printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
        assert((shapes[i].mesh.indices.size() % 3) == 0);
        for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
//            printf("  triangle[%ld] = %d, %d, %d\n", f, shapes[i].mesh.indices[3*f+0], shapes[i].mesh.indices[3*f+1], shapes[i].mesh.indices[3*f+2]);
        }
        
        printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
        assert((shapes[i].mesh.positions.size() % 3) == 0);
        for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
//            printf("  vertex[%ld] = (%f, %f, %f)\n", v,
//                   shapes[i].mesh.positions[3*v+0],
//                   shapes[i].mesh.positions[3*v+1],
//                   shapes[i].mesh.positions[3*v+2]);
        }
    }
    
    // write the targa file to disk
    // true to scale to max color, false to clamp to 1.0
    Point cameraPos(0, 0, 0);
    Camera camera(cameraPos);
    camera.setShapes(shapes);
    
    Image img = camera.makeImage(600, 480);
    img.WriteTga((char *)"awesome.tga", true);
    
    return 0;
}
