//shader version
#version 150 core

uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

uniform mat4 modelViewProjectionMatrix;

in vec3 pos;
in vec3 nor;
in vec2 tex;

out VertexData
{
	vec3 position;
	vec3 normal;
	vec2 texcoord;
} VertexOut;

out vec3 fragEye;
out vec3 lightLocEye;
out vec3 fragNormal;


const vec4 lightLocation = vec4(0.0, 100.0, 0.0, 1.0);

void main()
{
	fragEye = (modelViewMatrix * vec4(pos, 1.0)).xyz;
	fragNormal = (normalMatrix * vec4(nor, 1.0)).xyz;
	lightLocEye = (viewMatrix * lightLocation).xyz;

	gl_Position = modelViewProjectionMatrix*vec4(pos.xyz,1);

	VertexOut.position = vec3(modelViewMatrix*vec4(pos.xyz,1));
	VertexOut.normal = vec3(normalMatrix*vec4(nor.xyz,1));	
	VertexOut.texcoord = vec2(tex.xy);
}
