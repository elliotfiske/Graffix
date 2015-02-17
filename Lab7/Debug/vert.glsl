attribute vec4 aPos;
attribute vec3 aNor;
uniform mat4 P;
uniform mat4 MV;
varying float lightDotProd;

void main()
{
    vec4 lightPos = vec4(0, -5, 0, 1);
    vec4 lightDiff = normalize(gl_Position - lightPos);
    
    lightDotProd = dot(vec3(0, 1, 0), normalize(aNor));
    
	gl_Position = P * MV * aPos;
}
