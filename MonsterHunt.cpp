#include <SFML/Graphics.hpp>
#include <iostream>



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
    float speed = 800.0f;
    
};


//bool validMove(sf::Vector2f& vPlayerMovement, sf::RenderWindow& window) {
//    sf::Vector2u windowsize = window.getSize();
//
//
//    if (vPlayerMovement.x >= 0 && vPlayerMovement.y >= 0 && vPlayerMovement.x <= windowsize.x  && vPlayerMovement.y <= windowsize.y) {
//        return true;
//    }
//    return false;
//};

sf::Vector2f Normalise(const sf::Vector2f& rVector) {
        float fLength = sqrt(rVector.x * rVector.x + rVector.y * rVector.y);
        if (fLength != 0) {
            sf::Vector2f vNormalisedVector(rVector.x / fLength, rVector.y / fLength);
            return vNormalisedVector;
        }
        return sf::Vector2f(0.0f, 0.0f);
    };

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Monster Hunt", sf::State::Fullscreen);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Images/player.png");
    sf::Sprite player(playerTexture);

    sf::Texture enemyTexture2;
    enemyTexture2.loadFromFile("Images/zombie.png");
    sf::Sprite enemy2(enemyTexture2);
    enemy2.setPosition(sf::Vector2f(960, 540));

    sf::Texture enemyTexture3;
    enemyTexture3.loadFromFile("Images/werewolf.png");
    sf::Sprite enemy3(enemyTexture3);
    enemy3.setPosition(sf::Vector2f(960, 540));

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Images/ghost.png");
    sf::Sprite enemy(enemyTexture);
    enemy.setPosition(sf::Vector2f(960, 540));

    sf::Clock clock;
    Player p;
    


    while (window.isOpen())
    {
        sf::Time lastFrame = clock.restart();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) // button closes the game
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
       
        vPlayerMovement = Normalise(vPlayerMovement);
        player.move(vPlayerMovement * lastFrame.asSeconds() * p.speed);


        sf::Vector2f vEnemyMove = player.getPosition() - enemy.getPosition();
        vEnemyMove = Normalise(vEnemyMove);
        enemy.move(vEnemyMove * lastFrame.asSeconds() * 600.0f);

        sf::Vector2f vEnemyMove2 = player.getPosition() - enemy2.getPosition();
        vEnemyMove2 = Normalise(vEnemyMove2);
        enemy2.move(vEnemyMove2 * lastFrame.asSeconds() * 200.0f);

        sf::Vector2f vEnemyMove3 = player.getPosition() - enemy3.getPosition();
        vEnemyMove3 = Normalise(vEnemyMove3);
        enemy3.move(vEnemyMove3 * lastFrame.asSeconds() * 900.0f);


        
        // sets a rectangular boundry that holds the player sprite, ensuring it cant move off the window
        sf::Vector2f position = player.getPosition();
        sf::Vector2u windowSize = window.getSize();
        sf::FloatRect bounds = player.getGlobalBounds();
        position.x = std::clamp(position.x, 0.f, windowSize.x - bounds.size.x);
        position.y = std::clamp(position.y, 0.f, windowSize.y - bounds.size.y);
        player.setPosition(position);

        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.draw(enemy2);
        window.draw(enemy3);
        window.display();
    }
}


