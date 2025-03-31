// vertex.frag

varying vec2 worldPos;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	worldPos = gl_ModelViewMatrix * gl_Vertex;
	gl_FrontColor = gl_Color;
}