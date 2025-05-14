// shadow.frag
uniform sampler2D texture;
uniform vec2 resolution;
uniform float time;
varying vec2 worldPos;
uniform vec2 camPosition;

void main()
{
    vec2 uv = gl_FragCoord.xy/resolution;
    vec2 u_cam = camPosition/resolution;
    u_cam = 1.0 - u_cam;
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    float circle = 1.0 - length(uv-u_cam)*10.0;
    gl_FragColor = (0.1, 0.1, 0.1, circle*(1.0-pixel.y)*1.35);
}