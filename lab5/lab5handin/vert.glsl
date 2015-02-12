attribute vec4 aPos;
attribute vec3 aNor;
attribute float aPoints; // A radius for each point
uniform float uTime;
uniform mat4 P;
uniform mat4 MV;
varying vec3 vCol;
varying vec3 norms;

uniform int shapeID;

void main()
{
    if (shapeID != 5) {
        gl_Position = P * MV * aPos;
        vCol = 0.5*(aNor + 1.0);
        norms = aNor;
    }
    else {
        gl_Position = vec4(sin(uTime) * aPoints, cos(uTime) * aPoints + 0.4, 0.1, 1);
        gl_PointSize = 20.0;
    }
}
