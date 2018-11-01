#include "Model.h"

#include "SFML/Graphics.hpp"

/**
 *
 */
void Model::renderModell(sf::RenderWindow &window)
{
    int i = 0;
    Face f;
    Vector3d ver1,ver2,ver3;

    int tx = window.getSize().x/20;
    int ty = window.getSize().y/4;

    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Red;
    triangle[2].color = sf::Color::Red;

    for(i = 0; i<faceCount; i++)
    {
        f = faceTable[i];
        ver1 = vertexViewTable[f.v0];
        ver2 = vertexViewTable[f.v1];
        ver3 = vertexViewTable[f.v2];

        triangle[0].position = sf::Vector2f(ver1.x + tx,ver1.y + ty);
        triangle[1].position = sf::Vector2f(ver2.x + tx,ver2.y + ty);
        triangle[2].position = sf::Vector2f(ver3.x + tx,ver3.y + ty);

        window.draw(triangle);
    }
}
