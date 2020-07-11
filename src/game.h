#ifndef GAME_H
#define GAME_H

#include <Arduboy2.h>
#include <Tinyfont.h>

#define WORLD_WIDTH 14
#define WORLD_HEIGHT 7
#define TILE_SIZE 16
#define PLAYER_SIZE 16
#define PLAYER_X_OFFSET WIDTH / 2 - PLAYER_SIZE / 2
#define PLAYER_Y_OFFSET HEIGHT / 2 - PLAYER_SIZE / 2

enum class GameState : uint8_t
{
    TITLE,
    GAMEPLAY,
    GAMEOVER,
    HIGHSCORE
};

enum SpriteTypes
{
    GRASS,
    WATER,
    TREES,
    STONE
};

const unsigned char tiles[] PROGMEM  = {
// width, height,
16, 16,

//Grass
0xff, 0x7f, 0xfb, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xf7, 0xff, 0xfd, 0xff, 0xff, 0xf7, 0x7f, 0xff,
0xdf, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0xff, 0xef, 0xfe, 0xff, 0xff, 0xfb, 0xff, 0x7f, 0xff,

//Water
0x08, 0x10, 0x10, 0x08, 0x10, 0x08, 0x10, 0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x20, 0x40, 0x40, 0x20, 0x00, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02, 0x01, 0x02, 0x21, 0x40, 0x40,

//Tree
0xff, 0x1f, 0x5b, 0x3f, 0xeb, 0xdd, 0xff, 0xf7, 0xbb, 0xef, 0xfd, 0x7f, 0xe3, 0xcb, 0xe3, 0xff,
0xff, 0xc7, 0x96, 0xc7, 0xff, 0xff, 0xef, 0xfd, 0xff, 0xe3, 0xcb, 0xe3, 0xff, 0xff, 0x7b, 0xff,

//Stone
0xff, 0xdf, 0x7b, 0x3f, 0x9f, 0x6f, 0x77, 0xab, 0xdb, 0xd7, 0xcd, 0x5f, 0xbf, 0x77, 0xff, 0xff,
0xff, 0xc1, 0xdc, 0xd3, 0xaf, 0x9f, 0xae, 0xb0, 0xbb, 0xbd, 0xbd, 0xba, 0xd7, 0xcc, 0x63, 0xff,

};

const int tilesWide = WIDTH / TILE_SIZE + 1;
const int tilesTall = HEIGHT / TILE_SIZE + 1;
// Allows map move up this amount of pixels before the screen moves back.
const int cameraTranslationOffset = TILE_SIZE;
class SupremeSpoonGame
{
public:
    SupremeSpoonGame(void) = default;
    void run(void);

private:
    GameState showTitleScreen();
    GameState showGameplayScreen();
    GameState showGameOverScreen();
    GameState showHighScoreScreen();
    Arduboy2Base arduboy;
    Tinyfont tinyfont = Tinyfont(arduboy.getBuffer(), Arduboy2::width(), Arduboy2::height());
    GameState currGameState = GameState::TITLE;
    void drawWorld();
    void drawCursor();
    void debugDrawPlayerCoordinates(int mapX, int mapY);
    void playerInput();

    int world[WORLD_HEIGHT][WORLD_WIDTH] = {
        { TREES, GRASS, GRASS, WATER, GRASS, GRASS, GRASS, TREES, GRASS, GRASS, GRASS, GRASS, GRASS, TREES },
        { GRASS, WATER, WATER, WATER, GRASS, WATER, GRASS, GRASS, GRASS, GRASS, GRASS, STONE, GRASS, GRASS },
        { GRASS, GRASS, GRASS, GRASS, GRASS, WATER, STONE, GRASS, GRASS, GRASS, TREES, GRASS, GRASS, GRASS },
        { STONE, GRASS, GRASS, STONE, TREES, WATER, WATER, WATER, GRASS, WATER, WATER, GRASS, TREES, GRASS },
        { GRASS, GRASS, GRASS, GRASS, TREES, GRASS, GRASS, GRASS, TREES, WATER, GRASS, GRASS, STONE, TREES },
        { GRASS, GRASS, GRASS, WATER, STONE, GRASS, GRASS, TREES, TREES, TREES, GRASS, GRASS, WATER, WATER },
        { GRASS, WATER, WATER, TREES, GRASS, WATER, WATER, TREES, TREES, GRASS, GRASS, GRASS, GRASS, STONE }
    };
    int mapX = TILE_SIZE / 2;
    int mapY = TILE_SIZE / 2;
};
#endif
