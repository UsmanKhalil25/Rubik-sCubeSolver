#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <string>

// Define EFACE and ECOLOUR enums
enum class EFACE : uint8_t { U, L, F, R, B, D };
enum class ECOLOUR : uint8_t { W, O, G, R, B, Y };

class CubeFace : public sf::Drawable {
public:
    CubeFace(const sf::RectangleShape &face, std::vector<std::vector<ECOLOUR>> &sticker_values);

    void updateStickers();
    void handleMouseClick(const sf::Vector2f &mousePosition);
    bool isMouseOverSticker(const sf::Vector2f &mousePosition);

private:
    const sf::RectangleShape &face;
    std::vector<std::vector<ECOLOUR>> &sticker_values;
    std::vector<std::vector<sf::RectangleShape>> stickers;

    std::array<ECOLOUR, 6> availableColors = {ECOLOUR::W, ECOLOUR::O, ECOLOUR::G, ECOLOUR::R, ECOLOUR::B, ECOLOUR::Y};

    void toggleColor(int i, int j);

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const override;
};

