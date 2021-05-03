#version 400 core
layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

uniform int totalImages;
uniform int imgSize;
uniform int spacing;
uniform mat4 model;
uniform mat4 projectionView;

//flat in mat4 modelViewProjectionMatrix[];
in FaceInfo
{
    flat int openFaces;
    flat int tileNum[6];
} gs_in[];


out vec2 texCoords;
out vec2 wholeTextureCoords;
out vec3 FragPos;
out vec3 normal;
out mat4 inModel;

void BuildFront();
void BuildBack();
void BuildTop();
void BuildBottom();
void BuildLeft();
void BuildRight();

//https://stackoverflow.com/questions/14560619/optimizing-cubes-rendering-with-geometry-shader
const vec4 cubeVerts[8] = vec4[8]
(
    //front
    vec4(-0.5, -0.5, -0.5, 1), //Left bottom
    vec4(-0.5, 0.5, -0.5, 1), //Left Top
    vec4(0.5, -0.5, -0.5, 1), //Right Bottom
    vec4(0.5, 0.5, -0.5, 1), //Right Top

    //back
    vec4(-0.5, -0.5, 0.5, 1),  //Left bottom
    vec4(-0.5, 0.5, 0.5, 1), //Left Top
    vec4(0.5, -0.5, 0.5, 1), //Right Bottom
    vec4(0.5, 0.5, 0.5, 1)  //Right Top
);


vec4 correctVerts[8];
vec3 correctFragPos[8];
mat3 normalMatrix;


//pre load vertices that way the calculation is only done once.
void GenerateCorrectVerts()
{
    //get the correct model position
    mat4 correctModel = model;
    correctModel[3][0] += gl_in[0].gl_Position.x;
    correctModel[3][1] += gl_in[0].gl_Position.y;
    correctModel[3][2] += gl_in[0].gl_Position.z;

    mat4 correctMatrix = projectionView * correctModel;
    for(int i = 0; i < 8; ++i)
    {
        correctVerts[i] = correctMatrix * (cubeVerts[i]);
        correctFragPos[i] = vec3(correctModel * cubeVerts[i]);
    }

    //create the normal matrix
    normalMatrix = mat3(transpose(inverse(correctModel)));

    //send model to fragment shader
    inModel = correctModel;
}



void main() 
{    
    
    int mask = 1;
    int value = gs_in[0].openFaces;

    //is its self trasparent
    if(bool(value & mask))
    {
        return;
    }

    GenerateCorrectVerts();

    //front
    if(bool(value & (mask << 1)))
    {
        normal = normalMatrix * vec3(0, 0, -1);
        BuildFront();
        EndPrimitive();
    }
    //right
    if(bool(value &  (mask << 6)))
    {
        normal = normalMatrix * vec3(1, 0, 0);
        BuildRight();
        EndPrimitive();
    }
    //back
    if(bool(value & (mask << 2)))
    {
        normal = normalMatrix * vec3(0, 0, 1);
        BuildBack();
        EndPrimitive();
    }
    //bottom
    if(bool(value &  (mask << 4)))
    {
        normal = normalMatrix * vec3(0, -1, 0);
        BuildBottom();
        EndPrimitive();
    }
    //left
    if(bool(value &  (mask << 5)))
    {
        normal = normalMatrix * vec3(-1, 0, 0);
        BuildLeft();
        EndPrimitive();
    }
    //top
    if(bool(value &  (mask << 3)))
    {
        normal = normalMatrix * vec3(0, 1, 0);
        BuildTop();
        EndPrimitive();
    } 
} 


//Get the correct texture coordinates for the specified tile in the texture atlas
void GenTexCoords(vec2 wholeTexCoords, int tile)
{
    wholeTextureCoords = wholeTexCoords;
    int size = int(ceil(sqrt(totalImages)));

    
    int y = int(mod(tile, size));
    int x = (tile - y) / size;

	float xSpacing = spacing / float(imgSize);
	float ySpacing = spacing / float(imgSize);

	float sx = (1.0 / float(size)) * float(x);
	float sy = (1.0 / float(size)) * float(y);
	
	vec2 tempCoord = wholeTexCoords;
	tempCoord.x = (tempCoord.x / float(size)) + sx;
	tempCoord.y = (tempCoord.y / float(size)) + sy;

	texCoords = tempCoord;
    //texCoords = wholeTexCoords;
}






