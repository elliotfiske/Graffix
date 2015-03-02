attribute vec4 aPosition;
attribute vec3 aNormal;
uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

varying vec4 interpNormal;
varying vec4 interpVertex;

void main()
{
    gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * aPosition;
    
    interpNormal = /*uViewMatrix **/ uModelMatrix * vec4(normalize(aNormal), 0);
    
    interpVertex = uViewMatrix * uModelMatrix * aPosition;
}
