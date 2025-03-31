// assets/water.frag

uniform sampler2D texture;
uniform float time;

void main()
{
    vec2 uv1 = gl_TexCoord[0].xy;
    uv1.y -= time*0.05;
    uv1.y = mod(uv1.y, 1.0);    // in range 0.0 - 1.0
    vec4 noise1 = texture2D(texture, uv1);
    
    vec2 uv2 = gl_TexCoord[0].xy;
    uv2.x -= time*0.05;
    uv2.x = mod(uv2.x, 1.0);    // in range 0.0 - 1.0
    vec4 noise2 = texture2D(texture, uv2);
    

    float waves = noise1.z + noise2.x;
    waves = smoothstep(0.75, 2, waves);

    vec4 color = vec4(0.125, 0.125, 0.6, 0.75); 

    gl_FragColor = vec4(color.x + waves, color.y + waves, color.z + waves, color.w);
}