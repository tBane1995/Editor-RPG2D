// assets/jagged_circle.frag

uniform sampler2D texture;
uniform float time;

void main() {
	// Odczytaj szum z tekstury
    vec3 noise = texture2D(texture, gl_TexCoord[0].xy).rgb;

    // Wyznacz współrzędną okręgu opartą o czas
    float distanceFromCenter = length(gl_TexCoord[0].xy - vec2(0.5, 0.5));
    float radius = mod(time * 0.2, 1.0); // Powiększający się promień

    // Zastosuj szum na promień, aby uzyskać zniekształcenia
    radius += noise.r * 0.1;

    // Wyznacz opadanie kolorów na krawędziach okręgu
    float circle = smoothstep(radius + 0.05, radius, distanceFromCenter);

    // Wyznacz finalny kolor (zanikanie i mieszanie kolorów)
    gl_FragColor = vec4(circle * noise, 1.0) * vec4(1.0, 1.0, 1.0, 1.0 - distanceFromCenter);
}