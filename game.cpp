#include "game.h"

///////////////////////
// DEBUG, remove later
#include <iostream>
using std::cout;
//////////////////////

Game::Game(): FPS_LIMIT(60), FIELD_WIDTH(10), FIELD_HEIGHT(20)
{
     field.assign(FIELD_HEIGHT, std::vector<Tetromino::Color>(FIELD_WIDTH, Tetromino::EMPTY));
     initFieldFrame();
}


void Game::initFieldFrame()
{
     fieldFrame.setSize(sf::Vector2f(FIELD_WIDTH * Tetromino::TILE_SIZE,
                                     FIELD_HEIGHT * Tetromino::TILE_SIZE));
     fieldFrame.setFillColor(sf::Color::Transparent);
     fieldFrame.setOutlineThickness(6.f);
     fieldFrame.setOutlineColor(sf::Color::Black);
     fieldFrame.setPosition(Tetromino::TILE_SIZE, Tetromino::TILE_SIZE);
}


void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(Tetromino::TILE_SIZE * FIELD_WIDTH * 2.2f,
                                          Tetromino::TILE_SIZE * FIELD_HEIGHT * 1.3f),
                                                                            "Tetris");
    window.setFramerateLimit(FPS_LIMIT);


    Position shape[Tetromino::SHAPE_SIZE_IN_TILES];
    Tetromino::Color shapeColor;
    bool shapeIsActive = false;
    float dropDelay = 0.27f;
    float dropTimer = 0.f;
    sf::Clock clock;

    int shapeOffsetX = 0;
    int shapeOffsetY = 1;


    while (window.isOpen())
    {
        dropTimer += clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    shapeOffsetX = -1;
                    break;
                case sf::Keyboard::Right:
                    shapeOffsetX = 1;
                    break;
                }
            }
        }


        if (dropTimer >= dropDelay)
        {
            shapeOffsetY = 1;
            dropTimer = 0.f;
        }
        else
        {
            shapeOffsetY = 0;
        }

        if (!shapeIsActive)
        {
            tetromino.getRandomShape(shape);
            shapeColor = tetromino.getRandomColor();

            if (!placeShapeToField(shape, shapeColor)) // Game over condition
                window.close();
            shapeIsActive = true;
        }
        else if (shapeOffsetX || shapeOffsetY)
        {
            if (!moveShape(shape, shapeColor, shapeOffsetX, shapeOffsetY) &&
                 shapeOffsetX == 0)
            {
                 shapeIsActive = false;
            }
            shapeOffsetX = 0;
        }


        window.clear(sf::Color::White);

        window.draw(fieldFrame);
        drawField(window);

        window.display();
    }
}


bool Game::placeShapeToField(Position shape[Tetromino::SHAPE_SIZE_IN_TILES],
                             const Tetromino::Color shapeColor)
{
    int offsetX = rand() % (FIELD_WIDTH - 1);
    for (int i = 0; i < Tetromino::SHAPE_SIZE_IN_TILES; ++i)
    {
        if (field[shape[i].y][shape[i].x + offsetX] != Tetromino::EMPTY)
            return false;
        field[shape[i].y][shape[i].x + offsetX] = shapeColor;
        shape[i].x += offsetX;
    }
    return true;
}


bool Game::canPlaceShapeAtPosition(const Position 
                                   shape[Tetromino::SHAPE_SIZE_IN_TILES]) const
{
    for (int i = 0; i < Tetromino::SHAPE_SIZE_IN_TILES; ++i)
    {
        if (shape[i].y >= FIELD_HEIGHT ||
            shape[i].x >= FIELD_WIDTH ||
            shape[i].x < 0 ||
            field[shape[i].y][shape[i].x] != Tetromino::EMPTY)
        {
            return false;
        }
    }
    return true;
}


bool Game::moveShape(Position shape[Tetromino::SHAPE_SIZE_IN_TILES],
                     const Tetromino::Color shapeColor,
                     const int offsetX, const int offsetY)
{
    Position nextShape[Tetromino::SHAPE_SIZE_IN_TILES];
    for (int i = 0; i < Tetromino::SHAPE_SIZE_IN_TILES; ++i)
    {
        field[shape[i].y][shape[i].x] = Tetromino::EMPTY;
        nextShape[i] = Position(shape[i].x + offsetX, shape[i].y + offsetY);
    }

    if (canPlaceShapeAtPosition(nextShape))
    {
        for (int i = 0; i < Tetromino::SHAPE_SIZE_IN_TILES; ++i)
        {
            field[nextShape[i].y][nextShape[i].x] = shapeColor;
            shape[i] = nextShape[i];
        }
        return true;
    }

    for (int i = 0; i < Tetromino::SHAPE_SIZE_IN_TILES; ++i)
    {
        field[shape[i].y][shape[i].x] = shapeColor;
    }
    return false;
}


void Game::drawField(sf::RenderWindow& window)
{
    for (int i = 0; i < FIELD_HEIGHT; ++i)
    {
        for (int j = 0; j < FIELD_WIDTH; ++j)
        {
            if (field[i][j] != Tetromino::EMPTY)
            {
                tetromino.drawTile(window, field[i][j], Position(j + 1, i + 1));
            }
        }
    }
}