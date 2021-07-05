#ifndef TETROMINO_H
#define TETROMINO_H

#include <SFML/Graphics.hpp>

typedef sf::Vector2i Position;

const int TILE_SIZE            = 18;
const int NUMBER_OF_SHAPES     = 7;
const int SHAPE_SIZE_IN_TILES  = 4;


class Tetromino
{
public:
    enum Color
    {
        EMPTY = -1,
        BLUE,
        PURPLE,
        RED,
        GREEN,
        YELLOW,
        CYAN,
        ORANGE,
        NUMBER_OF_COLORS
    };

                                            Tetromino();
    static const Position                   shapes[NUMBER_OF_SHAPES][SHAPE_SIZE_IN_TILES]; // Contains tile positions of different shapes
    void                                    getRandomShape(Position buffer[SHAPE_SIZE_IN_TILES]) const; 
    Color                                   getRandomColor() const;
    void                                    drawTile(sf::RenderWindow& window, const Color tileColor, const Position& drawingPosition); // Drawing position must be in tiles, not in pixels
    bool                                    isSquare(const Position shape[SHAPE_SIZE_IN_TILES]); // Checks if the shape has "O" form

private:
    sf::Texture                             tilesTexture;
    sf::Sprite                              tilesSprite;
};

#endif // TETROMINO_H
