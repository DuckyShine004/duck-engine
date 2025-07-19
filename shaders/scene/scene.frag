#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};

// Expect Phong lighting
struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float innerCutoff;
    float outerCutoff;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float innerCutoff;
    float outerCutoff;
};

in vec2 fTextureCoordinates;

in vec3 fNormal;
in vec3 fFragmentPosition;

uniform vec3 uViewPosition;

uniform sampler2D texture_diffuse1;

uniform Material material;

uniform Light light;

out vec4 oFragmentColour;

vec3 calculateAmbient() {
    vec3 ambient = light.ambient * material.ambient;

    return ambient;
}

vec3 calculateDiffuse(vec3 normal, vec3 lightDirection) {
    float diffuseIntensity = max(dot(normal, lightDirection), 0.0);

    return diffuseIntensity * light.diffuse * material.diffuse;
}

vec3 calculateSpecular(vec3 normal, vec3 lightDirection) {
    vec3 viewDirection = normalize(uViewPosition - fFragmentPosition);

    vec3 reflectionDirection = reflect(-lightDirection, normal);

    float specularIntensity = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);

    return specularIntensity * light.specular * material.specular;
}

float calculateAttenuation() {
    float distance = length(light.position - fFragmentPosition);

    float constant = light.constant;
    float linear = light.linear * distance;
    float quadratic = light.quadratic * (distance * distance);

    return 1.0 / (constant + linear + quadratic);
}

float calculateIntensity(vec3 lightDirection) {
    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon = light.innerCutoff - light.outerCutoff;

    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

    return intensity;
}

vec4 calculatePhongLight() {
    vec3 normal = normalize(fNormal);
    vec3 lightDirection = normalize(light.position - fFragmentPosition);

    vec3 ambient = calculateAmbient();
    vec3 diffuse = calculateDiffuse(normal, lightDirection);
    vec3 specular = calculateSpecular(normal, lightDirection);

    vec4 phong = vec4(ambient + diffuse + specular, 1.0);

    return phong;
}

vec4 calculateDirectionalLight() {
    vec3 normal = normalize(fNormal);
    vec3 lightDirection = normalize(-light.position); // light.direction (we don't have it right now, implement later)

    vec3 ambient = calculateAmbient();
    vec3 diffuse = calculateDiffuse(normal, lightDirection);
    vec3 specular = calculateSpecular(normal, lightDirection);

    vec4 directionalLighting = vec4(ambient + diffuse + specular, 1.0);

    return directionalLighting;
}

vec4 calculateSpotLight() {
    vec3 normal = normalize(fNormal);
    vec3 lightDirection = normalize(light.position - fFragmentPosition);

    vec3 ambient = calculateAmbient();
    vec3 diffuse = calculateDiffuse(normal, lightDirection);
    vec3 specular = calculateSpecular(normal, lightDirection);

    float attenuation = calculateAttenuation();
    float intensity = calculateIntensity(lightDirection);

    ambient *= intensity * attenuation;
    diffuse *= intensity * attenuation;
    specular *= intensity * attenuation;

    vec4 spotLight = vec4(ambient + diffuse + specular, 1.0);

    return spotLight;
}

void main() {
    vec4 textureColour = texture(texture_diffuse1, fTextureCoordinates);

    vec4 phongLight = calculatePhongLight();

    oFragmentColour = textureColour * phongLight;
}
