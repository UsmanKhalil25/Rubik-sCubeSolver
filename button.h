#include <SFML/Graphics.hpp>
#include <functional>

class Button:public sf::Drawable {
public:
    Button();
    void initialize(float x, float y, float width, float height, const std::string& text);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool isMouseOver(const sf::Vector2f& mousePosition);
    void setOnClick(std::function<void()> onClick);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    void setBackgroundColor(const sf::Color& color);
    void setTextColor(const sf::Color& color);
    std::function<void()> onClickCallback;
    sf::Color defaultOutlineColor;
    sf::Color defaultBackgroundColor;
    sf::Color defaultTextColor;
    float defaultOutlineThickness;

    sf::Color hoverOutlineColor;
    sf::Color hoverBackgroundColor;
    sf::Color hoverTextColor;

private:
    sf::RectangleShape rect;
    sf::Text buttonText;
    sf::Font font;
    bool isMouseHovering;
    void changeColor();

};
