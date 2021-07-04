#ifndef TETROMINO_H
#define TETROMINO_H

#include <SFML/Graphics.hpp>

typedef sf::Vector2i Position;

class Tetromino
{
public:
    static const int TILE_SIZE = 18;
    static const int NUMBER_OF_SHAPES = 7;
    static const int SHAPE_SIZE_IN_TILES = 4;

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

    static const Position shapes[NUMBER_OF_SHAPES][SHAPE_SIZE_IN_TILES]; // Contains tile positions of different shapes

	Tetromino();

    void getRandomShape(Position buffer[SHAPE_SIZE_IN_TILES]) const; 

    Color getRandomColor() const;

    void drawTile(sf::RenderWindow& window, const Color tileColor,
                  const Position& drawingPosition); // Drawing position must be in tiles, not in pixels

private:
    sf::Texture tilesTexture;
    sf::Sprite tilesSprite;
};

#endif // TETROMINO_H
