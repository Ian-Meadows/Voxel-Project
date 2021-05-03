#version 400 core

layout(points) in;
layout(triangle_strip,max_vertices=4) out;
//#extension GL_EXT_geometry_shader4 : enable

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform float size;

mat4 modelView;
mat4 wholeMatrix;

out vec2 texCoords;

void billboard(float x,float y,int s,int t)
{
   texCoords = vec2(s, t);

   //  Determine position
   vec2 delta = vec2(x,y);
   vec4 p = gl_in[0].gl_Position;
   p.x += dot(delta,modelView[0].xy);
   p.y += dot(delta,modelView[1].xy);
   p.z += dot(delta,modelView[2].xy);
   gl_Position = wholeMatrix*p;
   //  Emit new vertex
   EmitVertex();
}

void main()
{
    modelView = view * model;
    wholeMatrix = projection * view * model;


   billboard(-size,-size , 0,0);
   billboard(+size,-size , 1,0);
   billboard(-size,+size , 0,1);
   billboard(+size,+size , 1,1);
   EndPrimitive();
}