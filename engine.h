#ifndef ENGINE_H
#define ENGINE_H

#include "cube.h"
#include "searchutil.h"
#include "randomnumgenerator.h"
#include "thistlethwaite.h"
#include"button.h"
#include <SFML/Graphics.hpp>
#include<map>
#include<string>



class Engine
{
public:
    Engine();

    void run();

private:
    void init();
    void mainLoop();
    void pollEvents();
    void update();
    void render();

    std::map<Rubiks::EMOVE, std::string> moveCharMap = {
    {Rubiks::EMOVE::U, "U"},
    {Rubiks::EMOVE::Up, "U'"},
    {Rubiks::EMOVE::U2, "U2"},
    {Rubiks::EMOVE::L, "L"},
    {Rubiks::EMOVE::Lp, "L'"},
    {Rubiks::EMOVE::L2, "L2"},
    {Rubiks::EMOVE::F, "F"},
    {Rubiks::EMOVE::Fp, "F'"},
    {Rubiks::EMOVE::F2, "F2"},
    {Rubiks::EMOVE::R, "R"},
    {Rubiks::EMOVE::Rp, "R'"},
    {Rubiks::EMOVE::R2, "R2"},
    {Rubiks::EMOVE::B, "B"},
    {Rubiks::EMOVE::Bp, "B'"},
    {Rubiks::EMOVE::B2, "B2"},
    {Rubiks::EMOVE::D, "D"},
    {Rubiks::EMOVE::Dp, "D'"},
    {Rubiks::EMOVE::D2, "D2"}
    };
    std::string getMoveChar(Rubiks::EMOVE move) {return moveCharMap[move];}

    sf::RenderWindow m_window;
    bool m_exit = false;

    sf::Color m_colours[6];
    enum { W, O, G, R, B, Y };

    const uint32_t FPS = 60;
    const sf::Time FRAME_TIME = sf::seconds(1.f / FPS);

    void renderFacelet(size_t ind);
    void setFaceletPos(size_t ind, float x, float y);

    Rubiks m_cube;

    sf::View view;

    sf::Vector2f face_size;

    sf::RectangleShape m_facelets[54];
    sf::RectangleShape m_centreFacelets[6];
    uint8_t m_faceletsColour[48];

    void scramble(size_t movesAmount);

    Thistlethwaite m_thistlethwaite;

    Button resetButton;
    Button shuffleButton;
    Button solveButton;
    Button returnButton;
    Button nextMoveButton;

    bool solving;
    bool goToNextMove;
    Rubiks::EMOVE currentMove;

    sf::RectangleShape cubeFaces[6];
    sf::Text cubeFacesText[6];
    sf::Font font;  // Load the font you want to use
    sf::Text errorMessage;
    sf::Text moveText;

    sf::Text allMoves;
};
#endif // ENGINE_H
