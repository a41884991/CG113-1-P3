#version 460 core
layout(location = 0) in vec3 aPos;

out vec3 Normal;
out vec3 FragPos;

struct Wave {
    vec2 direction;
    float amplitude;
    float waveLength;
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform Wave wave;

uniform float time;

#define PI 3.14159


vec3 GenWave(Wave wave, vec3 position, inout vec3 tangent, inout vec3 binormal)
{
    float waveNumber = 2*PI/wave.waveLength;
    float c = sqrt(9.8/waveNumber);
    float f = waveNumber*(dot(wave.direction,position.xz)-c*time);
    vec2 d = normalize(wave.direction);
    float a = wave.amplitude;

    tangent += vec3(
		-d.x * d.x * (a * sin(f)),
		d.x * (a * cos(f)),
		-d.x * d.y * (a * sin(f))
	);
	binormal += vec3(
		-d.x * d.y * (a * sin(f)),
		d.y * (a * cos(f)),
		-d.y * d.y * (a * sin(f))
	);

	return vec3(d.x * (a * cos(f)), a * sin(f), d.y * (a * cos(f)));
}

void main()
{
    vec3 tangent = vec3(1.0,0.0,0.0);
    vec3 binormal = vec3(0.0,0.0,1.0);
    vec3 pos = aPos;
    pos+=GenWave(wave, aPos, tangent, binormal);
    Normal = normalize(cross(binormal, tangent));

    FragPos = vec3(model*vec4(pos,1.0));
    gl_Position = projection*view*vec4(FragPos,1.0);
}