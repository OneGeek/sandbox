#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include "voronoi.h"
#include "constants.h"
#include "geom.h"

using namespace std;
using namespace sf;
using Voronoi::Site;




class TerraVerse {
public:
    RenderWindow& window;
    bool isRunning;

    TerraVerse();
    void setup();
    void run();
    void processEvents();
    void handleKeyPress(Event::KeyEvent);

private:
    Event event;
    vector<shared_ptr<Shape>> shapes;
};

TerraVerse::TerraVerse()
:window(*(new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "TerraVerse")))
{}

void TerraVerse::processEvents() {
    while (window.GetEvent(event)) {

        switch(event.Type) {

            case Event::Closed:
                window.Close();
                break;

            case Event::KeyPressed:
                handleKeyPress(event.Key);
                break;

            default:
                break;
        }
    }
}

void TerraVerse::handleKeyPress(Event::KeyEvent key)
{
    if (key.Code == Key::Code::Escape) {
        window.Close();
    }
    printf("Key Pressed: %d\n", key.Code);
}

void TerraVerse::setup()
{
    Voronoi::Diagram diagram;

    for (int i=0; i < NUMBER_OF_SITES; i++) {
        int x = rand() % (WINDOW_WIDTH - 100) + 50;
        int y = rand() % (WINDOW_HEIGHT - 100) + 50;

        diagram.addSite(make_shared<Site>(x, y));
    }

    for (auto iter=diagram.sites.begin(); iter != diagram.sites.end(); iter++) {

                auto site = *iter;
                //printf("%d, %d\n", site->position.x, site->position.y);


                auto shape(make_shared<Shape>(
                    Shape::Circle(
                        site->position.x,
                        site->position.y,
                        3, // radius
                        Color::Green,
                        1.0f, // outline
                        Color::Black // outline color

                    )));


                shapes.push_back(shape);
    }


    //diagram.generate();
}

int x = 0;
geom::Parabola parabola = {geom::Vector2D(300, 300), 299};

void TerraVerse::run() {
    setup();


    while (window.IsOpened())
    {
        processEvents();

        window.Clear(Color::White);

        for (auto iter = shapes.begin(); iter != shapes.end(); iter++) {
            auto shape = **iter;
            window.Draw(shape);
        }

        if (x < WINDOW_WIDTH) {

            x+=1;

            auto p = geom::pointOnParabola(parabola, x);
            //printf("%d: %f, %f \n", x, p.x, p.y);
            shapes.push_back(make_shared<Shape>(
                Shape::Circle(
                    p.x, p.y,
                    0.8f, // radius,
                    Color::Black
            )));
        }



        window.Display();
    }

}

int main()
{
    TerraVerse terraverse;
    terraverse.run();
    return EXIT_SUCCESS;
}
