#include "main.h"
#include <windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({600, 600}), "SnakeGame\t\t\t github: Flartks/snakegame");

    // define the level with an array of tile indices
    constexpr std::array level = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };    
    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("tileset.png", {50, 50}, level.data(), 12, 12))
        return -1;

    sf::Texture playerT("images/snake.png", false, sf::IntRect({0, 0}, {50, 50}));
    sf::Sprite player(playerT);
    int direction = 4;
    float pos[] = {0.f, 0.f};

    sf::Clock clock;
    sf::Time moveDelay = sf::milliseconds(300);

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // input wasd
        char keyChar = ' ';
        for (int keyCode = 0; keyCode < 256; ++keyCode) {
            if (GetAsyncKeyState(keyCode) & 0x8000) {
                keyChar = static_cast<char>(keyCode);
            }
        }

        // move player
        if(keyChar != ' ') {
            switch (keyChar) {
                case 'W':
                    direction = 1;
                    break;
                case 'A':
                    direction = 2; 
                    break;
                case 'S':
                    direction = 3;
                    break;
                case 'D':
                    direction = 4;
                    break;
            }
        }

        if (clock.getElapsedTime() > moveDelay) {
            switch(direction) {
                case 1:
                    if(pos[1] > 0.f) {
                        player.move({0.f, -50.f});
                        pos[1] -=50.f;
                    }
                    break;
                case 2:
                    if(pos[0] > 0.f) {
                        player.move({-50.f, 0.f});
                        pos[0] -=50.f;
                    }
                    break;
                case 3:
                    if(pos[1] < 550.f) {
                        player.move({0.f, 50.f});
                        pos[1] += 50.f;
                    }
                    break;
                case 4:
                    if(pos[0] < 550.f) {
                        player.move({50.f, 0.f});
                        pos[0] += 50.f;
                    }
                    break;
            }
            clock.restart();
        }

        // draw 
        window.clear();
        window.draw(map);
        window.draw(player);
        window.display();
    }
}
