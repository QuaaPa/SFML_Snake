#include <SFML/Graphics.hpp>

#include <time.h>
#include <iostream>
#include <windows.h>
#include <sstream>

int N = 30, M = 20;
int ts = 25;

int dir = 2, num = 4;

bool game = true;
bool gameOver = false;

struct Snake
{
    int x, y;
} s[600];

struct Apple
{
    int x, y;
} f;


void Tick()
{
    for(int i = num; i > 0; i--)
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }
    if(dir == 0)
        s[0].y += 1;
    if(dir == 1)
        s[0].x -= 1;
    if(dir == 2)
        s[0].x += 1;
    if(dir == 3)
        s[0].y -= 1;

    if(s[0].x < 0)
        s[0].x = N - 1;
    if(s[0].x > N - 1)
        s[0].x = 0;
    if(s[0].y < 0)
        s[0].y = M - 1;
    if(s[0].y > M - 1)
        s[0].y = 0;

    if((s[0].x == f.x) && (s[0].y == f.y))
    {
        num++;
        f.x = rand() % N;
        f.y = rand() % M;
    }

    for(int i = 1; i < num; i++)
    {
        if(s[0].x == s[i].x && s[0].y == s[i].y)
        {
            game = false;
            break;
        }
    }
}

int main()
{

    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(ts * N, ts * M), "Snake");

    sf::Texture textureT;
    textureT.loadFromFile("resources/Paint/tiles.png");
    sf::Sprite spriteT;
    spriteT.setTexture(textureT);

    sf::Texture textureS;
    textureS.loadFromFile("resources/Paint/snake.png");
    sf::Sprite snake;
    snake.setTexture(textureS);

    sf::Texture textureA;
    textureA.loadFromFile("resources/Paint/apple.png");
    sf::Sprite apple;
    apple.setTexture(textureA);

    sf::Texture textureG;
    textureG.loadFromFile("resources/Paint/gameover.png");
    sf::Sprite gameover;
    gameover.setTexture(textureG);
    gameover.setPosition(0, 175);


    f.x = 10;
    f.y = 10;

    sf::Clock clockSnake;
    float timer = 0, delay = 0.115;

    sf::Clock clock;

    while (window.isOpen())
    {
        float time = clockSnake.getElapsedTime().asSeconds();
        clockSnake.restart();
        timer += time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            dir = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            dir = 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            dir = 2;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            dir = 3;

        if(timer > delay && game == true)
        {
            timer = 0;
            Tick();
        }


        window.clear();
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
                spriteT.setPosition(i * ts, j * ts);
                window.draw(spriteT);
            }
        }

        for(int i = 0; i < num; i++)
        {
            if(i != 0)
                snake.setTextureRect(sf::IntRect(0, 0, ts, ts));
            else
                snake.setTextureRect(sf::IntRect(dir * ts, ts, ts, ts));

            if(!game && i == 1)
            {
                snake.setTextureRect(sf::IntRect(dir * ts, ts * 2, ts, ts));
            }

            snake.setPosition(s[i].x * ts, s[i].y * ts);
            window.draw(snake);
        }
        apple.setPosition(f.x * ts, f.y * ts);
        window.draw(apple);

        if(!game && gameOver == false)
        {
            gameOver = true;
            clock.restart();
        }
        if(!game && gameOver == true)
            window.draw(gameover);
        if(gameOver = true && game == false)
        {
            if(clock.getElapsedTime().asSeconds() > 2)
            {
                num = 4;
                f.x = 10;
                f.y = 10;
                game = true;
                gameOver = false;
                clock.restart();
            }
        }

        window.setTitle("Score: " + std::to_string(num - 4));

        window.display();
    }

    return 0;
}