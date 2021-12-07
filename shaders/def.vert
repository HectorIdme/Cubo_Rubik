#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 model_text;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    vec2 TexCoord_ = vec2(aTexCoord.x, aTexCoord.y);
    vec4 rotCoord = model_text * vec4(aTexCoord.xy, 0.0, 1.0);
    TexCoord = vec2(rotCoord.s, rotCoord.t);
}

 