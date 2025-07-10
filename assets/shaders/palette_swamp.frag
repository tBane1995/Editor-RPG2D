// palette_swamp.frag
uniform sampler2D texture;
uniform vec2 resolution;
uniform float time;
varying vec2 worldPos;
uniform vec2 camPosition;

vec4 permute(vec4 x) {
  return mod((34.0 * x + 1.0) * x, 289.0);
}
vec3 permute(vec3 x) {
  return mod((34.0 * x + 1.0) * x, 289.0);
}

vec2 cellular2x2x2(vec3 P) {
	#define K 0.142857142857
	#define Ko 0.428571428571
	#define K2 0.020408163265306
	#define Kz 0.166666666667
	#define Kzo 0.416666666667
	#define jitter 0.8
	vec3 Pi = mod(floor(P), 289.0);
 	vec3 Pf = fract(P);
	vec4 Pfx = Pf.x + vec4(0.0, -1.0, 0.0, -1.0);
	vec4 Pfy = Pf.y + vec4(0.0, 0.0, -1.0, -1.0);
	vec4 p = permute(Pi.x + vec4(0.0, 1.0, 0.0, 1.0));
	p = permute(p + Pi.y + vec4(0.0, 0.0, 1.0, 1.0));
	vec4 p1 = permute(p + Pi.z);
	vec4 p2 = permute(p + Pi.z + vec4(1.0));
	vec4 ox1 = fract(p1*K) - Ko;
	vec4 oy1 = mod(floor(p1*K), 7.0)*K - Ko;
	vec4 oz1 = floor(p1*K2)*Kz - Kzo;
	vec4 ox2 = fract(p2*K) - Ko;
	vec4 oy2 = mod(floor(p2*K), 7.0)*K - Ko;
	vec4 oz2 = floor(p2*K2)*Kz - Kzo;
	vec4 dx1 = Pfx + jitter*ox1;
	vec4 dy1 = Pfy + jitter*oy1;
	vec4 dz1 = Pf.z + jitter*oz1;
	vec4 dx2 = Pfx + jitter*ox2;
	vec4 dy2 = Pfy + jitter*oy2;
	vec4 dz2 = Pf.z - 1.0 + jitter*oz2;
	vec4 d1 = dx1 * dx1 + dy1 * dy1 + dz1 * dz1;
	vec4 d2 = dx2 * dx2 + dy2 * dy2 + dz2 * dz2;

#if 0

	d1 = min(d1, d2);
	d1.xy = min(d1.xy, d1.wz);
	d1.x = min(d1.x, d1.y);
	return sqrt(d1.xx);
#else

	vec4 d = min(d1,d2);
	d2 = max(d1,d2);
	d.xy = (d.x < d.y) ? d.xy : d.yx;
	d.xz = (d.x < d.z) ? d.xz : d.zx;
	d.xw = (d.x < d.w) ? d.xw : d.wx;
	d.yzw = min(d.yzw, d2.yzw);
	d.y = min(d.y, d.z);
	d.y = min(d.y, d.w);
	d.y = min(d.y, d2.x);
	return sqrt(d.xy);
#endif
}

void main() {
    vec4 texcolor = texture2D(texture, gl_TexCoord[0].xy);
    if(texcolor.x == 127./255. && texcolor.y == 127./255. && texcolor.z == 127./255. && texcolor.w == 1.0) {

        float pixelSize = 2.0;
        vec2 pixelatedWorldPos = floor(worldPos / pixelSize) * pixelSize;

        vec2 st = (2.0 * (pixelatedWorldPos - camPosition) - resolution.xy) / resolution.y;

        st.y = st.y * 2.0;
        st *= 10.0;

        vec2 F = cellular2x2x2(vec3(st, time / 4.0));

        float n = smoothstep(0.4, 0.5, F.x);
        vec4 final_color;

        if(n < 0.6)
            final_color = vec4(0.15, 0.35, 0.15, 1.0);
        else
            final_color = vec4(0.15*n, 0.25*n, 0.15*n, 1.0);

        gl_FragColor = final_color;
    }else {
        gl_FragColor = texcolor;
    }
}