#version 330

out vec4 FragColor;
in vec4 Color;

void main(){
    FragColor = Color;

    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}