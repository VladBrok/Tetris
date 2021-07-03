#ifndef GAME_H
#define GAME_H

#include "tetromino.h"
#include <vector>

class Game
{
public:
    Game();
    void run();

private:
    const int FPS_LIMIT;
    Tetromino tetromino;
    sf::RectangleShape fieldFrame;
    const int FIELD_WIDTH;
    const int FIELD_HEIGHT;
    std::vector<std::vector<Tetromino::Color>> field;

    void initFieldFrame();

    bool placeShapeToField(Position shape[Tetromino::SHAPE_SIZE_IN_TILES],
                           const Tetromino::Color shapeColor);

    bool canPlaceShapeAtPosition(const Position 
                                 shape[Tetromino::SHAPE_SIZE_IN_TILES]) const;

    bool moveShape(Position shape[Tetromino::SHAPE_SIZE_IN_TILES],
                   const Tetromino::Color shapeColor,
                   const int offsetX, const int offsetY);

    void clearFullLines();

    void rotateShape(Position shape[Tetromino::SHAPE_SIZE_IN_TILES],
                     const Tetromino::Color shapeColor);

    void drawField(sf::RenderWindow& window);
};

#endif // GAME_H