void BuildFront()
{
    gl_Position = correctVerts[0];
    FragPos = correctFragPos[0];
    GenTexCoords(vec2(1, 0), gs_in[0].tileNum[0]);
    EmitVertex();

    gl_Position = correctVerts[1];
    FragPos = correctFragPos[1];
    GenTexCoords(vec2(1, 1), gs_in[0].tileNum[0]);
    EmitVertex();

    gl_Position = correctVerts[2];
    FragPos = correctFragPos[2];
    GenTexCoords(vec2(0, 0), gs_in[0].tileNum[0]);
    EmitVertex();


    gl_Position = correctVerts[3];
    FragPos = correctFragPos[3];
    GenTexCoords(vec2(0, 1), gs_in[0].tileNum[0]);
    EmitVertex();

}

void BuildBack()
{
    gl_Position = correctVerts[7];
    FragPos = correctFragPos[7];
    GenTexCoords(vec2(1, 1), gs_in[0].tileNum[1]);
    EmitVertex();

    gl_Position = correctVerts[5];
    FragPos = correctFragPos[5];
    GenTexCoords(vec2(0, 1), gs_in[0].tileNum[1]);
    EmitVertex();

    gl_Position = correctVerts[6];
    FragPos = correctFragPos[6];
    GenTexCoords(vec2(1, 0), gs_in[0].tileNum[1]);
    EmitVertex();

    gl_Position = correctVerts[4];
    FragPos = correctFragPos[4];
    GenTexCoords(vec2(0, 0), gs_in[0].tileNum[1]);
    EmitVertex();
}


void BuildTop()
{
    gl_Position = correctVerts[3];
    FragPos = correctFragPos[3];
    GenTexCoords(vec2(0, 0), gs_in[0].tileNum[2]);
    EmitVertex();

    gl_Position = correctVerts[1];
    FragPos = correctFragPos[1];
    GenTexCoords(vec2(1, 0), gs_in[0].tileNum[2]);
    EmitVertex();

    gl_Position = correctVerts[7];
    FragPos = correctFragPos[7];
    GenTexCoords(vec2(0, 1), gs_in[0].tileNum[2]);
    EmitVertex();

    gl_Position = correctVerts[5];
    FragPos = correctFragPos[5];
    GenTexCoords(vec2(1, 1), gs_in[0].tileNum[2]);
    EmitVertex();
}
void BuildBottom()
{
    gl_Position = correctVerts[4];
    FragPos = correctFragPos[4];
    GenTexCoords(vec2(0, 0), gs_in[0].tileNum[3]);
    EmitVertex();

    gl_Position = correctVerts[0];
    FragPos = correctFragPos[0];
    GenTexCoords(vec2(1, 0), gs_in[0].tileNum[3]);
    EmitVertex();

    gl_Position = correctVerts[6];
    FragPos = correctFragPos[6];
    GenTexCoords(vec2(0, 1), gs_in[0].tileNum[3]);
    EmitVertex();

    gl_Position = correctVerts[2];
    FragPos = correctFragPos[2];
    GenTexCoords(vec2(1, 1), gs_in[0].tileNum[3]);
    EmitVertex();
}
void BuildLeft()
{

    gl_Position = correctVerts[1];
    FragPos = correctFragPos[1];
    GenTexCoords(vec2(0, 1), gs_in[0].tileNum[4]);
    EmitVertex();

    gl_Position = correctVerts[0];
    FragPos = correctFragPos[0];
    GenTexCoords(vec2(0, 0), gs_in[0].tileNum[4]);
    EmitVertex();

    gl_Position = correctVerts[5];
    FragPos = correctFragPos[5];
    GenTexCoords(vec2(1, 1), gs_in[0].tileNum[4]);
    EmitVertex();

    gl_Position = correctVerts[4];
    FragPos = correctFragPos[4];
    GenTexCoords(vec2(1, 0), gs_in[0].tileNum[4]);
    EmitVertex();
}
void BuildRight()
{

    gl_Position = correctVerts[7];
    FragPos = correctFragPos[7];
    GenTexCoords(vec2(0, 1), gs_in[0].tileNum[5]);
    EmitVertex();

    gl_Position = correctVerts[6];
    FragPos = correctFragPos[6];
    GenTexCoords(vec2(0, 0), gs_in[0].tileNum[5]);
    EmitVertex();

    gl_Position = correctVerts[3];
    FragPos = correctFragPos[3];
    GenTexCoords(vec2(1, 1), gs_in[0].tileNum[5]);
    EmitVertex();

    gl_Position = correctVerts[2];
    FragPos = correctFragPos[2];
    GenTexCoords(vec2(1, 0), gs_in[0].tileNum[5]);
    EmitVertex();
}