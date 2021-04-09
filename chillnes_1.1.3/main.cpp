#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using std::vector;
using std::cout;
using std::endl;


//Global variables======================================================================================================
unsigned int height = 1500;
unsigned int width = 2000;
unsigned int population = 20;
float base_size = 100;
float animal_size = 20;
int energy = 100;
int price_of_animal = 5;
sf::Font font;
sf::Color green = sf::Color::Green;
sf::Color red = sf::Color::Red;
sf::Color white = sf::Color::White;
bool pushed = false;




class Base;

//Point class--------------------------------------------------------
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
    return -(get_x() - a.get_x());
}

double Point::delta_y(Point a) const{
    return -(get_y() - a.get_y());
}

double Point::distance(Point a) const{
    return sqrt(delta_x(a) * delta_x(a) + delta_y(a) * delta_y(a));
}



//Animal class----------------------------------------------------------------------------------------------------------
class Animal
{
public:
    Animal(int energy_, int strength_, int speed_, Point aim_, Point pos_){
        energy = energy_;
        strength = strength_;
        speed = speed_;
        aim = aim_;
        pos = pos_;
        color = green;
        selected = false;
    }
    virtual void move() = 0;
    virtual void eat() = 0;
    virtual void attack(Animal* opponent) = 0;
    virtual void capture(Base* base) = 0;
    int get_energy() const{return energy;}
    int get_strength() const{return strength;}
    int get_price() const{return price;}
    int get_speed() const{return speed;}
    bool is_selected() const{return selected;}
    void set_energy(int energy_) {energy = energy_;}
    void set_strength(int strength_) {strength = strength_;}
    void set_price(int price_) {price = price_;}
    void set_speed(int speed_) {speed = speed_;}
    void select(bool a) {selected = a;}
    Point get_pos() const {return pos;}
    Point set_pos(Point a) {pos = a;}
    Point get_aim() const {return aim;}
    Point set_aim(Point a) {aim = a;}
    sf::CircleShape picture;
    const int size = 5;
    sf::Color color;
    Point pos, aim = pos;
    int native_base;
protected:
    int energy, strength, price, speed;
    bool selected;

};

//Animal types------------------------------------------------------
class Simple_Animal: public Animal
{
public:
    Simple_Animal(int energy_, int strength_, int speed_, Point aim_, Point pos_):
            Animal(energy_, strength_, speed_, aim_, pos_){ }
    void move() final;
    void eat() final;
    void attack(Animal* opponent) final;
    void capture(Base* base) final;
};

vector<Simple_Animal> animals = {};



//Function definition:
void Simple_Animal::move() {
    if (pos.distance(aim) > 1) {
        pos.set_x(pos.get_x() + speed * pos.delta_x(aim) / pos.distance(aim));
        pos.set_y(pos.get_y() + speed * pos.delta_y(aim) / pos.distance(aim));
        picture.setPosition(pos.get_x(), pos.get_y());
    }
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
    sf::CircleShape picture;
    sf::Color color;
    Point pos;
    Base(Point pos_){
        pos = pos_;
        color = white;
    }
};

Point p1(100, 100), p2(300, 1100), p3(600, 750), p4(1000, 1100), p5(1400, 750), p6(1900, 100), p7(1700, 1100);
Base b1(p1), b2(p2), b3(p3), b4(p4), b5(p5), b6(p6), b7(p7);
vector<Base> bases = {b1, b2, b3, b4, b5, b6, b7};


struct button{
    sf::RectangleShape picture;
    sf:: Text caption;
    bool pushed = 0;
};
//Board structure-----------------------------------------------------
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
    Point mouse;
    sf::RectangleShape area;
    int x_mouse, y_mouse;
    int x_mouse_0, y_mouse_0;

    //Private functions
    void initVariables();
    void initWindow();
    void initCursor();

public:
    //Public functions
    void initBoard();
    Game();
    void initBase();
    void initAnimal();
    void pushButtons();
    virtual ~Game();

    const bool running() const;
    void pollEvents();
    void update();
    void render();

    void box ();
};

//Functions definitions:
void Game::initVariables() {
    this->window = nullptr;
}

void Game::initWindow() {
    this->videoMode.height = height;
    this->videoMode.width = width;
    this->window = new sf::RenderWindow(this->videoMode, "Chillness 1.1.3", sf::Style::Titlebar | sf::Style::Close);
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
    this->initBase();
}

const bool Game::running() const {
    return this->window->isOpen();
}

void Game::pollEvents() {
    bool were_selected = false;
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
                    for (int i = 0; i < animals.size(); i++){
                        if (animals[i].is_selected()){
                            animals[i].select(false);
                        }
                    }
                    x_mouse_0 = x_mouse;
                    y_mouse_0 = y_mouse;
                    area.setFillColor(sf::Color(200, 0, 100, 100));
                }
                if (this->ev.mouseButton.button == sf::Mouse::Right) {
                    for (int i = 0; i < animals.size(); i++){
                        if (animals[i].is_selected()){
                            animals[i].set_aim(Point(x_mouse, y_mouse));
                        }
                    }
                }
                break;

            case sf::Event::MouseButtonReleased:
                if (this->ev.mouseButton.button == sf::Mouse::Left) {
                    this->box();
                    for (int i = 0; i < animals.size(); i++){
                        if (animals[i].is_selected()) were_selected = true;
                    }
                    if (!were_selected){
                        this->pushButtons();
                        this->initAnimal();
                    }
                }
                break;
        }
    }
}

