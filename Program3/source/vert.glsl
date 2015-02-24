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

uniform int colorNornmals; // TRUE to visually see the values of normals as a color
varying vec4 interpNormal;
varying vec4 interpVertex;

varying vec3 gouradColor;

varying vec4 phongWorldCoord;

void main() {
	gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * aPosition;
    
    vec4 vertexWorldPos = uViewMatrix * uModelMatrix * aPosition;
    vec4 worldNormal = uViewMatrix * uModelMatrix * vec4(normalize(aNormal), 0);
    interpNormal = worldNormal;
    interpVertex = vertexWorldPos;
    
    if (uShadeModel == 0) {
        
        // Gourad shading
        vec3 lightVec = normalize((uLightPos - vertexWorldPos.xyz));
        vec3 lightColor = vec3(1, 1, 1);
        
        vec3 halfAngle = normalize(lightVec - vertexWorldPos.xyz);
        
        gouradColor = lightColor *     dot(worldNormal.xyz, lightVec)           * UdColor  +   // Diffuse
                      lightColor * pow(dot(worldNormal.xyz, halfAngle), Ushine) * UsColor  +   // Specular
                                                                                  UaColor;     // Ambient
    }
    else {
        phongWorldCoord = vertexWorldPos;
        
    }
}
