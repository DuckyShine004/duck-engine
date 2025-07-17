#version 410 core

layout(location = 1) out vec3 fNear;
layout(location = 2) out vec3 fFar;
layout(location = 3) out mat4 fFragmentView;
layout(location = 7) out mat4 fFragmentProjection;

uniform mat4 uView;
uniform mat4 uProjection;

const vec3 gridPlane[6] = vec3[](
        vec3(1.0, 1.0, 0.0),
        vec3(-1.0, -1.0, 0.0),
        vec3(-1.0, 1.0, 0.0),
        vec3(-1.0, -1.0, 0.0),
        vec3(1.0, 1.0, 0.0),
        vec3(1.0, -1.0, 0.0)
    );

vec3 unprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInverse = inverse(view);
    mat4 projectionInverse = inverse(projection);

    vec4 unprojectedPoint = viewInverse * projectionInverse * vec4(x, y, z, 1.0);

    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main() {
    vec3 gridPoint = gridPlane[gl_VertexID].xyz;

    fNear = unprojectPoint(gridPoint.x, gridPoint.y, 0.0, uView, uProjection).xyz;
    fFar = unprojectPoint(gridPoint.x, gridPoint.y, 1.0, uView, uProjection).xyz;

    fFragmentView = uView;
    fFragmentProjection = uProjection;

    gl_Position = vec4(gridPoint, 1.0);
}
