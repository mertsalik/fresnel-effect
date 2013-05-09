#version 120

// sabit degiskenler
uniform mat4 MVP;

// diziden alinacak degiskenler
attribute vec4 Position;

// fragment shader'a aktarilacak veriler
varying float pos;

// vertex shader main metodu
void main()
{	
    //pos = Position.y;
    pos = (MVP * Position).y;
    // gl_Position ekranda noktanin nerede olacagini belirtir.
	gl_Position = MVP * Position;
}