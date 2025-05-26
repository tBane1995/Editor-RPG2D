// assets/circle.frag

uniform sampler2D texture;
uniform float time;

vec4 circle(vec2 uv, vec2 pos, float rad, vec3 color) {
	
	float d = length(pos - uv) - rad*time;
	if(d > 0.0)
		d = 1.0;
	return vec4(color.x, color.y, color.z, 1.0 - d*d);
}

void main() {
	vec2 uv = gl_TexCoord[0].xy;
	vec2 center = vec2(0.5, 0.5);
	float radius = 0.025;
	
	vec4 background = vec4(0.0, 0.0, 0.0, 1.0);
	vec3 color = vec3(0.5, 0.5, 0.5);
	vec4 circle1 = circle(uv, center, radius, color); 
	gl_FragColor = mix(background, circle1, circle1.a);
}