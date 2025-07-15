#version 330 core

in vec2 fTextureCoordinates;

uniform sampler2D texture_diffuse1;

out vec4 oFragmentColour;

void main() {
    oFragmentColour = texture(texture_diffuse1, fTextureCoordinates);
}
