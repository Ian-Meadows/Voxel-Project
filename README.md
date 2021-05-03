## Things to take note of
- Multiple lights with per-pixel lighting, per-light shadows, normal maps, and specular maps(how shiny something looks), attenuation(light fades the farther it travels).
- This is a scene containing 49 chunks. Each chunk contains 65,536 blocks. Making a total of 3,211,264 blocks if you include the air blocks.
- Each cube is generated using a geometry shader. Faces on each cube are pre-culled if they can never be viewed.
- You can place and remove blocks. This includes lights. You can place up to 25 lights in the scene. Every other block is unlimited.
- Each block face has its own normal and specular map. This is done using a texture atlas to store every texture into one image. (There is an atlas for texture, normals, and speculars)
- The light block texture is a procedural texture.
- Note: the light is coming from a point inside the light block. You can view the point by sticking the camera inside the block. This point is actually drawn using a geometry shader.

## Things I am proud of
- I created a way to generate shadows for multiple lights and store them into one texture object. This was a samplerCubeArray. 
- I created a system to only render the faces the could be viewed. This involved using a geometry shader and some precalculations on the CPU. If I did not do this the project would not be able to run in real time because for each light to generate a shadow map they each have to render the scene 6 times.
- I created a texture atlas system that could store multiple textures. I also created the algorithm to pull the a texture out of the texture atlas using a single number.


## Building
- To build use make
- To clean use make clean

## Running
- run the voxel_project file that is generated. ./voxel_project

## Exit 
- To exit use the ESC key

## Controls
- L: lock/unlock mouse
- W,A,S,D: move camera
- arrow keys: rotate camera
- Space: place block
- R: remove block
- M: move moving light to camera position
- E: remove blocks in an area around camera
- Q: place blocks in an area directly below camera (uses current selected block except light)
- B: change ambient lighting
- left click on screen locks mouse. You can Unlock it with L
- 1: change block to cobblestone
- 2: change block to light (not yet implemented)
- 3: change block to grass
- 4: change block to diamond
- 5: change block to stone

if mouse is locked:
- mouse movement: rotates camera
- left click: place block
- right click: remove block
 

## References
- Code from one of my own personal projects
- learnopengl.com
-- https://learnopengl.com/Advanced-Lighting/Shadows/Point-Shadows
-- https://learnopengl.com/Advanced-Lighting/Normal-Mapping

- http://ogldev.atspace.co.uk/www/tutorial26/tutorial26.html
- https://stackoverflow.com/questions/5255806/how-to-calculate-tangent-and-binormal

- Documentation from Khronos.org