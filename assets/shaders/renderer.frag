uniform sampler2D render_texture_0;
//uniform sampler2D render_texture_1;
//uniform sampler2D render_texture_2;

uniform float brightness;
uniform float contrast;
uniform float gamma;

void main()
{
    vec4 c0 = texture2D(render_texture_0, gl_TexCoord[0].xy);
    //vec4 c1 = texture2D(render_texture_1, gl_TexCoord[0].xy);
    //vec4 c2 = texture2D(render_texture_2, gl_TexCoord[0].xy);
    
    //vec4 color = c2 * 0.7 + c1 * 0.2 + c0 * 0.1;
    vec4 color = c0;

    color.rgb += brightness;
    color.rgb = (color.rgb - 0.5) * contrast + 0.5;
    color.rgb = pow(color.rgb, vec3(1.0 / gamma));

    gl_FragColor = color;
}