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
unsigned int height = 800;
unsigned int width = 1500;
unsigned int population = 20;
float base_size = 100;
float energy = 100;
sf::Font font;


//useful classes
class Point{
public:
    Point() = default;
    Point(double x_, double y_){
        x = x_;
        y = y_;
    }
    double get_x() const {return x;}
    double get_y() const {return y;}
    void set_x(double a) {x = a;}
    void set_y(double a) {y = a;}
    double delta_x(Point a) const;
    double delta_y(Point a) const;
    double distance(Point a) const;
    Point& operator= (Point a){
        this->set_x(a.get_x());
        this->set_y(a.get_y());
        return *this;
    }
private:
    double x = 0;
    double y = 0;
};

double Point::delta_x(Point a) const{
    return std::abs(get_x() - a.get_x());
}

double Point::delta_y(Point a) const{
    return std::abs(get_y() - a.get_y());
}

double Point::distance(Point a) const{
    return sqrt(delta_x(a) * delta_x(a) + delta_y(a) * delta_y(a));
}



//Global functions---------------------
//float distance(double x1, double x2, double y1, double y2){
//    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
//}

class Base;



//Animal interface--------------------------------------------------------
class Animal
{
public:
    Animal(int energy_, int strength_, int price_, int speed_, Point aim_, Point pos_){
        energy = energy_;
        strength = strength_;
        price = price_;
        speed = speed_;
        aim = aim_;
        pos = pos_;
    }
    virtual void move() = 0;
    virtual void eat() = 0;
    virtual void attack(Animal* opponent) = 0;
    virtual void capture(Base* base) = 0;
    int get_energy() const{return energy;}
    int get_strength() const{return strength;}
    int get_price() const{return price;}
    int get_speed() const{return speed;}
    void set_energy(int energy_) {energy = energy_;}
    void set_strength(int strength_) {strength = strength_;}
    void set_price(int price_) {price = price_;}
    void set_speed(int speed_) {speed = speed_;}

protected:
    int energy, strength, price, speed;
    Point aim, pos;
};


//Animal types------------------------------------------------------
class Simple_Animal: public Animal
{
public:
    Simple_Animal(int energy_, int strength_, int price_, int speed_, Point aim_, Point pos_):
    Animal(energy_, strength_, price_, speed_, aim_, pos_){ }
    void move() final;
    void eat() final;
    void attack(Animal* opponent) final;
    void capture(Base* base) final;
};


//Function definition:
void Simple_Animal::move(){
    pos.set_x(pos.get_x() + speed * pos.delta_x(aim) / pos.distance(aim));
    pos.set_y(pos.get_y() + speed * pos.delta_y(aim) / pos.distance(aim));
}

void Simple_Animal::eat(){
}

void Simple_Animal::attack(Animal* opponent){
    opponent->set_energy(opponent->get_energy() - strength);
    energy -= opponent->get_strength();
    if (energy < 0){
        delete this;
    }
}

void Simple_Animal::capture(Base* base){
}

//Base class--------------------------------------------------------
class Base{
public:
    sf::RectangleShape picture;
    Point pos;
    float  size;
    Base(Point pos_, float size_){
        pos = pos_;
        size = size_;
    }
    Simple_Animal* buildanimal(int energy_, unsigned int strength_, unsigned int price_, unsigned int speed_, Point aim_, Point pos_){
        auto beast = new Simple_Animal(energy_, strength_, price_, speed_, aim_, pos_);
        return beast;
    }
};

vector<Base> bases;


//Board class------------------------------------------------------
struct Board{
    sf::RectangleShape energy_lvl;
    sf::RectangleShape energy_lvl_back;
    sf::RectangleShape board;
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
    void initEnergy_lvl();
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

        this->board.energy_lvl.setSize(sf::Vector2(energy*10, 50.f));


    }
    else this->cursor.setFillColor(sf::Color::Green);
}

void Game::render() {
    this->window->clear(sf::Color(40, 10, 40, 255));
    this->window->draw(this->board.board);
    this->window->draw(this->board.energy_lvl_back);
    this->window->draw(this->board.energy_lvl);
    this->window->draw(this->board.energy_lvl_caption);
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

void Game::initEnergy_lvl() {
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
}

void Game::initBase() {
    bool nearby = false;
    Point position(0, 0);
    position.set_x(sf::Mouse::getPosition(*this->window).x);
    position.set_y(sf::Mouse::getPosition(*this->window).y);
    for(int i = 0; i < bases.size(); i++){
        if(position.distance(bases[i].pos)) nearby = true;
    }
    if (nearby == false and energy >= 10 and position.get_y() < 1400) {
        energy -= 10;
        Base b = Base(position, 1);
        b.size = base_size;
        b.picture.setPosition(b.pos.get_x(), b.pos.get_y());
        b.picture.setSize(sf::Vector2(b.size, b.size));
        b.picture.setFillColor(sf::Color::Yellow);
        b.picture.setOrigin(b.size / 2, b.size / 2);
        bases.push_back(b);
    }
}

//------------------------------------------------------GAME LOOP-------------------------------------------------------
int main() {
    font.loadFromFile("/home/egor/Repositories/Chillness/Chillness_1.1.2_/OpenSans-Regular.ttf");
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
