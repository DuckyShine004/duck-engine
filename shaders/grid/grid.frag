#version 410 core

layout(location = 1) in vec3 fNear;
layout(location = 2) in vec3 fFar;
layout(location = 3) in mat4 fFragmentView;
layout(location = 7) in mat4 fFragmentProjection;

layout(location = 0) out vec4 oFragmentColour;

vec4 grid(vec3 fragmentPosition, float scale) {
    vec2 coordinates = fragmentPosition.xz * scale;
    vec2 derivative = fwidth(coordinates);
    vec2 grid = abs(fract(coordinates - 0.5) - 0.5) / derivative;

    float line = min(grid.x, grid.y);

    float minimumX = min(derivative.x, 1);
    float minimumZ = min(derivative.y, 1);

    vec4 colour = vec4(0.2, 0.2, 0.2, 1.0 - min(line, 1.0));

    if (fragmentPosition.x > -1.0 * minimumX && fragmentPosition.x < 1.0 * minimumX) {
        colour.z = 1.0;
    }

    if (fragmentPosition.z > -1.0 * minimumZ && fragmentPosition.z < 1.0 * minimumZ) {
        colour.x = 1.0;
    }

    return colour;
}

float computeDepth(vec3 fragmentPosition) {
    vec4 clipSpacePosition = fFragmentProjection * fFragmentView * vec4(fragmentPosition.xyz, 1.0);

    return (clipSpacePosition.z / clipSpacePosition.w);
}

float computeLinearDepth(vec3 fragmentPosition) {
    float near = 0.01;
    float far = 100;

    vec4 clipSpacePosition = fFragmentProjection * fFragmentView * vec4(fragmentPosition.xyz, 1.0);

    float clipSpaceDepth = (clipSpacePosition.z / clipSpacePosition.w) * 2.0 - 1.0;

    float linearDepth = (2.0 * near * far) / (far + near - clipSpaceDepth * (far - near));

    return linearDepth / far;
}

void main() {
    float t = -fNear.y / (fFar.y - fNear.y);

    vec3 fragmentPosition = fNear + t * (fFar - fNear);

    gl_FragDepth = computeDepth(fragmentPosition);

    float linearDepth = computeLinearDepth(fragmentPosition);
    float fade = max(0, (0.5 - linearDepth));

    vec4 gridColour = grid(fragmentPosition, 1) + grid(fragmentPosition, 0.1);

    oFragmentColour = gridColour * float(t > 0);

    oFragmentColour.a *= fade;
}
