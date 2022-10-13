
#include "Common.hlsl"


[earlydepthstencil]

PS_OUTPUT_GEOMETRY main(PS_INPUT input)
{
    PS_OUTPUT_GEOMETRY output;
    
    float2 texCoord = input.TexCoord;
    
    /*texCoord *= 100.0;
    texCoord = floor(texCoord);
    texCoord /= 100.0;
    float4 baseColor = TextureBaseColor.Sample(Sampler, texCoord).rgba;
    */
    
    float4 baseColor = TextureBaseColor.Sample(Sampler, input.TexCoord);
    
    //baseColor.rgb = 1.0 - baseColor.rgb;
    
    //baseColor.rgb *= 2.0;
    //baseColor.rgb = (baseColor.r + baseColor.g + baseColor.b) / 3.0;
    
    output.Color = baseColor;
    
    float3 normal = input.Normal;
    normal = normalize(normal);
    output.Normal.rgb = normal;
    output.Normal.a = 1.0f;
    
    float3 position = input.WorldPosition.xyz;
    output.Position.rgb = position;
    output.Position.a = 1.0f;
    
    
    return output;
    
}