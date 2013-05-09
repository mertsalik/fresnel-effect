#version 120

// vertex shaderindan gelen veriler
varying float Cos;

// fragment shader main metodu
void main(void)
{
	vec4 FirstColor = vec4(0.86,0.86,0.86,0.5);
	vec4 SecondColor = vec4(1.0,0.0,0.0,1);
	gl_FragColor = mix(FirstColor, SecondColor, Cos);
}