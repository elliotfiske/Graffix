attribute vec4 aPosition;
attribute vec3 aNormal;
uniform mat4 uProjMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;

uniform vec3 uLightPos;
uniform vec3 UaColor;
uniform vec3 UdColor;
uniform vec3 UsColor;

uniform float Ushine;
uniform int uShadeModel;

varying vec3 vCol;

void main()
{
	gl_Position = uProjMatrix * uModelMatrix * uViewMatrix * aPosition;
	vCol = 0.5*(aNormal + 1.0);
}
