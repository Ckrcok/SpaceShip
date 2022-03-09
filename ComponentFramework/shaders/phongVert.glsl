#version 450
#extension GL_ARB_separate_shader_objects : enable

// these are attributes  
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;

//layout(location = 2) in vec2 inUVCoord;

layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 modelMatrix;
layout(location  = 3 ) uniform vec3 lightPos;

layout(location = 0 ) out vec3 vertNormal;
layout(location = 1) out vec3 lightDir;
layout(location = 2) out vec3 eyeDir; 


void main() {
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    vertNormal = normalize(normalMatrix * vNormal); /// Rotate the normal to the correct orientation 
    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex);
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;
    lightDir = normalize(vec3(lightPos) - vertPos);
    gl_Position = (projectionMatrix * viewMatrix) * (modelMatrix * vVertex);
}