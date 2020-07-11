#include "game.h"

void SupremeSpoonGame::run(void)
{
    arduboy.begin();
    arduboy.setFrameRate(45);
    arduboy.initRandomSeed();

    while (true)
    {
        switch (currGameState)
        {
        case GameState::GAMEPLAY:
            showGameplayScreen();
            break;

        case GameState::GAMEOVER:
            showGameOverScreen();
            break;

        case GameState::HIGHSCORE:
            showHighScoreScreen();
            break;

        default:
            this->currGameState = showTitleScreen();
            break;
        }
    }
}

GameState SupremeSpoonGame::showTitleScreen()
{
    while (true)
    {
        if (!arduboy.nextFrame())
            continue;
        arduboy.pollButtons();

        arduboy.clear();
        tinyfont.setCursor(23, 21);
        tinyfont.print(F("Title screen"));
        if (arduboy.justPressed(A_BUTTON))
        {
            this->currGameState = showGameplayScreen();
        }
        arduboy.display();
    }
}

GameState SupremeSpoonGame::showGameplayScreen()
{
    while (true)
    {
        if (!arduboy.nextFrame())
            continue;
        arduboy.pollButtons();
        arduboy.clear();
        playerInput();
        drawWorld();
        drawPlayer();

        if (arduboy.justPressed(A_BUTTON))
        {
            this->currGameState = showGameOverScreen();
        }
        if (arduboy.justPressed(B_BUTTON))
        {
            this->currGameState = showHighScoreScreen();
        }
        arduboy.display();
        
    }
}

GameState SupremeSpoonGame::showGameOverScreen()
{
    while (true)
    {
        if (!arduboy.nextFrame())
            continue;
        arduboy.pollButtons();

        arduboy.clear();
        tinyfont.setCursor(23, 21);
        tinyfont.print(F("Game Over!"));
        if (arduboy.justPressed(A_BUTTON))
        {
            this->currGameState = showTitleScreen();
        }
        arduboy.display();
    }
}

GameState SupremeSpoonGame::showHighScoreScreen()
{
    while (true)
    {
        if (!arduboy.nextFrame())
            continue;
        arduboy.pollButtons();
        arduboy.clear();
        tinyfont.setCursor(23, 21);
        tinyfont.print(F("High Score screen"));
        if (arduboy.justPressed(A_BUTTON))
        {
            this->currGameState = showTitleScreen();
        }
        arduboy.display();
    }
}

void SupremeSpoonGame::drawWorld()
{
    for (int y = 0; y < tilesTall; y++)
    {
        for (int x = 0; x < tilesWide; x++)
        {
            // Set the boundaries of the map
            const int tileX = x - mapX / TILE_SIZE;
            const int tileY = y - mapY / TILE_SIZE;
            bool isInBounds = tileX >= 0 && tileY >= 0 && tileX < WORLD_WIDTH && tileY < WORLD_HEIGHT;
            if(isInBounds) { // Only draw up to the boundary
                Sprites::drawOverwrite(x * TILE_SIZE + mapX % cameraTranslationOffset, y * TILE_SIZE + mapY % cameraTranslationOffset, tiles, world[tileY][tileX]);
            }
        }
    }
    debugDrawPlayerCoordinates(mapX, mapY);
}

void SupremeSpoonGame::debugDrawPlayerCoordinates(int mapX, int mapY) {
    arduboy.fillRect(0,0,48,8,BLACK);
    tinyfont.setCursor(0,0);
    tinyfont.print(mapX);
    tinyfont.print(",");
    tinyfont.print(mapY);
}

void SupremeSpoonGame::drawPlayer() {
    arduboy.fillRect(PLAYER_X_OFFSET, PLAYER_Y_OFFSET, PLAYER_SIZE, PLAYER_SIZE, BLACK);
}

void SupremeSpoonGame::playerInput()
{
    if(arduboy.justPressed(UP_BUTTON) && mapY < PLAYER_Y_OFFSET) {
        mapY += TILE_SIZE;
    }
    if (arduboy.justPressed(DOWN_BUTTON) && PLAYER_Y_OFFSET + PLAYER_SIZE < mapY + TILE_SIZE * WORLD_HEIGHT) {
        mapY -= TILE_SIZE;
    }
    if (arduboy.justPressed(LEFT_BUTTON) && mapX < PLAYER_X_OFFSET) {
        mapX += TILE_SIZE;
    }
    if (arduboy.justPressed(RIGHT_BUTTON) && PLAYER_X_OFFSET + PLAYER_SIZE < mapX + TILE_SIZE * WORLD_WIDTH) {
        mapX -= TILE_SIZE;
    }
}