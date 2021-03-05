#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <chrono>


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using std::vector;
using std::cout;
using std::endl;

//Global variables---------------------
unsigned int height = 1500;
unsigned int width = 2000;
unsigned int population = 20;
float base_size = 100;
float energy = 100;

//Global functions---------------------
float distance(float x1, float y1, float x2, float y2){
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//Base class--------------------------------------------------------
class Base{
public:
    sf::RectangleShape picture;
    int x, y;
    float  size;
    Base(int x_, int y_){
        this->x = x_;
        this->y = y_;
    }
};

vector<Base> bases;

//Animal class--------------------------------------------------------
class Animal
{
};


//Game class--------------------------------------------------------
class Game
{
private:
    //Private variables
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    //Game objects
    sf::RectangleShape cursor;
    sf::RectangleShape energy_lvl;
    sf::Text energy_lvl_caption;

    //Private functions
    void initVariables();
    void initWindow();
    void initCursor();
    void initEnergy_lvl();
public:
    //Public functions
    Game();
    void initBase();
    virtual ~Game();

    const bool running() const;
    void pollEvents();
    void update();
    void render();
};

//Functions definitions:
void Game::initVariables() {
    this->window = nullptr;
}

void Game::initWindow() {
    this->videoMode.height = height;
    this->videoMode.width = width;
    this->window = new sf::RenderWindow(this->videoMode, "Chillness 1.1.1", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(40);

}

Game::~Game() {
    delete this->window;
}

Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initCursor();
    this->initEnergy_lvl();
}

const bool Game::running() const {
    return this->window->isOpen();
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev))
    {
        switch(this->ev.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (this->ev.mouseButton.button == sf::Mouse::Left) {
                    this->initBase();
                    }
                break;

        }
    }
}

void Game::update() {
    this->pollEvents();
    int x_mouse, y_mouse;
    x_mouse = sf::Mouse::getPosition(*this->window).x;
    y_mouse = sf::Mouse::getPosition(*this->window).y;
    if (x_mouse >= 0 and y_mouse >= 0 and x_mouse <= this->videoMode.width and y_mouse <= this->videoMode.height){
        this->cursor.setFillColor(sf::Color::Red);
        this->cursor.setPosition(x_mouse, y_mouse);

        this->energy_lvl.setSize(sf::Vector2(energy*10, 20.f));


    }
    else this->cursor.setFillColor(sf::Color::Green);
}

void Game::render() {
    this->window->clear(sf::Color(40, 10, 40, 255));
    this->window->draw(this->cursor);
    this->window->draw(this->energy_lvl);
    this->window->draw(this->energy_lvl_caption);
    for(int i = 0; i < bases.size(); i++) this->window->draw(bases[i].picture);
    this->window->display();
}

void Game::initCursor() {
    this->cursor.setSize(sf::Vector2(20.f, 20.f));
    this->cursor.setFillColor(sf::Color::Magenta);
    this->cursor.setOutlineColor(sf::Color::Green);
    this->cursor.setOutlineThickness(1.f);
    this->cursor.setOrigin(sf::Vector2(5.f, 5.f));
}

public void Game::initEnergy_lvl() {
    this->energy_lvl.setPosition(10, 1300);
    this->energy_lvl.setSize(sf::Vector2(energy*10, 20.f));
    this->energy_lvl.setFillColor(sf::Color::Green);
    this->energy_lvl.setOrigin(sf::Vector2(5.f, 5.f));
    this->energy_lvl_caption.setCharacterSize(10);
    this->energy_lvl_caption.setFont(sf::Font::loadFromFile("20326.otf"))
    this->energy_lvl_caption.setPosition(10, 1200);
    this->energy_lvl_caption.setFillColor(sf::Color::White);
    this->energy_lvl_caption.setString("Egor's dick");
}

void Game::initBase() {
    bool nearby = false;
    float x_, y_;
    x_ = sf::Mouse::getPosition(*this->window).x;
    y_ = sf::Mouse::getPosition(*this->window).y;
    for(int i = 0; i < bases.size(); i++){
        if(distance(x_, y_, bases[i].x, bases[i].y) < base_size*2) nearby = true;
    }
    if (nearby == false and energy >= 10) {
        energy -= 10;
        Base b = Base(x_, y_);
        b.size = base_size;
        b.picture.setPosition(b.x, b.y);
        b.picture.setSize(sf::Vector2(b.size, b.size));
        b.picture.setFillColor(sf::Color::Yellow);
        b.picture.setOrigin(b.size / 2, b.size / 2);
        bases.push_back(b);
    }
}

//------------------------------------------------------GAME LOOP-------------------------------------------------------
int main() {
//Init Game
    Game game;
//Game loop
    while(game.running())
    {
//Update
        game.update();
//Render
        game.render();
    }
    return 0;
}
