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
//Cell class--------------------------------------------------------
class Animal
{
public:
    int x;
    int y;
    int x_stable;
    int y_stable;

public:
    sf::CircleShape picture;

    Animal(){
        this->x = 0;
        this->y = 0;
        this->x_stable = 0;
        this->y_stable = 0;
    };

    void set_position(int a, int b){
        this->x = a;
        this->y = b;
        picture.setPosition(a, b);
    }

    void set_stable_position(int a, int b){
        this->x_stable = a;
        this->y_stable = b;
    }
};

//Definition for functions---------------


//Game class--------------------------------------------------------
class Game
{
private:
    //Private variables
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    //Game objects
    sf::RectangleShape enemy;

    //Private functions
    void initVariables();
    void initWindow();
    void initEnemies();
public:
    //Public functions
    Game();
    virtual ~Game();

    const bool running() const;
    void pollEvents();
    vector<Animal> update(vector<Animal> group);
    void render(vector <Animal> group);
};
//------------------------------------------------------------------


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
    this->initEnemies();
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

        }
    }
}

vector<Animal> Game::update(vector<Animal> group) {
    this->pollEvents();
    int x_mouse, y_mouse;
    x_mouse = sf::Mouse::getPosition(*this->window).x;
    y_mouse = sf::Mouse::getPosition(*this->window).y;
    //std::cout << "Mouse: " << x_mouse << " " << y_mouse << std::endl;
    if (x_mouse >= 0 and y_mouse >= 0 and x_mouse <= this->videoMode.width and y_mouse <= this->videoMode.height){
        this->enemy.setFillColor(sf::Color::Red);
        this->enemy.setPosition(x_mouse, y_mouse);

    }
    else this->enemy.setFillColor(sf::Color::Green);

    for(int i = 0; i < population; i++){
        group[i].set_position(group[i].x_stable + 10*sin(ceil(clock()/2000)), group[i].y_stable + 10*sin(ceil(clock()/1500 + i)));
    }
    return group;
}

void Game::render(vector<Animal> group) {

    this->window->clear(sf::Color(40, 10, 40, 255));
    this->window->draw(this->enemy);
    for (int i = 0; i < population; i++){

        this->window->draw(group[i].picture);
    }
    this->window->display();

}

void Game::initEnemies() {
    this->enemy.setSize(sf::Vector2(10.f, 10.f));
    this->enemy.setFillColor(sf::Color::Magenta);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
    this->enemy.setOrigin(sf::Vector2(5.f, 5.f));
    //this->enemy.setPosition();
}

vector<Animal> createAnimals(vector<Animal> group) {
    for (int i = 0; i < population;  i++){
        group[i].set_stable_position(rand()%width, rand()%height);
        group[i].picture.setRadius(10.f);
        group[i].picture.setFillColor(sf::Color::Blue);
    }
    return group;
}


//------------------------------------------------------GAME LOOP-------------------------------------------------------
int main() {
    vector<Animal> group(population);
    group.reserve(population);
    group = createAnimals(group);
    //Init Game
    Game game;

    //Game loop
    while(game.running())
    {

        //Update
        group = game.update(group);
        //Render

        game.render(group);
    }

    return 0;
}
