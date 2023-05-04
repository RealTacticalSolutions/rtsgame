#version 450


layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(set = 0, binding = 2) buffer StorageBufferObject {
    mat4 model[30];
    vec4 color[30];
} sbo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;

const vec3 DIRECTION_TO_LIGHT = normalize(vec3(0.0, 0.0, 1.0));
const float AMBIENCE = 0.03f;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * sbo.model[gl_InstanceIndex] * vec4(inPosition, 1.0);

    vec3 normalWorldSpace = normalize(mat3(sbo.model[gl_InstanceIndex]) * inNormal);

    float lightIntensity = max(dot(normalWorldSpace, DIRECTION_TO_LIGHT), 0);

    fragColor = sbo.color[gl_InstanceIndex] * lightIntensity;
    fragTexCoord = inTexCoord;
}