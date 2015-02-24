varying vec3 vCol;
varying vec3 gouradColor;
varying vec4 interpNormal;
varying vec4 interpVertex;
varying vec4 phongWorldCoord;

uniform vec3 uLightPos;
uniform vec3 UaColor;
uniform vec3 UdColor;
uniform vec3 UsColor;

uniform float Ushine;
uniform int uShadeModel;
uniform int isLight;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;

uniform int colorNormals;

void main()
{
    if (isLight == 1) {
        gl_FragColor = vec4(1, 1, 1, 1);
    }
    else {
        vec4 normalInterpNormal = normalize(interpNormal);
        
        if (uShadeModel == 0) {
            gl_FragColor = vec4(gouradColor.r, gouradColor.g, gouradColor.b, 1.0);
        }
        else {
            vec3 lightColor = vec3(1, 1, 1);
            vec3 lightVec = normalize((uLightPos - phongWorldCoord.xyz));
            
            vec3 halfAngle = normalize(lightVec - interpVertex.xyz);
            
            gl_FragColor = vec4(lightColor *     dot(interpNormal.xyz, lightVec)           * UdColor  +   // Diffuse
                                lightColor * pow(dot(interpNormal.xyz, halfAngle), Ushine) * UsColor  +   // Specular
                                                                                             UaColor      // Ambient
                                , 1.0);
        }
        
        
        if (colorNormals == 1) {
            gl_FragColor = vec4(interpNormal.r, interpNormal.g, interpNormal.b, 1.0);
        }
    }
}
