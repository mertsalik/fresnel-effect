#version 120

// sabit degiskenler
uniform mat4 MVP,ModelView;

// diziden alinacak degiskenler
attribute vec4 Position;
attribute vec3 Normal;

// fragment shadera aktarilacak veri
varying float Cos;

// vertex shader main metodu
void main()
{
	// camera space position
	vec3 vVertex = vec3(ModelView * Position);
	// camera space normal
	vec3 normal = mat3(ModelView)*Normal;

	vec3 lightDir = vec3(gl_LightSource[0].position.xyz - vVertex);
	vec3 eyeVec = -vVertex;

	vec3 Light = normalize(lightDir);

	Cos = dot(normal,Light) / dot(length(normal),length(Light));

	gl_Position = MVP * Position;
}