#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace sf;
using namespace std;

// ---------------- BULLET ----------------
class Bullet {
public:
    RectangleShape shape;
    float speed = 7.f;

    Bullet(float x, float y) {
        shape.setSize(Vector2f(5, 15));
        shape.setFillColor(Color::Yellow);
        shape.setPosition(x, y);
    }

    void update() {
        shape.move(0, -speed);
    }
};

// ---------------- BOMB ----------------
class Bomb {
public:
    CircleShape shape;
    float speed = 4.f;

    Bomb(float x, float y) {
        shape.setRadius(6);
        shape.setFillColor(Color::Red);
        shape.setPosition(x, y);
    }

    void update() {
        shape.move(0, speed);
    }
};

// ---------------- ENEMY ----------------
class Enemy {
public:
    RectangleShape shape;
    float speed = 2.f;
    int dropTimer = 0;

    Enemy(float y) {
        shape.setSize(Vector2f(50, 25));
        shape.setFillColor(Color::Cyan);
        shape.setPosition(-60, y);
    }

    void update() {
        shape.move(speed, 0);
        dropTimer++;
    }

    bool canDropBomb() {
        return dropTimer > 120 && rand() % 100 < 2;
    }
};

// ---------------- PLAYER ----------------
class Player {
public:
    RectangleShape shape;
    float speed = 6.f;
    int energy = 100;

    Player() {
        shape.setSize(Vector2f(60, 25));
        shape.setFillColor(Color::Green);
        shape.setPosition(370, 550);
    }

    void moveLeft() {
        if (shape.getPosition().x > 0)
            shape.move(-speed, 0);
    }

    void moveRight() {
        if (shape.getPosition().x + shape.getSize().x < 800)
            shape.move(speed, 0);
    }
};

// ---------------- GAME ----------------
int main() {
    srand(time(nullptr));
    RenderWindow window(VideoMode(800, 600), "SPACE INVADER");
    window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("arial.ttf"); // place arial.ttf in folder

    Player player;
    vector<Bullet> bullets;
    vector<Enemy> enemies;
    vector<Bomb> bombs;

    int score = 0;
    Clock enemySpawnClock;

    // Energy bar
    RectangleShape energyBarBack(Vector2f(200, 20));
    energyBarBack.setFillColor(Color(50, 50, 50));
    energyBarBack.setPosition(10, 10);

    RectangleShape energyBar(Vector2f(200, 20));
    energyBar.setFillColor(Color::Green);
    energyBar.setPosition(10, 10);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(18);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(600, 10);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // -------- INPUT --------
        if (Keyboard::isKeyPressed(Keyboard::Left))
            player.moveLeft();

        if (Keyboard::isKeyPressed(Keyboard::Right))
            player.moveRight();

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (bullets.size() < 10) {
                bullets.emplace_back(
                    player.shape.getPosition().x + 27,
                    player.shape.getPosition().y
                );
            }
        }

        // -------- SPAWN ENEMY --------
        if (enemySpawnClock.getElapsedTime().asSeconds() > 1.5f) {
            enemies.emplace_back(rand() % 400 + 50);
            enemySpawnClock.restart();
        }

        // -------- UPDATE BULLETS --------
        for (auto &b : bullets) b.update();

        // -------- UPDATE ENEMIES --------
        for (auto &e : enemies) {
            e.update();
            if (e.canDropBomb()) {
                bombs.emplace_back(
                    e.shape.getPosition().x + 20,
                    e.shape.getPosition().y + 20
                );
            }
        }

        // -------- UPDATE BOMBS --------
        for (auto &bomb : bombs) bomb.update();

        // -------- COLLISIONS --------
        // Bullet vs Enemy
        for (size_t i = 0; i < bullets.size(); i++) {
            for (size_t j = 0; j < enemies.size(); j++) {
                if (bullets[i].shape.getGlobalBounds().intersects(
                        enemies[j].shape.getGlobalBounds())) {
                    bullets.erase(bullets.begin() + i);
                    enemies.erase(enemies.begin() + j);
                    score += 10;
                    goto skip;
                }
            }
        }
        skip:;

        // Bomb vs Player
        for (size_t i = 0; i < bombs.size(); i++) {
            if (bombs[i].shape.getGlobalBounds().intersects(
                    player.shape.getGlobalBounds())) {
                bombs.erase(bombs.begin() + i);
                player.energy -= 20;
                if (player.energy < 0) player.energy = 0;
            }
        }

        // -------- ENERGY BAR UPDATE --------
        energyBar.setSize(Vector2f(2 * player.energy, 20));

        // -------- GAME OVER --------
        if (player.energy <= 0) {
            window.close();
        }

        scoreText.setString("Score : " + to_string(score));

        // -------- RENDER --------
        window.clear();
        window.draw(player.shape);

        for (auto &b : bullets) window.draw(b.shape);
        for (auto &e : enemies) window.draw(e.shape);
        for (auto &bomb : bombs) window.draw(bomb.shape);

        window.draw(energyBarBack);
        window.draw(energyBar);
        window.draw(scoreText);

        window.display();
    }
    return 0;
}
