#ifndef GAME_H
#define GAME_H

#include "tetromino.h"
#include <vector>


class Game
{
public:
                                                Game();
    void                                        run();

private:
    enum ShapeMovementType
    {
        ROTATE,
        SHIFT_HORIZONTALLY
    };
    const int                                   FPS_LIMIT;
    Tetromino                                   tetromino;
    sf::RectangleShape                          fieldFrame;
    sf::RectangleShape                          sideFrame;
    sf::Text                                    text;
    sf::Font                                    font;
    const int                                   FIELD_WIDTH;
    const int                                   FIELD_HEIGHT;
    std::vector<std::vector<Tetromino::Color>>  field;

    void                                        initFieldFrame();
    void                                        initSideFrame();
    void                                        initText();
    bool                                        placeShapeToField(Position shape[SHAPE_SIZE_IN_TILES], const Tetromino::Color shapeColor);
    bool                                        canPlaceShapeAtPosition(const Position shape[SHAPE_SIZE_IN_TILES]) const;
    bool                                        moveShape(const ShapeMovementType moveType, Position shape[SHAPE_SIZE_IN_TILES], 
                                                          const Tetromino::Color shapeColor, const int offsetX = 0, const int offsetY = 0);
    int                                         clearFullLines();
    void                                        drawField(sf::RenderWindow& window);
    void                                        drawNextShape(sf::RenderWindow& window, const Tetromino::Color shapeColor, const Position shape[SHAPE_SIZE_IN_TILES]);
};

#endif // GAME_H
