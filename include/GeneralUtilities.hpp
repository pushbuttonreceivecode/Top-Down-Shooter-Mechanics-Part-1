#ifndef GENERALUTILITIES_HPP
#define GENERALUTILITIES_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <sstream>
#include <random>
#include <cmath>
#include <ctime>
#include <cassert>

// Call setOrigin() with the center of the object
void			centerOrigin(sf::Sprite& sprite);
void			centerOrigin(sf::Text& text);

// Degree/radian conversion
float			toDegree(float radian);
float			toRadian(float degree);

// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);

#endif // GENERALUTILITIES_HPP
