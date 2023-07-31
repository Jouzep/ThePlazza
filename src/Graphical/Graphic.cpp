/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Graphic
*/

#include "Graphic.hpp"

static void loadFontFromFile(std::string path, sf::Font &font)
{
    if (!font.loadFromFile(path))
        throw Error("Error Load Font", path);
}

Graphic::Graphic(int capacityMax, bool graphic) : _window(sf::VideoMode(1920, 1080), "Plazza"), _capacityMax(capacityMax)
{
    if (graphic) {
        _capacityMsgQ.createIpc(ftok(".", CAPACITY_KEY));
        try {
            loadFontFromFile("assets/font/Raleway-Regular.ttf", _font);
            _pizza.setFont(_font);
            _pizza.setCharacterSize(24);
            _pizza.setFillColor(sf::Color(128, 128, 128));
            loadSpriteFromFile("assets/background.jpg", _backgroundS, _backgroundT);
            loadSpriteFromFile("assets/four.png", _hovenS, _hovenT);
            loadSpriteFromFile("assets/pizza.png", _pizzaS, _pizzaT);
            _backgroundS.setScale(3.f, 3.f);
            _hovenS.setScale(2.5f, 2.5f);
            rotate = 0;
            auto width = _pizzaS.getGlobalBounds().width / 2;
            auto height = _pizzaS.getGlobalBounds().height / 2;
            _pizzaS.setOrigin(width, height);
            _pizzaS.setScale(0.1f, 0.1f);
        } catch (const Error &e) {
        std::cout << e.what() << ":" << e.message() << std::endl;
        }
    }
}

void Graphic::loadSpriteFromFile(std::string path, sf::Sprite &sprite, sf::Texture &texture)
{
    if (!texture.loadFromFile(path))
        throw Error("Error Loading Sprite", path);
    sprite.setTexture(texture);
}

Graphic::~Graphic()
{
}

void Graphic::event()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
}

void Graphic::drawKitchen()
{
    int x = 0;
    int y = 0;
    int size = _kitchen->size();
    for (int i = 0; i < size; i++)
    {
        try {
        _hovenS.setPosition(x, y);
        _window.draw(_hovenS);
        drawCooks(x, y, 100, _kitchen->at(i));
        } catch ( ... ) {
        i = size + 1;
        }
        x += 100 * 2.5;
        if (x >= 1920 - 100*2.5) {
            x = 0;
            y += 100*2.5;
        }
    }
}

void Graphic::draw()
{
    _window.clear();
    _window.draw(_backgroundS);
    drawKitchen();
    _window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

void Graphic::run()
{
    while (_window.isOpen()) {
        event();
        draw();
    }
}

void Graphic::setKitchen(std::shared_ptr<std::vector<int>> kitchen)
{
    _kitchen = kitchen;
}

void Graphic::drawCooks(int x, int y, int sizes, int pid)
{
    float size = 10;
    sf::RectangleShape rect(sf::Vector2f(size, size));
    int tmpX = x;
    int tmpY = y;

        capacity_data data;
    std::memset(&data, 0, sizeof(data));
    _capacityMsgQ.push(data, pid);

    std::unique_ptr<capacity_data> a = nullptr;

    while (a == nullptr) {
        if (!pidIsOn(pid))
            return;
        a = _capacityMsgQ.pop(getpid(), IPC_NOWAIT);
    }
    int capacityLeft = _capacityMax - a->value;
    int cooks = _capacityMax / 2;
    for (int i = 0; i != cooks; i++)
    {
        rect.setPosition(tmpX + size * 2.5, tmpY+ size * 2.5);
        rect.setOutlineColor(sf::Color(128,128,128));
        rect.setOutlineThickness(4);
        if (i < capacityLeft)
            rect.setFillColor(sf::Color::Red);
        else 
            rect.setFillColor(sf::Color::Green);
        _window.draw(rect);
        tmpX += size * 2.5;
        if (tmpX >= x + sizes * 2.5 - size * 2.5) {
            tmpX = x;
            tmpY += size * 2.5;
        }
    }
    drawPizza(x, y + 250, capacityLeft);
}

void Graphic::drawPizza(int x, int y, int qty)
{
    _pizza.setPosition(x + 60, y - 40);
    _pizza.setString(std::to_string(qty) + " : " + std::to_string(_capacityMax) + " Max");
    _pizzaS.setPosition(x + 30, y - 20);
    rotate++;
    _pizzaS.setRotation(rotate);
    _window.draw(_pizzaS);
    _window.draw(_pizza);
}

bool Graphic::pidIsOn(int pid)
{
    int count = std::count(_kitchen->begin(), _kitchen->end(), pid);
    if (count > 0)
        return true;
    return false;
}