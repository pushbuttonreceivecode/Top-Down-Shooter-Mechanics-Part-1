#include <iostream>
#include <SFML/Graphics.hpp>
#include <GeneralUtilities.hpp>

sf::Vector2f direction(sf::RectangleShape& follower, sf::Vector2f target);

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(800,600,32), "Follow me!!", sf::Style::Default);
    sf::Event e;

    sf::RectangleShape player;
    player.setFillColor(sf::Color(200,0,0,255));
    player.setSize(sf::Vector2f(50.f,50.f));
    player.setPosition(window.getSize().x/2.f, window.getSize().y - player.getLocalBounds().height);

    sf::RectangleShape enemy;
    enemy.setFillColor(sf::Color(0,200,0,255));
    enemy.setSize(sf::Vector2f(50.f,50.f));
    enemy.setPosition(0.f, enemy.getLocalBounds().height);

    sf::Font myfont;
    if(!myfont.loadFromFile("resources/fonts/contb.ttf"))
    {
        std::cerr<<"Could not load font"<<std::endl;
    }

    sf::Text status("Chasing....", myfont);
    status.setPosition(window.getSize().x/2.f, 0.f);
    status.setCharacterSize(32);
    status.setColor(sf::Color(200,100,0,255));

    sf::Time timePerFrame = sf::seconds(1.f/60.f);
    sf::Clock clock;
    sf::Time timeElapsed = sf::Time::Zero;
    sf::Time duration = sf::Time::Zero;

    while(window.isOpen())
    {
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }

            if(e.type == sf::Event::KeyPressed)
            {
                switch(e.key.code)
                {
                case sf::Keyboard::Escape:
                    {
                        window.close();
                        return 0;
                    }
                    break;

                case sf::Keyboard::Left:
                {
                    player.move(-10.f,0.f);
                }
                break;

                case sf::Keyboard::Right:
                {
                    player.move(10.f,0.f);
                }
                break;

                case sf::Keyboard::Up:
                {
                    player.move(0.f,-10.f);
                }
                break;

                case sf::Keyboard::Down:
                {
                    player.move(0.f,10.f);
                }
                break;

                default:
                    break;
                }
            }
        }

        timeElapsed += clock.restart();
        while (timeElapsed > timePerFrame)
        {
            timeElapsed -= timePerFrame;

            //update position of follower

            sf::Vector2f target = direction(enemy,player.getPosition());
            sf::Vector2f velocity = unitVector(sf::Vector2f(timePerFrame.asSeconds() + target.x, timePerFrame.asSeconds() + target.y));
            float angle = std::atan2(velocity.y, velocity.x);

            velocity *= 2.f;

            if(enemy.getPosition().y >= player.getPosition().y
               && enemy.getPosition().y < player.getPosition().y + player.getLocalBounds().height
               && enemy.getPosition().x >= player.getPosition().x
               && enemy.getPosition().x < player.getPosition().x + player.getLocalBounds().width)
                status.setString("Gotcha!");
            else
            {
                enemy.move(velocity);
                enemy.setRotation(toDegree(angle) + 90.f);
                status.setString("Chasing....");
            }
        }

        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.draw(status);
        window.display();
    }
    return 0;
}

sf::Vector2f direction(sf::RectangleShape& follower, sf::Vector2f target)
{
    return unitVector(sf::Vector2f(target - follower.getPosition()));
}
