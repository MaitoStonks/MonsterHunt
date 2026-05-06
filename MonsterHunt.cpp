#include <SFML/Graphics.hpp>



class Weapon {
public:
    int damage;
};

class Enemy {
public: 
    int health;
    float speed;
    int damage;

    
};

class Werewolf : public Enemy {
public:
    Werewolf() {
        speed = 50.0f;
    }
};

class Player {

public:
    int position = 0;
    float speed = 200.0f;
    
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Monster Hunt");
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Images/player.png");
    sf::Sprite player(playerTexture);

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Images/ghost.png");
    sf::Sprite enemy(enemyTexture);

    sf::Clock clock;
    Player p;
    


    while (window.isOpen())
    {
        sf::Time lastFrame = clock.restart();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        sf::Vector2f vPlayerMovement(0.0f, 0.0f);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            vPlayerMovement += sf::Vector2f(0.0f, -1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            vPlayerMovement += sf::Vector2f(-1.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            vPlayerMovement += sf::Vector2f(0.0f, 1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            vPlayerMovement += sf::Vector2f(1.0f, 0.0f);
        }

        player.move(vPlayerMovement*lastFrame.asSeconds() * p.speed);
        

        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.display();
    }
}