/*
** EPITECH PROJECT, 2022
** Step1toLife
** File description:
** Game
*/

#include <sstream>
#include "camera.hpp"
#include "Game.hpp"

Game::Game()
{
    this->seed = std::rand() % 100000;
    this->window = new Window(720, 480, 70);
    this->inputs = new Inputs();
    this->chunkmap = new Chunkmap(this->seed);
    SetTargetFPS(150);
    this->window->initWindow();
    this->held = GRASS;
}

static Vector3 getPos(float x, float y, float z)
{
    Vector3 vec = {};
    vec.x = x;
    vec.y = y;
    vec.z = z;

    return (vec);
}

bool IsInBlock(Vector3 pos, Chunkmap* chunkmap)
{
    int chunk_x = std::floor(std::floor(pos.x)/16);
    int chunk_y = std::floor(std::floor(pos.z)/16);
    int i = fmod(pos.x, 16);
    i = i < 0 ? i + 16 : i;
    int k = std::floor(pos.y);
    int j = fmod(pos.z, 16);
    j = j < 0 ? j + 16 : j;
            std::cout << "Y = " << k <<std::endl;
            std::cout << "IN BLOCK " << i << " " << k << " " << j << std::endl;
            std::cout << "IN CHUNK " << chunk_x << " " << chunk_y << std::endl;
    if(k <= 0 || k >= 20)
        return false;
    return ((chunkmap->GetChunk(chunk_x, chunk_y)->blockmap[i][j][k]->type) != AIR);
}

void Game::init()
{
	this->cam.Setup(90,Vector3{ 0, 0, 0 });
	this->cam.MoveSpeed.z = 10;
	this->cam.MoveSpeed.x = 5;
	this->cam.FarPlane = 5000;
    this->cam.SetCameraPosition(getPos(0.0f, 20.0f, 0.0f));

    std::function<bool(rlFPCamera&, Vector3&, const Vector3&)> ValidateCamPosition =
    [this](rlFPCamera& camera, Vector3& newPosition, const Vector3& oldPosition) {
        if(IsInBlock(newPosition, this->chunkmap)){
            std::cout << "IN BLOCK" << std::endl;
            newPosition = oldPosition;
        }
        return true;
    };
    this->cam.ValidateCamPosition = ValidateCamPosition;
}

void Game::loop()
{
    //this->chunkmap->GenChunk(0, 0);
    while(!this->window->isWindowClosed()) {
        window->begin();
        this->chunkmap->CheckLoading(std::floor(this->cam.GetCameraPosition().x), std::floor(this->cam.GetCameraPosition().z));
        this->sight = this->cam.GetViewRay();
        this->events();
        this->cam.Update();
        //std::cout << "cam position: {" << this->cam.GetCameraPosition().x << ", " << this->cam.GetCameraPosition().y << ", " << this->cam.GetCameraPosition().z << "}" << std::endl;
        this->cam.BeginMode3D();
        this->draw();
        this->cam.EndMode3D();
        this->drawHUD();
        window->end();
    }
}

std::string Game::heldstr(BlockType block)
{
    switch (block)
    {
    case GRASS:
        return std::string("GRASS");
    case DIRT:
        return std::string("DIRT");
    case STONE:
        return std::string("STONE");
    case COBBLE:
        return std::string("COBBLE");
    default:
        return std::string("AIR");
    }
}

void Game::drawHUD()
{
    std::stringstream blocks;
    blocks << "Current inventory is " << this->inv[1] << " STONE, " << this->inv[2] << " DIRT, " << this->inv[3] << " GRASS, " << this->inv[4] << " COBBLE";
    DrawText(blocks.str().c_str(), 20, 300, 10, BLACK);
    std::stringstream holding;
    holding << "Currently holding " << this->heldstr(this->held);
    DrawText(holding.str().c_str(), 20, 330, 10, BLACK);
    if(this->showHUD) {
        std::stringstream mouse;
        mouse << "Current Mouse input is " << this->mouseMovement.x << ", " << this->mouseMovement.y;
        DrawText(mouse.str().c_str(), 40, 40, 20, BLACK);
        std::stringstream coord;
        coord << "Current coordinates is " << this->cam.GetCameraPosition().x << ", " << this->cam.GetCameraPosition().z;
        DrawText(coord.str().c_str(), 40, 80, 20, BLACK);
        std::stringstream chunk;
        chunk << "Current Chunk is " << std::floor(std::floor(this->cam.GetCameraPosition().x)/16) << ", " << std::floor(std::floor(this->cam.GetCameraPosition().z)/16);
        DrawText(chunk.str().c_str(), 40, 120, 20, BLACK);
        std::stringstream in_chunk_coord;
        in_chunk_coord << "Current in_chunk_coord is " << fmod((this->cam.GetCameraPosition().x), float(16)) << ", " << fmod((this->cam.GetCameraPosition().z), float(16));
        DrawText(in_chunk_coord.str().c_str(), 40, 160, 20, BLACK);
        std::stringstream fps;
        fps << "Current fps is " << GetFPS();
        DrawText(fps.str().c_str(), 40, 200, 20, BLACK);
    }

}

