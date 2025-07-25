#version 330 core

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec3 iNormals;
layout(location = 2) in vec2 iTextureCoordinates;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 fTextureCoordinates;

out vec3 fNormal;
out vec3 fFragmentPosition;

void main() {
    fTextureCoordinates = iTextureCoordinates;

    fNormal = mat3(transpose(inverse(uModel))) * iNormals;
    fFragmentPosition = vec3(uModel * vec4(iPosition, 1.0));

    gl_Position = uProjection * uView * uModel * vec4(iPosition, 1.0);
}
