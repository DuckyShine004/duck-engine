#version 330 core

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec2 iNormals;
layout(location = 2) in vec2 iTextureCoordinates;

uniform mat4 uProjection;

out vec2 fTextureCoordinates;

void main() {
    fTextureCoordinates = iTextureCoordinates;

    gl_Position = uProjection * vec4(iPosition, 1.0);
}
