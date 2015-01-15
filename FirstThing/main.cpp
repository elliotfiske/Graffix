#include <iostream>
#include <stdio.h>
#include <cassert>
#include "tiny_obj_loader.h"
#include "Camera.h"
#include <cstdlib>
#include <sstream>

int main( int argc, const char* argv[] )
{
    if (argc != 5) {
        printf("Specify an input <.obj> file, resolution, and rendering style with command line args like: %s cube.obj 100 200 1   (note that '1' indicates depth render, '2' indicates x-ramp shading)\n", *argv);
        return 0;
    }
    
    std::string inputfile = argv[1];
    
    
    bool invalidNumbers = false;
    std::istringstream ss2(argv[2]);
    int width;
    if (!(ss2 >> width)) {
        std::cerr << "Invalid width " << argv[2] << " Please just input an int!\n";
        invalidNumbers = true;
    }
    
    std::istringstream ss3(argv[3]);
    int height;
    if (!(ss3 >> height)) {
        std::cerr << "Invalid height " << argv[3] << " Please just input an int!\n";
        invalidNumbers = true;
    }
    
    std::istringstream ss4(argv[4]);
    int renderStyle;
    if (!(ss4 >> renderStyle) || (renderStyle != 1 && renderStyle != 2)) {
        std::cerr << "Invalid render style " << argv[4] << " Please just input either 1 or 2!\n";
        invalidNumbers = true;
    }
    
    if (invalidNumbers) {
        return 0;
    }
    
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
    
    bool renderingDepth = renderStyle == 1;
    Image img = camera.makeImage(width, height, renderingDepth);
    img.WriteTga((char *)"awesome.tga", true);
    
    return 0;
}
