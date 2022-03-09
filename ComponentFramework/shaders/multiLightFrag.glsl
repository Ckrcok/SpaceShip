#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 lightDir[2];
layout(location = 3) in vec3 eyeDir; 
layout(location = 4) in vec2 texCoord; 

uniform sampler2D myTexture;

layout(location = 0) out vec4 fragColor;

void main() {
	vec4 kd[2] = {vec4(0.0, 0.0, 0.5, 0.0),vec4(0.7, 0.0, 0.0, 0.0)};
    vec4 ks[2] = {0.7 * kd[0] , 0.7 * kd[1]};
	


	vec4 textureColor = texture(myTexture, texCoord);
	vec4 ka = (0.01 * textureColor);
	float diff[2];
	vec3 reflection[2];
	float spec[2];
	fragColor = ka;

	for(int i=0; i<2 ; i++){
	diff[i] = max(dot(vertNormal, lightDir[i]), 0.0);
	/// Reflection is based incedent which means a vector from the light source
	/// not the direction to the light source
	reflection[i] = normalize(reflect(-lightDir[i], vertNormal));
	spec[i] = max(dot(eyeDir, reflection[i]), 0.0);
	spec[i] = pow(spec[i],14.0);
	fragColor +=  (textureColor * diff[i] * kd[i]) + (spec[i] * ks[i]);
	}

}