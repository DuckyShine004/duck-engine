#version 330 core

uniform mat4 uView;
uniform mat4 uProjection;

const vec3 gridPlane[6] = vec3[6](
        vec3(1.0, 1.0, 0.0),
        vec3(-1.0, -1.0, 0.0),
        vec3(-1.0, 1.0, 0.0),
        vec3(-1.0, -1.0, 0.0),
        vec3(1.0, 1.0, 0.0),
        vec3(1.0, -1.0, 0.0)
    );

void main() {
    gl_Position = uProjection * uView * vec4(gridPlane[gl_VertexID].xyz, 1.0);
}
