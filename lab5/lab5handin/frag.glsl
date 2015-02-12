varying vec3 vCol;
varying vec3 norms;
uniform int shapeID;
uniform vec3 viewVec;

void main()
{
    vec3 normalVec = normalize(norms);

    if (shapeID == 0) { // Snowglobe discard
        float dotProd = dot(viewVec, normalVec);
        float currColor = 1.0 - dotProd;
        float alpha = max(dotProd, 0.8);
        
        gl_FragColor = vec4(currColor, currColor, currColor, alpha);
        
        if (dotProd < -0.3) {
            discard;
        }
    }
    
    if (shapeID == 1) {  // Normal interpolation for color
        gl_FragColor = vec4(vCol.r, vCol.g, vCol.b, 1.0);
    }
    
    if (shapeID == 2 || shapeID == 5) { // Make the red, red floaty hat things
        gl_FragColor = vec4(1, 0, 0, 0.4);
    }
}
