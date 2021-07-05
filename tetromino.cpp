#include "tetromino.h"
#include <stdexcept>
#include <cstdlib>
#include <cassert>


Tetromino::Tetromino()
{
    srand(time(0));

    // FIXME: Add handler for this exception
    if (!tilesTexture.loadFromFile("Textures\\tiles.png"))
        throw std::runtime_error("Could not load tiles texture.");
    tilesSprite.setTexture(tilesTexture);
}


void Tetromino::getRandomShape(Position buffer[SHAPE_SIZE_IN_TILES]) const
{
    int randomShape = rand() % NUMBER_OF_SHAPES;
    for (int tile = 0; tile < SHAPE_SIZE_IN_TILES; ++tile)
    {
        buffer[tile] = shapes[randomShape][tile];
    }
}


Tetromino::Color Tetromino::getRandomColor() const
{
    return static_cast<Color>(rand() % NUMBER_OF_COLORS);
}


void Tetromino::drawTile(sf::RenderWindow& window, const Color tileColor,
                         const Position& drawingPosition)
{
    assert(tileColor != EMPTY);
    tilesSprite.setTextureRect(sf::IntRect(tileColor * TILE_SIZE, 0,
                               TILE_SIZE, TILE_SIZE));
    tilesSprite.setPosition(drawingPosition.x * TILE_SIZE, drawingPosition.y * TILE_SIZE);
    window.draw(tilesSprite);
}


bool Tetromino::isSquare(const Position shape[SHAPE_SIZE_IN_TILES])
{
    for (int i = 0; i < SHAPE_SIZE_IN_TILES; ++i)
    {
        if (shape[i] != shapes[0][i])
            return false;
    }
    return true;
}


const Position Tetromino::shapes[NUMBER_OF_SHAPES][SHAPE_SIZE_IN_TILES] = 
{
    { Position(0, 0), Position(1, 0), Position(0, 1), Position(1, 1) }, // O
    { Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3) }, // I
    { Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2) }, // S
    { Position(1, 0), Position(1, 1), Position(0, 1), Position(0, 2) }, // Z
    { Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 2) }, // L
    { Position(1, 0), Position(1, 1), Position(1, 2), Position(0, 2) }, // J
    { Position(1, 0), Position(1, 1), Position(1, 2), Position(0, 1) }  // T
};
