attribute vec4 aPosition;
attribute vec3 aNormal;
uniform mat4 uProjMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;

varying vec4 interpNormal;
varying vec4 interpVertex;

varying vec4 phongWorldCoord;

uniform int isPlane;

void main() {
	gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * aPosition;
    
    interpNormal = /*uViewMatrix **/ uModelMatrix * vec4(aNormal, 0);
    
    interpVertex = uViewMatrix * uModelMatrix * aPosition;
}
