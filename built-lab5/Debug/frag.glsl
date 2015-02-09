varying vec3 vCol;
uniform int shapeID;

void main()
{
    gl_FragColor = vec4(vCol.r, vCol.g, vCol.b, 0.2);
    
    if (shapeID == 0) {  // Make the half-sided snowglobe
        gl_FragColor.w = 0.2;
    }
    else if (shapeID == 1) { // Make the bodies of the dudes
        gl_FragColor = vec4(1, 1, 1, 1);
    }
//    else { // Make the red, red eyeballs
//        gl_FragColor = vec4(1, 0, 0, 1);
//    }
}
