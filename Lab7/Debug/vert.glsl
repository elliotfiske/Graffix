attribute vec4 aPos;
attribute vec3 aNor;
uniform mat4 P;
uniform mat4 MV;

uniform int bakedShadows;
uniform int gurrad;

varying vec4 lightVec;
varying vec4 interpNormal;

varying float gurradLightDotProd;

void main()
{
    gl_Position = P * MV * aPos;
    
    vec4 lightPos = vec4(2, 2, 2, 1);
    lightVec = normalize(lightPos - MV * aPos);
    
    interpNormal = normalize(vec4(aNor, 0));
    if (bakedShadows == 0) {
        interpNormal = MV * interpNormal;
    }
    
    gurradLightDotProd = max(dot(lightVec.xyz, normalize(interpNormal.xyz)), 0.0);
}
