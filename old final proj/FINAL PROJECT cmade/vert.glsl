attribute vec4 aPosition;
attribute vec3 aNormal;
uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
varying vec3 vCol;

void main()
{
	gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * aPosition;
	vCol = 0.5*(aNormal + 1.0);
}
