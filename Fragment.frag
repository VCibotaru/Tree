//shader version
#version 150 core

uniform int useTexture;

uniform sampler2D textureSampler;

in VertexData
{
	vec3 position;
	vec3 normal;
	vec2 texcoord;
} VertexIn;


in vec3 fragEye;
in vec3 lightLocEye;
in vec3 fragNormal;

out vec4 fragColor;

const vec4 ka = vec4(0.05, 0.05, 0.05, 1);
const vec4 ks = vec4(0.4, 0.4, 0.4, 0.4);
const float ke = 20;
		
void main()
{
	vec3 light = normalize(lightLocEye - fragEye);
	vec3 normal = normalize(fragNormal);
	vec3 eye = normalize(fragEye);
	vec3 reflection = normalize(reflect(light, normal));
	float diffuseIntensity = clamp(max(dot(normal, light), -dot(normal, light)), 0.0, 1.0);
	float specularIntensity = pow(clamp(max(dot(reflection, eye), 0.0), 0.0, 1.0), ke);

	vec4 kd;
	if (useTexture>0)
		kd = vec4(texture(textureSampler,VertexIn.texcoord.xy).rgb,length(VertexIn.normal)*length(VertexIn.position));
	else
	{
		kd = vec4(0.5,0.2,0.1,1);
	}
	fragColor = ka + kd * diffuseIntensity + ks * specularIntensity;
}
