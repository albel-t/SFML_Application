#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

#define MaxSpeed 5

#define MaxClarity 255

#define MaxRadius 10
#define MinRadius 3

#define MaxX 800

#define MaxY 600



int random( int max, int min = 1)
{
    return std::rand() % (max-min) + min;
}

void drawDisplay(sf::RenderWindow* window, std::vector<std::pair<sf::CircleShape*, double>> drops)
{
    for (auto drop : drops)
    {
        if (drop.first)
        {
            window->draw(*(drop.first));
        }
    }
}

struct dynamicParam
{
    double x, radius, clarity, speed;
    dynamicParam()
    {
        radius = random(MaxRadius, MinRadius);
        x = random(MaxX);
        clarity = radius * MaxClarity / MaxRadius / 2 + 128;
        speed = radius * MaxSpeed / MaxRadius + 1;
    }
};

std::pair<sf::CircleShape*, double> createCircle(dynamicParam circleParam)
{
    sf::CircleShape* circle = new sf::CircleShape;
    circle->setRadius(circleParam.radius);
    circle->setFillColor(sf::Color(23,126,199, circleParam.clarity));
    circle->setScale(0.1, 1);
    circle->setPosition(circleParam.x, -10);
    circle->move(0, circleParam.speed);

    return std::make_pair(circle, circleParam.speed);
}

void OneTick(std::vector<std::pair<sf::CircleShape*, double>>& drops)
{
    for (auto& drop : drops)
    {
        if (drop.first == nullptr)
        {
            dynamicParam p;
            drop = createCircle(p);
            continue;
        }
        if(drop.first->getPosition().y > MaxY)
        {
            delete drop.first;
            drop.first = nullptr;
            continue;
        }

        drop.first->move(0, drop.second);

    }
}





int main()
{
    // Declare and create a new render-window
    sf::RenderWindow window(sf::VideoMode(MaxX, MaxY), "SFML window");

    // Limit the framerate to 60 frames per second (this step is optional)
    window.setFramerateLimit(60);
    std::vector<std::pair<sf::CircleShape*, double>> drops(1000);

    // The main loop - ends as soon as the window is closed
    while (window.isOpen())
    {
        // Event processing
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                window.close();
                window.clear();
        }

        // Clear the whole window before rendering a new frame
        window.clear();


        OneTick(drops);
        drawDisplay(&window, drops);

        // Draw some graphical entities
        //window.draw(sprite);
        //window.draw(circle);
        //window.draw(text);

        // End the current frame and display its contents on screen
        window.display();
    }
} 
