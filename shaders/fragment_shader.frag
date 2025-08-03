#version 430 core

uniform sampler2D tex;

out vec4 frag_color;

void main()
{
    ivec2 pos = ivec2(gl_FragCoord.xy);
    ivec2 aux = pos / 2;
    vec2 normalised = (vec2(aux) + 0.5) / vec2(400.0, 400.0);

    float val = texture(tex, normalised).r;

    vec3 rgb = vec3(0.f, 0.f, 0.f);

    if(val == 0.f)
        rgb = vec3(0.0f, 0.0f, 0.0f);
    else
        rgb = vec3(1.0f, 1.0f, 0.0f);

    frag_color = vec4(rgb, 1.f);
}