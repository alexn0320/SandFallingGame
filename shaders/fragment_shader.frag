#version 430 core

uniform sampler2D tex_input;
uniform sampler2D tex_output;

out vec4 frag_color;

void main()
{
    ivec2 pos = ivec2(gl_FragCoord.xy);
    float texel = texelFetch(tex_input, pos, 0).r;
    float out_texel;

    if(texel == 1.f)
    {
        out_texel = 0.f;
    }
    else if(texel == 0.f)
    {
        ivec2 down_pos = ivec2(gl_FragCoord.xy) - ivec2(0, 1);
        float down_texel = texelFetch(tex_input, down_pos, 0).r;

        if(down_texel == 1.f)
        {
            out_texel = 1.f;
        }
    }

    frag_color = vec4(out_texel, 0.f , 0.f, 1.f);
}