void Game::update() {
    this->pollEvents();
    area.setPosition(x_mouse_0, y_mouse_0);
    float size_x = x_mouse - x_mouse_0;
    float size_y = y_mouse - y_mouse_0;
    area.setSize(sf::Vector2(size_x, size_y));
    Point local_mouse(sf::Mouse::getPosition(*this->window).x, y_mouse = sf::Mouse::getPosition(*this->window).y);
    x_mouse = local_mouse.get_x();
    y_mouse = local_mouse.get_y();
    for(int i = 0; i < animals.size(); i++){
        animals[i].move();
    }

    if (x_mouse >= 0 and y_mouse >= 0 and x_mouse <= this->videoMode.width and y_mouse <= this->videoMode.height){
        this->cursor.setFillColor(sf::Color::Red);
        this->cursor.setPosition(x_mouse, y_mouse);
        this->board.energy_lvl.setSize(sf::Vector2(energy*10.f, 50.f));
    }
    else this->cursor.setFillColor(sf::Color::Green);

    if (board.spawn_base.pushed == 1) board.spawn_base.picture.setFillColor(sf::Color::Red);
    else board.spawn_base.picture.setFillColor(sf::Color::Green);

}

void Game::render() {
    window->clear(sf::Color(5, 0, 90, 255));
    window->draw(this->board.board);
    window->draw(this->board.energy_lvl_back);
    window->draw(this->board.energy_lvl);
    window->draw(this->board.energy_lvl_caption);
    window->draw(this->board.spawn_base.picture);
    window->draw(this->cursor);



    for(auto & base : bases) this->window->draw(base.picture);
    for(auto & animal : animals) {
        if (animal.is_selected()) animal.picture.setFillColor(red);
        else animal.picture.setFillColor(green);
        window->draw(animal.picture);
    }

    window->draw(this->area);
    this->window->display();
}

void Game::initCursor() {
    cursor.setSize(sf::Vector2(20.f, 20.f));
    cursor.setFillColor(sf::Color::Magenta);
    cursor.setOutlineColor(sf::Color::Green);
    cursor.setOutlineThickness(1.f);
    cursor.setOrigin(sf::Vector2(5.f, 5.f));

    area.setPosition(sf::Vector2(1.f, 1.f));
    area.setOrigin(sf::Vector2(1.f, 1.f));
    area.setSize(sf::Vector2(2.f, 2.f));
    area.setFillColor(sf::Color(0, 0, 0, 0));

}

void Game::initBoard() {
    this->board.energy_lvl.setPosition(10, 1420);
    this->board.energy_lvl.setSize(sf::Vector2(energy*10.f, 50.f));
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
    for(int i = 0; i < bases.size(); i++) {
        bases[i].picture.setOrigin(base_size, base_size);
        bases[i].picture.setPosition(bases[i].pos.get_x(), bases[i].pos.get_y());
        bases[i].picture.setRadius(base_size);
        bases[i].picture.setFillColor(bases[i].color);

    }
}

void Game::initAnimal() {
    bool near_animal = false;
    bool near_base = false;
    Point position(0, 0);
    position.set_x(x_mouse);
    position.set_y(y_mouse);
    for(int i = 0; i < animals.size(); i++){
        if(position.distance(animals[i].get_pos()) < animal_size*2) near_animal = true;
        }
    for(int i = 0; i < bases.size(); i++) {
        if (position.distance(bases[i].pos) < base_size) near_base = true;
        }

        if (near_animal == false and near_base == true and energy >= price_of_animal and position.get_y() < height and position.get_x() < width) {
            energy -= price_of_animal;
            Point aim_ = position;
            auto beast = Simple_Animal(price_of_animal, 100, 10, aim_, position);
            beast.picture.setRadius(animal_size);
            beast.picture.setPosition(beast.get_pos().get_x(), beast.get_pos().get_y());
            beast.picture.setOrigin(animal_size, animal_size);
            beast.picture.setFillColor(beast.color);
            beast.picture.setOutlineThickness(3);
            beast.picture.setOutlineColor(white);
            animals.push_back(beast);
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

void Game::box (){
    Point a1(x_mouse, y_mouse);
    Point a2(x_mouse_0, y_mouse_0);
    double xmax = std::max(a1.get_x(), a2.get_x());
    double xmin = std::min(a1.get_x(), a2.get_x());
    double ymax = std::max(a1.get_y(), a2.get_y());
    double ymin = std::min(a1.get_y(), a2.get_y());

    for (unsigned int i = 0; i < animals.size(); i++){
        if ((animals[i].pos.get_x() < xmax && animals[i].pos.get_x() > xmin) && (animals[i].pos.get_y() < ymax && animals[i].pos.get_y() > ymin)){
            animals[i].select(true);
            animals[i].picture.setFillColor(red);
        }
    }
    x_mouse_0 = 0;
    y_mouse_0 = 0;
    area.setFillColor(sf::Color(0, 0, 0, 0));
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
