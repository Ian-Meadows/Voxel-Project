#include "Scene.h"
#include "Window.h"

Scene::Scene()
{
    world = new World();

    shader = new Shader("Shaders/Voxel.vert", "Shaders/Voxel.frag", "Shaders/Voxel.geom");


    std::vector<TileImage> tiles;
    tiles.push_back(TileImage("Images/Cobble/cobblestone.png", "Images/Cobble/cobblestone_n.png", "Images/Cobble/cobblestone_s.png"));//0
    tiles.push_back(TileImage("Images/Dirt/dirt.png", "Images/Dirt/dirt_n.png", "Images/Dirt/dirt_s.png"));//1
    tiles.push_back(TileImage("Images/Grass/grass_block_side.png", "Images/Grass/grass_block_side_n.png", "Images/Grass/grass_block_side_s.png"));//2
    tiles.push_back(TileImage("Images/Grass/grass_block_top_greened.png", "Images/Grass/grass_block_top_n.png", "Images/Grass/grass_block_top_s.png"));//3
    tiles.push_back(TileImage("Images/Stone/stone.png", "Images/Stone/stone_n.png", "Images/Stone/stone_s.png"));//4
    tiles.push_back(TileImage("Images/Diamond/diamond_ore.png", "Images/Diamond/diamond_ore_n.png", "Images/Diamond/diamond_ore_s.png"));//5
    tiles.push_back(TileImage("Images/Light/Light_Surface.png", "Images/Light/Light_Surface_n.png", "Images/Light/Light_Surface.png"));//6

    




    textureAtlas = new TextureAtlas(256, 0, tiles);
    textureAtlas->Build();

    LightHandler::Init();


}
Scene::~Scene()
{

}


void Scene::RenderUI()
{
    glUseProgram(0);

    //  Display parameters
    glColor3f(1,1,1);
    glWindowPos2i(5,5);
    Print("Block to place: %s", world->GetPlacementBlockName().c_str());
}


void Scene::Render(glm::mat4 projection)
{
    CheckForBlockChange();
    world->Update(projection);  
    
    if(Input::GetKeyPressed(KeyCode::B))
    {
        firstAmbient = !firstAmbient;
    }
    
    
    LightHandler::BuildShadows(this);
    

    //main rendering
    textureAtlas->Load(GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2);
    glViewport(0, 0, Window::GetWidth(), Window::GetHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    LightHandler::RenderLights(projection, Camera::GetView());
    shader->use();

    
    
    
    //shader->setInt("tiles", textureAtlas->GetID());
    
    //setup texture positions
    shader->setInt("tiles", 0);
    shader->setInt("normals", 1);
    shader->setInt("speculars", 2);
    shader->setInt("depthArrayMap", 3);
    shader->setInt("directionalDepthMap", 4);

    if(firstAmbient)
    {
        //first ambient value
        shader->setFloat("ambient", 0.05f);
    }
    else
    {
        //second ambient value
        shader->setFloat("ambient", 0.25f);
    }


    //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    shader->setVec3("viewPos", Camera::GetPosition());
    LightHandler::SetUpLights(shader);
    RenderScene(shader, projection, Camera::GetView());

    
    

}


void Scene::RenderScene(Shader* shader, glm::mat4 projection, glm::mat4 view)
{
    //model = glm::translate(model, glm::vec3(5, 0, 0));

    shader->setInt("totalImages", textureAtlas->GetTotalImages());
    shader->setInt("imgSize", textureAtlas->GetImageSizes());
    shader->setInt("spacing", textureAtlas->GetSpacing());
    //shader->setMat4("projection", projection);
    //shader->setMat4("view", view);
    shader->setMat4("projectionView", projection * view);

    world->Render(shader);
}


void Scene::CheckForBlockChange()
{
    if(Input::GetKeyPressed(KeyCode::ALPHA_1))
    {
        world->ChangePlacementBlock(BlockType::cobble);
    }
    if(Input::GetKeyPressed(KeyCode::ALPHA_2))
    {
        world->ChangePlacementBlock(BlockType::light);
    }
    if(Input::GetKeyPressed(KeyCode::ALPHA_3))
    {
        world->ChangePlacementBlock(BlockType::grass);
    }
    if(Input::GetKeyPressed(KeyCode::ALPHA_4))
    {
        world->ChangePlacementBlock(BlockType::diamond);
    }
    if(Input::GetKeyPressed(KeyCode::ALPHA_5))
    {
        world->ChangePlacementBlock(BlockType::stone);
    }
}