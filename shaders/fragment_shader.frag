#version 430 core

uniform sampler2D tex_input;
uniform sampler2D tex_output;

out vec4 frag_color;

void main()
{
    ivec2 pos = ivec2(gl_FragCoord.xy) / ivec2(2, 2);
    float texel = texelFetch(tex_input, pos, 0).r;

    if(texel == 0.0f)
    {
        frag_color = vec4(0.f);
    }
    else
    {
        frag_color = vec4(1.f, 1.f, 0.f, 1.f);
    }
}