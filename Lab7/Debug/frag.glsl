varying vec4 lightVec;
varying vec4 interpNormal;
varying float gurradLightDotProd;

uniform int gurrad;

uniform int bakedShadows;

void main()
{
    if (gurrad == 0) {
        float lightDotProd = dot(normalize(lightVec), normalize(interpNormal));
        gl_FragColor = lightDotProd * vec4(1, 0.3, 0, 1);
    }
    else {
        gl_FragColor = gurradLightDotProd * vec4(1, 0.3, 0, 1);
    }
}
