
#include "Common.hlsl"


PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    
    float4 baseColor = TextureBaseColor.Sample(Sampler, input.TexCoord).rgba;
    float4 normal = TextureNormal.Sample(Sampler, input.TexCoord).rgba;
    float4 position = TexturePosition.Sample(Sampler, input.TexCoord);
    
    float3 eye = CameraPosition.xyz - position.xyz;
    
    eye = normalize(eye);
    float3 ref = reflect(-eye, normal.xyz);
    
    float3 diffuse;
    {
        diffuse = saturate(dot(LightDirection.xyz, normal.xyz));
        diffuse *= baseColor.rgb;
        diffuse *= LightColor.rgb;
        
        // 正規化ランバート
        diffuse /= PI;
        
    }
    
    float3 specular;
    {
        //フォン
        specular = saturate(dot(LightDirection.xyz, ref.xyz));
        specular = pow(specular, 50);
        specular *= LightColor.rgb * 0.1;
        
        // 正規化フォン
        float div = 2.0 * PI / (50 + 1);
        specular /= div;

    }
    
    
    output.Color.rgb = diffuse.rgb + specular.rgb;
    output.Color.a = 1.0;
    
    return output;
    
}