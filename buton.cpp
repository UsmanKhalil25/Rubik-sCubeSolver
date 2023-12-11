#include "button.h"
#include <iostream>

Button::Button()
    : rect(sf::Vector2f(100.0f, 30.0f)), isMouseHovering(false), defaultOutlineColor(sf::Color(27,27,27)), defaultOutlineThickness(2.0f), defaultBackgroundColor(sf::Color(27,27,27)), defaultTextColor(sf::Color::White),hoverOutlineColor(sf::Color(27,27,27)),hoverBackgroundColor(sf::Color::White),hoverTextColor(sf::Color()) {
    rect.setPosition(0.0f, 0.0f); // Default position at (0, 0)
    rect.setSize(sf::Vector2f(100.0f, 30.0f));
    rect.setFillColor(defaultBackgroundColor);
    rect.setOutlineColor(defaultOutlineColor);
    rect.setOutlineThickness(defaultOutlineThickness);

    if (!font.loadFromFile("fonts/oswald.ttf")) {
        // Handle font loading error, e.g., print an error message
        std::cerr << "Error loading font." << std::endl;
    }

    buttonText.setFont(font);
    buttonText.setString("Button"); // Default text
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(defaultTextColor);

    // Set the text position within the button
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(rect.getPosition().x + rect.getSize().x / 2.0f, rect.getPosition().y + rect.getSize().y / 2.0f);
}


void Button::initialize(float x, float y, float width, float height, const std::string& text) {
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(defaultBackgroundColor);
    rect.setOutlineColor(defaultOutlineColor);
    rect.setOutlineThickness(defaultOutlineThickness);

    if (!font.loadFromFile("fonts/oswald.ttf")) {
        // Handle font loading error, e.g., print an error message
        std::cerr << "Error loading font." << std::endl;
    }

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(defaultTextColor);

    // Set the text position within the button
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void Button::changeColor(){
    if (isMouseHovering) {
        rect.setFillColor(hoverBackgroundColor);
        rect.setOutlineColor(hoverOutlineColor);
        buttonText.setFillColor(hoverTextColor);
    }
    else {
        rect.setFillColor(defaultBackgroundColor);
        rect.setOutlineColor(defaultOutlineColor);
        buttonText.setFillColor(defaultTextColor);
    }

}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(rect);
    target.draw(buttonText);
}

bool Button::isMouseOver(const sf::Vector2f& mousePosition) {
    isMouseHovering = rect.getGlobalBounds().contains(mousePosition);
    changeColor();
    return isMouseHovering;
}

void Button::setOnClick(std::function<void()> onClick) {
    onClickCallback = onClick;
}

void Button::setOutlineColor(const sf::Color& color) {
    rect.setOutlineColor(color);
}

void Button::setOutlineThickness(float thickness) {
    rect.setOutlineThickness(thickness);
}

void Button::setBackgroundColor(const sf::Color& color) {
    rect.setFillColor(color);
}

void Button::setTextColor(const sf::Color& color) {
    buttonText.setFillColor(color);
}
