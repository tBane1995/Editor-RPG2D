// river.frag
uniform sampler2D texture;
uniform vec2 resolution;
uniform float time;
varying vec2 worldPos;
uniform vec2 direction;

float random(float x) {
 
    return fract(sin(x) * 10000.);
          
}

float noise(vec2 p) {

    return random(p.x + p.y * 10000.);
            
}

vec2 sw(vec2 p) { return vec2(floor(p.x), floor(p.y)); }
vec2 se(vec2 p) { return vec2(ceil(p.x), floor(p.y)); }
vec2 nw(vec2 p) { return vec2(floor(p.x), ceil(p.y)); }
vec2 ne(vec2 p) { return vec2(ceil(p.x), ceil(p.y)); }

float smoothNoise(vec2 p) {

    vec2 interp = smoothstep(0., 1., fract(p));
    float s = mix(noise(sw(p)), noise(se(p)), interp.x);
    float n = mix(noise(nw(p)), noise(ne(p)), interp.x);
    return mix(s, n, interp.y);
        
}

float fractalNoise(vec2 p) {

    float x = 0.;
    x += smoothNoise(p      );
    x += smoothNoise(p * 2. ) / 2.;
    x += smoothNoise(p * 4. ) / 4.;
    x += smoothNoise(p * 8. ) / 8.;
    x += smoothNoise(p * 16.) / 16.;

    x /= 1. + 1./2. + 1./4. + 1./8. + 1./16.;
    return x;
            
}

float movingNoise(vec2 p) {
 
    float x = fractalNoise(p + time);
    float y = fractalNoise(p - time);
    return fractalNoise(p + vec2(x, y));   
    
}

float nestedNoise(vec2 p) {
    vec2 moveOfWater = -direction * time;
    moveOfWater.y = -moveOfWater.y;
    float x = movingNoise(p);
    float y = movingNoise(p + 100.);
    return movingNoise(p + vec2(x, y) + moveOfWater);
    
}

void main()
{
    vec4 texcolor = texture2D(texture, gl_TexCoord[0].xy);
    if(texcolor.x == 127./255. && texcolor.y == 127./255. && texcolor.z == 127./255. && texcolor.w == 1.0) {
        vec2 coords = worldPos.xy/resolution;
        float pixelationFactor = 0.00390625;
        vec2 pixelCoord = floor(coords / pixelationFactor) * pixelationFactor;
        float n = nestedNoise(pixelCoord * 25.60);
        vec3 color = mix(vec3(.4, .6, 1.), vec3(.05, .1, 1.), n);
        vec3 darkcolor = color * 0.7;
        gl_FragColor = vec4(darkcolor, 1.);
    }else{
        gl_FragColor = texcolor;
    }
}