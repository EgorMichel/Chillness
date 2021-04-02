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
sf::Font font;


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
public:
    sf::RectangleShape picture;
    int x, y, native_base;
    float  size;
    Animal(int x_, int y_){
        this->x = x_;
        this->y = y_;
        this->size = 10;
    }
};
struct button{
    sf::RectangleShape picture;
    sf:: Text caption;
    bool pushed = 0;
};
//Board class------------------------------------------------------
struct Board{
    sf::RectangleShape energy_lvl;
    sf::RectangleShape energy_lvl_back;
    sf::RectangleShape board;
    button spawn_base;
    sf::Text energy_lvl_caption;
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
    Board board;

    //Private functions
    void initVariables();
    void initWindow();
    void initCursor();

public:
    //Public functions
    void initBoard();
    Game();
    void initBase();
    void pushButtons();
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
    this->initBoard();
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
                    this->pushButtons();
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
        this->board.energy_lvl.setSize(sf::Vector2(energy*10, 50.f));
    }
    else this->cursor.setFillColor(sf::Color::Green);

    if (board.spawn_base.pushed == 1) board.spawn_base.picture.setFillColor(sf::Color::Red);
    else board.spawn_base.picture.setFillColor(sf::Color::Green);

}

void Game::render() {
    this->window->clear(sf::Color(40, 10, 40, 255));
    this->window->draw(this->board.board);
    this->window->draw(this->board.energy_lvl_back);
    this->window->draw(this->board.energy_lvl);
    this->window->draw(this->board.energy_lvl_caption);
    this->window->draw(this->board.spawn_base.picture);
    this->window->draw(this->cursor);

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

void Game::initBoard() {
    this->board.energy_lvl.setPosition(10, 1420);
    this->board.energy_lvl.setSize(sf::Vector2(energy*10, 50.f));
    this->board.energy_lvl.setFillColor(sf::Color::Blue);

    this->board.energy_lvl_caption.setCharacterSize(50);
    this->board.energy_lvl_caption.setFont(font);
    this->board.energy_lvl_caption.setPosition(20, 1410);
    this->board.energy_lvl_caption.setFillColor(sf::Color::Yellow);
    this->board.energy_lvl_caption.setString("energy");

    this->board.energy_lvl_back.setPosition(10, 1420);
    this->board.energy_lvl_back.setSize(sf::Vector2(energy*10+20.f, 50.f));
    this->board.energy_lvl_back.setFillColor(sf::Color::Black);

    this->board.board.setPosition(10, 1400);
    this->board.board.setSize(sf::Vector2(1900.f, 100.f));
    this->board.board.setFillColor(sf::Color::White);

    this->board.spawn_base.picture.setPosition(1725, 1445);
    this->board.spawn_base.picture.setSize(sf::Vector2(50.f, 50.f));
    this->board.spawn_base.picture.setFillColor(sf::Color::Green);
    this->board.spawn_base.picture.setOrigin(25,25);
}

void Game::initBase() {
    bool nearby = false;
    float x_, y_;
    x_ = sf::Mouse::getPosition(*this->window).x;
    y_ = sf::Mouse::getPosition(*this->window).y;
    for(int i = 0; i < bases.size(); i++){
        if(distance(x_, y_, bases[i].x, bases[i].y) < base_size*2) nearby = true;
    }
    if (nearby == false and energy >= 30 and y_ < 1300 and board.spawn_base.pushed == true) {
        energy -= 30;
        Base b = Base(x_, y_);
        b.size = base_size;
        b.picture.setPosition(b.x, b.y);
        b.picture.setSize(sf::Vector2(b.size, b.size));
        b.picture.setFillColor(sf::Color::Yellow);
        b.picture.setOrigin(b.size / 2, b.size / 2);
        bases.push_back(b);
    }
}

void Game::pushButtons() {
    int x_mouse, y_mouse;
    x_mouse = sf::Mouse::getPosition(*this->window).x;
    y_mouse = sf::Mouse::getPosition(*this->window).y;
    if (x_mouse >= 0 and y_mouse >= 0 and x_mouse <= this->videoMode.width and y_mouse <= this->videoMode.height
    and abs(x_mouse - board.spawn_base.picture.getPosition().x) < board.spawn_base.picture.getSize().x/2 and
    abs(y_mouse - board.spawn_base.picture.getPosition().y) < board.spawn_base.picture.getSize().y/2){
        this->board.spawn_base.pushed = !this->board.spawn_base.pushed;
    }
}

//------------------------------------------------------GAME LOOP-------------------------------------------------------
int main() {
    font.loadFromFile("/home/egorchan/CLionProjects/Chillness/Chillness_1.1.2_/20326.otf");
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
