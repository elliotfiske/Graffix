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

varying vec3 gouradColor;

void main() {
    vec3 normNorm = normalize(aNormal);
    
    
	gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * aPosition;
	vCol = 0.5*(normNorm + 1.0);
    
    // Gourad shading
    vec4 vertexWorldPos = uViewMatrix * uModelMatrix * aPosition;
    vec3 lightVec = normalize((uLightPos - vertexWorldPos.xyz));
    vec3 lightColor = vec3(1, 1, 1);
    
    vec3 halfAngle = normalize(lightVec + vertexWorldPos.xyz);
    
    gouradColor = lightColor *     dot(aNormal, lightVec)           * UdColor  +   // Diffuse
                  lightColor * pow(dot(aNormal, halfAngle), Ushine) * UsColor  +   // Specular
                                                                      UaColor;     // Ambient
}
