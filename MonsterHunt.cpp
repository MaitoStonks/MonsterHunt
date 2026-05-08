#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "imgui.h"


sf::Vector2f Normalise(const sf::Vector2f& rVector) {
    float fLength = sqrt(rVector.x * rVector.x + rVector.y * rVector.y);
    if (fLength != 0) {
        sf::Vector2f vNormalisedVector(rVector.x / fLength, rVector.y / fLength);
        return vNormalisedVector;
    }
    return sf::Vector2f(0.0f, 0.0f);
};

sf::Vector2f EnemySpawn(sf::Vector2u windowSize) {
    static std::random_device rd;  
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> edge_spawn(1,4);
    int edge = edge_spawn(gen);
    switch (edge) {
    case 1: {
        std::uniform_int_distribution<> random_x(-50, 0);
        std::uniform_int_distribution<> random_y(0, windowSize.y);
        return sf::Vector2f(random_x(gen), random_y(gen));
    }
    case 2: {
        std::uniform_int_distribution<> random_x(0, windowSize.x);
        std::uniform_int_distribution<> random_y(-50, 0);
        return sf::Vector2f(random_x(gen), random_y(gen));
    }
    case 3: {
        std::uniform_int_distribution<> random_x(windowSize.x, windowSize.x + 50);
        std::uniform_int_distribution<> random_y(0, windowSize.y);
        return sf::Vector2f(random_x(gen), random_y(gen));
    }

    case 4: {
        std::uniform_int_distribution<> random_x(0, windowSize.x);
        std::uniform_int_distribution<> random_y(windowSize.y, windowSize.y + 50);
        return sf::Vector2f(random_x(gen), random_y(gen));
    }
    }
}

class Weapon {
public:
    int damage;
};

class Enemy {
public:

    int health;
    float speed;
    int damage;
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite enemySprite;
    Enemy(const std::string& path)
        : texture(path), enemySprite(texture)
    {
    }
};


class Werewolf : public Enemy {
public:
    Werewolf() : Enemy("Images/werewolf.png"){
        speed = 700.0f;
        health = 200;
        damage = 20;
        position = sf::Vector2f(960, 540);
    }
};

class Zombie : public Enemy {
public:
    Zombie() : Enemy("Images/zombie.png") {
        speed = 300.0f;
        health = 200;
        damage = 10;
        position = sf::Vector2f(960, 540);
    }
};

class Ghost : public Enemy {
public:
    Ghost() : Enemy("Images/ghost.png") {
        speed = 500.0f;
        health = 200;
        damage = 5;
        position = sf::Vector2f(960, 540);
    }
};

class Player {

public:
    float speed = 800.0f;
    int health = 100;
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite playerSprite;
    Player() : 
        texture("Images/player.png"),
        playerSprite(texture)
    {
    }
    
};



int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Monster Hunt", sf::State::Fullscreen);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Images/player.png");
    sf::Sprite player(playerTexture);

    sf::Clock clock;
    Player player1;
    sf::Font font("assets/LuxuriousRoman-Regular.ttf");
    
    
    std::vector<sf::CircleShape> bullets;
    std::vector<std::unique_ptr<Enemy>> enemies;
    enemies.push_back(std::make_unique<Werewolf>());
    enemies.push_back(std::make_unique<Zombie>());
    enemies.push_back(std::make_unique<Ghost>());

    sf::Text Hp(font);
    Hp.setFillColor(sf::Color::Red);
    Hp.setCharacterSize(100);
    Hp.setPosition({ 50, 10 });

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
        player.move(vPlayerMovement * lastFrame.asSeconds() * player1.speed);


        
        // sets a rectangular boundry that holds the player sprite, ensuring it cant move off the window
        sf::Vector2f position = player.getPosition();
        sf::Vector2u windowSize = window.getSize();
        sf::FloatRect bounds = player.getGlobalBounds();
        position.x = std::clamp(position.x, 0.f, windowSize.x - bounds.size.x);
        position.y = std::clamp(position.y, 0.f, windowSize.y - bounds.size.y);
        player.setPosition(position);


        
        /*if (sf::Event::MouseButtonPressed(sf::Mouse::Button::Left)) {
            bullets.push_back(sf::CircleShape());
            bullets.back().setRadius(5);
            bullets.back().setPosition(player.getPosition());
        }

        sf::Vector2f bulletMove =
            window.mapPixelToCoords(sf::Mouse::getPosition(window))
            - bullets.back().getPosition();
        bulletMove = Normalise(bulletMove);*/

        /*for (int i = 0; i < bullets.size(); i++) {
            window.draw(bullets[i]);
            bullets[i].move(bulletMove * lastFrame.asSeconds() * 900.0f);
            
        }*/
        window.clear(sf::Color::Cyan);
        if (enemies.size() != 0) {
            for (int i = 0; i < enemies.size(); i++) {
                window.draw(enemies[i]->enemySprite);
                sf::Vector2f vEnemyMove = player.getPosition() - enemies[i]->enemySprite.getPosition();
                vEnemyMove = Normalise(vEnemyMove);
                enemies[i]->enemySprite.move(vEnemyMove * lastFrame.asSeconds() * enemies[i]->speed);
            }
            for (int i = 0; i < enemies.size(); i++) {
                if (enemies[i]->enemySprite.getGlobalBounds().findIntersection(player.getGlobalBounds())) {
                    player1.health = player1.health - enemies[i]->damage;
                    enemies[i]->enemySprite.setPosition(EnemySpawn(windowSize));
                }
            }
        }
        Hp.setString(std::to_string(player1.health));
        window.draw(Hp);
        window.draw(player);
        window.display();
    }
}


