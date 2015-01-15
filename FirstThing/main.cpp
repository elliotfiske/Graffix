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
    
    // write the targa file to disk
    // true to scale to max color, false to clamp to 1.0
    Camera camera = *new Camera();
    camera.setShapes(shapes);
    
    Image img = camera.makeImage(1200, 800);
    img.WriteTga((char *)"awesome.tga", true);
    
    return 0;
}
