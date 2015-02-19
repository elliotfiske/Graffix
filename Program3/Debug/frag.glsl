varying vec3 vCol;
varying vec3 gouradColor;

void main()
{
    vec3 normVCol = normalize(vCol);
	gl_FragColor = vec4(gouradColor.r, gouradColor.g, gouradColor.b, 1.0);
}
