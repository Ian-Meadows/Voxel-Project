#version 400 core

#define MAX_LIGHTS 25

out vec4 FragColor;


struct PointLight 
{
    vec3 position;
    //0:false
    //1:true
    int hasAttenuation;
    float farPlane;
};

uniform int totalLights;
uniform vec3 LightPositions[MAX_LIGHTS];
uniform PointLight pointLights[MAX_LIGHTS];

uniform sampler2D tiles;
uniform sampler2D normals;
uniform sampler2D speculars;

uniform samplerCubeArray depthArrayMap;

in vec3 normal;
in vec3 FragPos;
uniform vec3 viewPos;

in mat4 inModel;


in vec2 texCoords;
in vec2 wholeTextureCoords;

//here to prevent errors
uniform vec3 lightPos;
uniform float far_plane;

uniform float ambient;

//used for sampling the cubemap
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);



//Info for a singular point light shadow taken from https://learnopengl.com/Advanced-Lighting/Shadows/Point-Shadows
float ShadowCalculation(vec3 fragPos, int lightNumber)
{
    vec3 fragToLight = fragPos - pointLights[lightNumber].position;

    vec3 lightDir = normalize(pointLights[lightNumber].position - fragPos);

    float currentDepth = length(fragToLight);

    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / pointLights[lightNumber].farPlane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        //to get the correct cubemap use w in a vec4 like indexing through an array
        float closestDepth = texture(depthArrayMap, vec4(fragToLight + gridSamplingDisk[i] * diskRadius, lightNumber)).r;
        closestDepth *= pointLights[lightNumber].farPlane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);   
        
    return shadow;
}


// normal map information taken from http://ogldev.atspace.co.uk/www/tutorial26/tutorial26.html, https://learnopengl.com/Advanced-Lighting/Normal-Mapping, and https://stackoverflow.com/questions/5255806/how-to-calculate-tangent-and-binormal
vec4 GetTangent(){
    vec3 p_dx = dFdx(FragPos);
    vec3 p_dy = dFdy(FragPos);
    // compute derivations of the texture coordinate
    vec2 tc_dx = dFdx(texCoords.st);
    vec2 tc_dy = dFdy(texCoords.st);
    // compute initial tangent and bi-tangent
    vec3 t = normalize( tc_dy.y * p_dx - tc_dx.y * p_dy );
    // get new tangent from a given mesh normal
    vec3 n = normalize(normal);
    vec3 x = cross(n, t);
    t = cross(x, n);
    t = normalize(t);
    return vec4(t, 1.0);
}

vec3 CalcBumpedNormal(vec3 normalMap)
{
    vec3 Normal = normalize(normal);
    vec3 Tangent = normalize(inModel * GetTangent()).xyz;
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 Bitangent = cross(Tangent, Normal);
    //move to range [-1,1]
    normalMap = 2.0 * normalMap - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    NewNormal = TBN * normalMap;
    NewNormal = normalize(NewNormal);
    return NewNormal;
}

vec4 GetLighting(vec3 specularMap, vec3 normalMap)
{
    //light block so no lighting
    if(specularMap.r > 0.95 && specularMap.g > 0.95 && specularMap.b > 0.95)
    {
        return vec4(1.0, 1.0, 1.0, 1.0);
    }

    vec3 normal = CalcBumpedNormal(normalMap);

    vec3 lightColor = vec3(1.0);

    // ambient
    float ambientStrength = ambient;

    vec3 ambientColor = ambientStrength * lightColor;

    vec4 lightTotal = vec4(ambientColor, 1.0);

    //loop though each light
    for(int i = 0; i < totalLights; ++i)
    {
        //float shadow = ShadowCalculation(FragPos, i);
        float shadow = ShadowCalculation(FragPos, i);
        // diffuse 
        vec3 norm = normalize(normal);
        vec3 lightDir = normalize(pointLights[i].position - FragPos);

        //make lights fade out over distance
        float distance = length(pointLights[i].position - FragPos);

        //attenuation is to make the light fade the farther it travels
        float attenuation = 1.0;
        if(bool(pointLights[i].hasAttenuation))
        {
            attenuation = 1.0 / (1.0 + 0.009 * distance + 0.032 * (distance * distance));
        }

        //diffuse
        float diff = max(dot(norm, lightDir) * 1.25, 0.0);
        vec3 diffuse = diff * attenuation * lightColor;
        
        // specular
        float specularStrength = specularMap.r + specularMap.g + specularMap.b;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * attenuation * lightColor;

        //add all lights together for fragment
        lightTotal = vec4(lightTotal.rgb + (1.0 - shadow) * (diffuse + specular), 1.0);
        
    }
    
  	
     
    return lightTotal;
}


vec3 ProceduralLightTexture(vec2 coords)
{
    //generate outside gray-black fade
    float dist = distance(coords, vec2(0.5, 0.5));
    float cDist = clamp(dist * 1.35, 0.0, 1.0);
    if(dist < 0.45)
    {

        vec2 loc = vec2(0.5, 0.5) - coords;

        //spiral code from https://www.shadertoy.com/view/ldBGDc
        float r = length(loc);
        float a = atan(loc.y, loc.x);
        float v = sin(100.0*(sqrt(r)-0.02*a- 0.3));
        float c = clamp(v,0.0,1.0);

        //light yellow fades to darker based on fragments distance from center
        return mix(vec3(1.0, 1.0, 1.0 - cDist), vec3(1.0, 0.75, 0.0), c);

        return vec3(c, c, c);
    }
    else
    {
        
        return vec3(1.0 - cDist);
    }
    
}


void main()
{
    //get specular
    vec4 specular = texture(speculars, texCoords);

    vec4 color = vec4(1.0);

    //only the light has a specular map that is all white
    if(specular.r > 0.99 && specular.g > 0.99 && specular.b > 0.99)
    {
        color = vec4(ProceduralLightTexture(wholeTextureCoords), 1.0);
    }
    else
    {
        color = texture(tiles, texCoords);
    }

    //get normal
    vec4 normalMap = texture(normals, texCoords);
    

    vec3 lightingResult = GetLighting(specular.rgb, normalMap.rgb).xyz;
    FragColor = vec4(lightingResult, 1.0) * color;
}