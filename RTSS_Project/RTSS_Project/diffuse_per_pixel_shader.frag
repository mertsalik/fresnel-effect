#version 120

// vertex shaderindan gelen veriler
varying vec3 normal,pos;

// fragment shader main metodu
void main(void)
{

	vec3 Normal = normalize(normal);
	vec3 Light = normalize(vec3(gl_LightSource[0].position.xyz - pos));
	float Cos = dot(Normal,Light) / dot(length(Normal),length(Light));
	
	vec4 FirstColor = vec4(0.86,0.86,0.86,0.5);
	vec4 SecondColor = vec4(1.0,0.0,0.0,1);
	gl_FragColor = mix(FirstColor, SecondColor,Cos);


}