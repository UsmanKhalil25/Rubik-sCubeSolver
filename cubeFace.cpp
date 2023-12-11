#include "cubeFace.h"
#include <SFML/Graphics.hpp>

CubeFace::CubeFace(const sf::RectangleShape &face, std::vector<std::vector<ECOLOUR>> &sticker_values) :
    face(face),
    sticker_values(sticker_values)
{
    face.setFillColor(sf::Color::Transparent);

    float face_border = 7;
    float sticker_width = (face.getSize().x - face_border * 2) / sticker_values[0].size();
    sf::Vector2f sticker_size(sticker_width, sticker_width);

    sf::Vector2f face_origin = face.getPosition(); // Top left corner of face
    for (int i = 0; i < sticker_values.size(); i++) {
        std::vector<sf::RectangleShape> row;
        for (int j = 0; j < sticker_values[i].size(); j++) {
            sf::RectangleShape sticker;
            sticker.setSize(sticker_size);
            sticker.setPosition(face_origin.x + face_border + j * sticker_width,
                               face_origin.y + face_border + i * sticker_width);
            // Set fill color for stickers
            switch (sticker_values[i][j]) {
                case ECOLOUR::W:
                    sticker.setFillColor(sf::Color::White);
                    break;
                case ECOLOUR::Y:
                    sticker.setFillColor(sf::Color::Yellow);
                    break;
                case ECOLOUR::G:
                    sticker.setFillColor(sf::Color::Green);
                    break;
                case ECOLOUR::B:
                    sticker.setFillColor(sf::Color::Blue);
                    break;
                case ECOLOUR::O:
                    sticker.setFillColor(sf::Color(255, 120, 0));
                    break;
                case ECOLOUR::R:
                    sticker.setFillColor(sf::Color::Red);
                    break;
                default:
                    sticker.setFillColor(sf::Color::Black);
                    break;
            }
            sticker.setOutlineColor(sf::Color::Black);
            sticker.setOutlineThickness(sticker_width * -0.05f);
            row.push_back(sticker);
        }
        stickers.push_back(row);
    }
}

void CubeFace::updateStickers() {
    for (int i = 0; i < stickers.size(); i++) {
        for (int j = 0; j < stickers[0].size(); j++) {
            // Set fill color for stickers
            switch (sticker_values[i][j]) {
                case ECOLOUR::W:
                    stickers[i][j].setFillColor(sf::Color::White);
                    break;
                case ECOLOUR::Y:
                    stickers[i][j].setFillColor(sf::Color::Yellow);
                    break;
                case ECOLOUR::G:
                    stickers[i][j].setFillColor(sf::Color::Green);
                    break;
                case ECOLOUR::B:
                    stickers[i][j].setFillColor(sf::Color::Blue);
                    break;
                case ECOLOUR::O:
                    stickers[i][j].setFillColor(sf::Color(255, 120, 0));
                    break;
                case ECOLOUR::R:
                    stickers[i][j].setFillColor(sf::Color::Red);
                    break;
                default:
                    stickers[i][j].setFillColor(sf::Color::Black);
                    break;
            }
        }
    }
}

void CubeFace::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(face);
    for (int i = 0; i < stickers.size(); i++) {
        for (int j = 0; j < stickers[0].size(); j++) {
            renderTarget.draw(stickers[i][j]);
        }
    }
}

void CubeFace::handleMouseClick(const sf::Vector2f &mousePosition) {
    for (int i = 0; i < stickers.size(); i++) {
        for (int j = 0; j < stickers[0].size(); j++) {
            if (stickers[i][j].getGlobalBounds().contains(mousePosition)) {
                // The mouse click is within the bounds of this sticker
                toggleColor(i, j);
            }
        }
    }
}

void CubeFace::toggleColor(const int i, const int j) {
    // Toggle the value of the clicked sticker
    ECOLOUR currentValue = sticker_values[i][j];
    // Find the index of the current value in the colors array
    int currentIndex = -1;
    for (int k = 0; k < availableColors.size(); k++) {
        if (availableColors[k] == currentValue) {
            currentIndex = k;
            break;
        }
    }
    if (currentIndex != -1) {
        // Calculate the index of the new value
        int newIndex = (currentIndex + 1) % availableColors.size();
        sticker_values[i][j] = availableColors[newIndex];
    }
    this->updateStickers();
}

bool CubeFace::isMouseOverSticker(const sf::Vector2f &mousePosition) {
    for (int i = 0; i < stickers.size(); i++) {
        for (int j = 0; j < stickers[0].size(); j++) {
            if (stickers[i][j].getGlobalBounds().contains(mousePosition)) {
                return true;
            }
        }
    }
    return false;
}
