#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    //outColor = texture(texSampler, fragTexCoord)* fragColor;
    outColor = vec4(fragColor.rgb * texture(texSampler, fragTexCoord).rgb, fragColor.a);
}