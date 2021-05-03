#version 400 core

layout (location = 0) in ivec3 position;
layout (location = 1) in int OpenFaces;
layout (location = 2) in int tileNumbers[6];




//struct to store faces and tiles
out FaceInfo
{
	flat int openFaces;
	flat int tileNum[6];
} vs_out;




void main()
{
	vs_out.openFaces = OpenFaces;
	for(int i = 0; i < 6; ++i)
	{
		vs_out.tileNum[i] = tileNumbers[i];
	}

	//check for air block.(Old code, but leaving it just in case)
	if(bool(OpenFaces & 1))
	{
		//move air block behind window
		gl_Position = vec4(-1, -1, -1, 1);
	}
	else
	{
		gl_Position = vec4(position, 1.0);
	}
    
}