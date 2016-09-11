#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>//
#include <stdlib.h>//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "config.h"

#define MY_MIN(a,b) ((a) < (b) ? (a) : (b))
#define MY_MAX(a,b) ((a) > (b) ? (a) : (b))

sf::Vector2f convertPositionToWindowCoordonates(sf::RenderWindow& window, sf::Vector2f position);

sf::Vector2f getCircleCenter(float radius);
sf::Vector2f getRectangleCenter(sf::Vector2f rectangle);

sf::CircleShape getCircleShapeForWindow(sf::RenderWindow& window, float radius, sf::Vector2f position);
sf::RectangleShape getRectangleShapeForWindow(sf::RenderWindow& window, sf::Vector2f rectangle, sf::Vector2f position);

#endif // TOOLS_H
