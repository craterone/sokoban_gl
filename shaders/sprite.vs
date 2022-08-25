
#version 330 core
layout (location = 0) in vec4 position;

out vec2 TexCoords;
vec4 temp;

uniform mat4 model;
uniform mat4 projection;


void main(){
  TexCoords = position.zw;
  temp = projection * model * vec4(position.xy, 0.0, 1.0);
  temp.y = -temp.y;
  gl_Position = temp;
}