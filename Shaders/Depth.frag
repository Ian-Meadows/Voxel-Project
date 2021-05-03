//some info from: https://learnopengl.com/Advanced-Lighting/Shadows/Point-Shadows
#version 400 core

uniform sampler2D tiles;
uniform sampler2D normals;
uniform sampler2D speculars;


uniform vec3 lightPos;
uniform float far_plane;

in vec3 normal;
in vec3 FragPos;

in mat4 inModel;


in vec2 texCoords;

void main()
{
    // get distance between fragment and light source
    float lightDistance = length(FragPos.xyz - lightPos);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / far_plane;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;
}