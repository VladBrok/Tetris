#include "game.h"


int main()
{
    try
    {
        Game tetris;
        tetris.run();
    }
    catch (const std::runtime_error&)
    {
        return -1;
    }

    return 0;
};
