uniform sampler2D texture;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    color.rgb += 0.03;
 
    //color.rgb += brightness;
    //color.rgb = (color.rgb - 0.5) * contrast + 0.5;
    //color.rgb = pow(color.rgb, vec3(1.0 / gamma));

    gl_FragColor = color;
}