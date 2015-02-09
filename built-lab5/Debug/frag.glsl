varying vec3 vCol;
uniform int shapeID;

void main()
{
    vec3 viewVec = vec3(0, 0, -1);
    vec3 normalVec = normalize(vCol);
    
    if (shapeID == 0 || shapeID == 1) {  // Normal interpolation for color
        gl_FragColor = vec4(vCol.r, vCol.g, vCol.b, 1.0);
    }
    
    if (shapeID == 0) { // Snowglobe discard
        float dotProd = dot(viewVec, normalVec);
        if (dotProd < -0.75) {
            discard;
        }
    }
    
    if (shapeID == 2) { // Make the red, red eyeball
        gl_FragColor = vec4(1, 0, 0, 1);
    }
}