void Game::draw()
{
    Vector3 pos = { 0.0f, 0.0f, -10.0f };
    DrawSphere(pos, 2.0f, RED);
    DrawPlane(Vector3{ 0, -1, 0 }, Vector2{ 50, 50 }, BEIGE);
    this->chunkmap->Draw();
}


void Game::events()
{
    this->mouseMovement = this->inputs->GetMouse(false);
    if(WindowShouldClose())
        this->window->close();
    if(this->inputs->IsPressed(KEY_Y)) {
        this->chunkmap->debugChunkPrint(std::floor(std::floor(this->cam.GetCameraPosition().x)/16), std::floor(std::floor(this->cam.GetCameraPosition().z)/16));
        std::cout << sizeof(Chunk) << std::endl;
        std::cout << sizeof(Block) * 16 * 16 * 100 * 25<< std::endl;
    }
    if(this->inputs->IsPressed(KEY_O)) {
        this->showHUD ^= true; //toggles ShowHUD
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        this->trybreak();
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        this->tryput();
    }
    if(GetMouseWheelMove() < 0) {
        this->held = (BlockType) (this->held - 1);
        if (this->held == AIR)
            this->held = COBBLE;
    }
    if(GetMouseWheelMove() > 0) {
        this->held = (BlockType) (this->held + 1);
        if (this->held == VOID)
            this->held = STONE;
    }
}

void Game::trybreak()
{
    RayColData best = {-1, -1, -1, -1, -1, 200.0f};
    RayCollision currentCol;
    int chunk_x = std::floor(std::floor(this->cam.GetCameraPosition().x)/16);
    int chunk_y = std::floor(std::floor(this->cam.GetCameraPosition().z)/16);

    for(int i = 0; i < 16; i++)
        for(int j = 0; j <16; j++)
            for(int k = 0; k < 20; k++) {
                currentCol = GetRayCollisionBox(this->sight, this->chunkmap->GetChunk(chunk_x, chunk_y)->blockmap[i][j][k]->boundingBox);
                if (currentCol.hit && (this->chunkmap->GetChunk(chunk_x, chunk_y)->blockmap[i][j][k]->type != AIR) && (currentCol.distance < best.distance))
                    best = {chunk_x, chunk_y, i, j, k, currentCol.distance, currentCol.normal};
            }
    if (best.block_i != -1) {
        this->inv[(this->chunkmap->GetChunk(chunk_x, chunk_y)->blockmap[best.block_i][best.block_j][best.block_k]->type)] += 1;
        this->chunkmap->GetChunk(chunk_x, chunk_y)->blockmap[best.block_i][best.block_j][best.block_k]->Destroy();
        //add inv management
    }
}

void Game::tryput()
{
    RayColData best = {-1, -1, -1, -1, -1, 200.0f};
    RayCollision currentCol;
    int chunk_x = std::floor(std::floor(this->cam.GetCameraPosition().x)/16);
    int chunk_y = std::floor(std::floor(this->cam.GetCameraPosition().z)/16);

    for(int i = 0; i < 16; i++)
        for(int j = 0; j <16; j++)
            for(int k = 0; k < 20; k++) {
                currentCol = GetRayCollisionBox(this->sight, this->chunkmap->GetChunk(chunk_x, chunk_y)->blockmap[i][j][k]->boundingBox);
                if (currentCol.hit && (this->chunkmap->GetChunk(chunk_x, chunk_y)->blockmap[i][j][k]->type != AIR) && (currentCol.distance < best.distance))
                    best = {chunk_x, chunk_y, i, j, k, currentCol.distance, currentCol.normal};
            }
    if (best.block_i != -1 && best.block_k <19 && this->inv[this->held]) {
        this->inv[this->held] -= 1;
        std::cout << this->heldstr(this->held) << std::endl;
        this->chunkmap->GetChunk(chunk_x, chunk_y)->blockmap[best.block_i + (int) best.colNorm.x][best.block_j +(int) best.colNorm.z][best.block_k +(int) best.colNorm.y]->Create(this->held);
        //add inv management
    }
}

Game::~Game()
{
    delete this->window;
    delete this->chunkmap;
    delete this->inputs;
}

void launch_game(Game &game)
{
    std::cout << "********************************" << std::endl;
    std::cout << "init game" << std::endl;
    game.init();
    std::cout << "start loop" << std::endl;
    game.loop();
    std::cout << "stop window" << std::endl;
    CloseWindow();
    std::cout << "********************************" << std::endl;
}

void quit_game(Game &game)
{
    std::cout << "********************************" << std::endl;
    std::cout << "close window" << std::endl;
    CloseWindow();
    std::cout << "********************************" << std::endl;
}