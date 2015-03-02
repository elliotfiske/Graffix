varying vec4 interpNormal;
varying vec4 interpVertex;

uniform vec3 UdColor;
uniform vec3 UsColor;
uniform vec3 UaColor;
uniform float Ushine;

uniform int shade;

void main()
{
    vec4 normInterpNormal = normalize(interpNormal);
    
    vec3 lightColor = vec3(1, 1, 1);
    vec3 lightVec =  normalize(vec3(0,-1,-0.5));
    
    
    vec3 halfAngle = normalize(lightVec + interpVertex.xyz);
    float NdotH = -dot(normInterpNormal.xyz, halfAngle);
    
    if (shade == 1 && NdotH > 0.0) {
        NdotH = 0.0;
    }
    
    gl_FragColor = vec4(lightColor *     dot(normInterpNormal.xyz, lightVec) * UdColor  +   // Diffuse
                        lightColor *     pow(NdotH, Ushine)                  * UsColor  +   // Specular
                                                                               UaColor      // Ambient
                        , 1.0);
}
