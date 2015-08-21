uniform sampler2D uTexUnit;

varying vec2 vTexCoord;
varying vec3 vColor;

void main(void) {
  vec4 BaseColor = vec4(vColor.x, vColor.y, vColor.z, 1);
  vec4 texColor1 = texture2D(uTexUnit, vTexCoord);

    if (texColor1.g > 0.1 && texColor1.b < 0.8 && texColor1.r < 0.8) {
        texColor1 = vec4(0, 0, 0, 1);
    }
    
    texColor1 = vec4(0, 0, 0, 1);
    
  gl_FragColor = texColor1;
}

