#include "engine.h"
#include <iostream>



// https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

    return view;
}



Engine::Engine()
{
    init();
}

void Engine::run()
{
    mainLoop();
}

void Engine::render()
{
    m_window.clear(sf::Color::White);
    // Set the view
    m_window.setView(view);

     //Centre facelets
    for (size_t i = 0; i < 6; ++i)
    {
        m_window.draw(m_centreFacelets[i]);
        m_window.draw(cubeFaces[i]);
        m_window.draw(cubeFacesText[i]);
    }
    // All facelets
    for (size_t i = 0; i < 48; ++i)
    {
        renderFacelet(i);
    }

    if(solving){
        m_window.draw(nextMoveButton);
        m_window.draw(moveText);
    }
    else{
        m_window.draw(resetButton);
        m_window.draw(shuffleButton);
        m_window.draw(solveButton);
        m_window.draw(errorMessage);

    }
    m_window.draw(allMoves);
    m_window.draw(returnButton);



    m_window.display();
}

void Engine::renderFacelet(size_t ind)
{
    m_facelets[ind].setFillColor(m_colours[m_faceletsColour[ind]]);
    m_window.draw(m_facelets[ind]);
}

void Engine::update()
{
    for (size_t i = 0; i < 48; ++i)
    {
        m_faceletsColour[i] = (uint8_t)m_cube.getColour(i);
    }
}


void Engine::init()
{
    int res_x = 1280;
    int res_y = 720;
    m_window.create(sf::VideoMode(res_x, res_y), "Rubik's Cube", (sf::Style::Resize + sf::Style::Close));
    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(FPS);
    //view to resize the screen
    view.setSize(res_x, res_y);
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

    constexpr int faceletSize = 40;
    constexpr int padding = 3; // Adjust this value for spacing between stickers

    m_colours[W] = sf::Color::White;
    m_colours[O] = sf::Color(255, 120, 0);
    m_colours[G] = sf::Color::Green;
    m_colours[R] = sf::Color::Red;
    m_colours[B] = sf::Color::Blue;
    m_colours[Y] = sf::Color::Yellow;


    face_size = sf::Vector2f(view.getSize().y * 0.24, view.getSize().y * 0.24);
    float centerX = view.getSize().x / 2;
    float centerY = view.getSize().y / 2;

    // Define the positions for each face
    sf::Vector2f facePositions[6];
    facePositions[0] = sf::Vector2f(centerX - face_size.x, centerY - face_size.y * 3/2);  // Upper (U)
    facePositions[1] = sf::Vector2f(centerX - face_size.x * 2, centerY - face_size.y / 2);  // Left (L)
    facePositions[2] = sf::Vector2f(centerX - face_size.x, centerY - face_size.y / 2);  // Front (F)
    facePositions[3] = sf::Vector2f(centerX, centerY - face_size.y / 2);  // Right (R)
    facePositions[4] = sf::Vector2f(centerX + face_size.x, centerY - face_size.y / 2);  // Back (B)
    facePositions[5] = sf::Vector2f(centerX - face_size.x, centerY + face_size.y / 2);  // Down (D)

    int index = 0;
    int centerIndex = 0;
    for (size_t face = 0; face < 6; face++)
    {
        for (size_t i = 0; i < 3; i++)
        {

            for (size_t j = 0; j < 3; j++)
            {
                // Calculate the positions for stickers based on the face's position
                float xPos = facePositions[face].x + j * (faceletSize + padding);
                float yPos = facePositions[face].y + i * (faceletSize + padding);


                if (i == 1 && j == 1)
                {
                    // Center stickers
                    m_centreFacelets[centerIndex].setSize(sf::Vector2f(faceletSize, faceletSize));
                    m_centreFacelets[centerIndex].setOutlineColor(sf::Color(27, 27, 27));
                    m_centreFacelets[centerIndex].setOutlineThickness(3.0f);
                    m_centreFacelets[centerIndex].setPosition(sf::Vector2f(xPos, yPos));
                    m_centreFacelets[centerIndex].setFillColor(m_colours[face]);
                    centerIndex++;
                }
                else
                {
                    int alterIndex =index;
                    if(i == 1 && j == 0)
                        alterIndex+=4;
                    else if(i == 1 && j == 2)
                        alterIndex-=1;
                    else if(i == 2 && j == 0)
                        alterIndex+=1;
                    else if(i == 2 && j == 1)
                        alterIndex-=1;
                    else if(i == 2 && j == 2)
                        alterIndex-=3;
                    // Use m_facelets for the corner and edge stickers
                    m_facelets[alterIndex].setSize(sf::Vector2f(faceletSize, faceletSize));
                    m_facelets[alterIndex].setOutlineColor(sf::Color(27, 27, 27));
                    m_facelets[alterIndex].setOutlineThickness(3.0f);
                    m_facelets[alterIndex].setPosition(sf::Vector2f(xPos, yPos));
                    m_facelets[alterIndex].setFillColor(m_colours[face]);
                    index++;
                }
            }
        }
    }




    // Calculate button width and height
    float buttonWidth = 80.f;
    float buttonHeight = 30.0f;

    // Calculate button spacing
    float buttonSpacing = 20.0f;

    // Calculate the X-coordinate for buttons to be centered horizontally
    float buttonX = view.getCenter().x - 1.5f * (buttonWidth + buttonSpacing);
    float buttonY = view.getCenter().y + view.getSize().y / 2.0f - (buttonHeight + buttonSpacing +20);

    // Position and create the buttons
    resetButton.initialize(buttonX, buttonY, buttonWidth, buttonHeight, "Reset");
    shuffleButton.initialize(buttonX + buttonWidth + buttonSpacing, buttonY, buttonWidth, buttonHeight, "Shuffle");
    solveButton.initialize(buttonX + 2 * (buttonWidth + buttonSpacing), buttonY, buttonWidth, buttonHeight, "Solve");
    float returnButtonX = view.getCenter().x + view.getSize().x / 2 - buttonWidth -100;
    float returnButtonY = 5;
    returnButton.initialize(returnButtonX, returnButtonY, buttonWidth+80, buttonHeight, "Go to home page");
    nextMoveButton.initialize(view.getCenter().x - buttonWidth+20, buttonY, buttonWidth+20, buttonHeight, "Next move");


    // Set the callback functions for the buttons
    resetButton.setOnClick([this]() {
        if(!solving){
            this->errorMessage.setString("");
            m_cube.resetCube();
        }

    });

    shuffleButton.setOnClick([this]() {
        if(!solving){
            m_cube.resetCube();
            // change the number of shuffles
            scramble(20);
            this->errorMessage.setString("");
        }

    });


    solveButton.setOnClick([this]() {
        if(!m_cube.isValidCube()){
            this->errorMessage.setString("Each color must be added exaclty 9 times.");
        }
        else{
            this->errorMessage.setString("");
            this->solving = true;

            std::vector<Rubiks::EMOVE> result = m_thistlethwaite.solve(m_cube);
                for (const auto& move : result){
                    std::string moveChar = getMoveChar(move);
                    currentMove = move;
                    moveText.setString(moveChar);
                    while(!goToNextMove){
                        render();
                        pollEvents();
                    };
                    //m_cube.performMove(move);
                    this->goToNextMove = false;
                    update();
                }
            this->solving = false;

        }


    });

    returnButton.setOnClick([this](){
        // implement where to go when return from game button is clicked
        m_window.close();
    });


    if (!font.loadFromFile("fonts/oswald.ttf")) {
        // Handle font loading error, e.g., print an error message
        std::cerr << "Error loading font." << std::endl;
    }

    errorMessage.setFont(font);
    errorMessage.setCharacterSize(22);
    errorMessage.setFillColor(sf::Color::Red);
    errorMessage.setString(""); // Initial error message
    errorMessage.setPosition(buttonX, view.getCenter().y + view.getSize().y / 2 - errorMessage.getCharacterSize()-10);
    moveText.setFont(font);
    moveText.setCharacterSize(30);
    moveText.Bold;
    moveText.setFillColor(sf::Color(27,27,27));
    moveText.setString(""); // Initial error message
    moveText.setPosition(view.getCenter().x - moveText.getCharacterSize(),12);

    allMoves.setFont(font);
    allMoves.setCharacterSize(15);
    allMoves.setFillColor(sf::Color(0,0,0));
    allMoves.setString("Avaliable Moves: \nU - Upper face clockwise rotation\nD - Lower face clockwise rotation\nL - Left face clockwise rotation\nR - Right faceclockwise rotation\nF - Front face clockwise rotation\nB - Rear face clockwise rotation\nU' - Upper face counterclockwise rotation\nD' - Lower face counterclockwise rotation\nL' - Left face counterclockwise rotation\nR' - Right face counterclockwise rotation\nF' - Front face counterclockwise rotation\nB' - Rear face counterclockwise rotation\nU2 - Upper face 180 degree rotation\nD2 - Lower face 180 degree rotation\nL2 - Left face 180 degree rotation\nR2 - Right face 180 degree rotation\nF2 - Front face 180 degree rotation\nB2 - Rear 180 degree rotation\n");
    allMoves.setPosition(returnButtonX-80,returnButtonY+100);

    sf::Vector2f cubeSize(faceletSize * 3, faceletSize * 3); // Adjust for your cube size

    for (int i = 0; i < 6; ++i) {
        cubeFaces[i].setSize(sf::Vector2f(faceletSize, faceletSize));
        cubeFaces[i].setOutlineColor(sf::Color(27, 27, 27));
        cubeFaces[i].setOutlineThickness(3.0f);
        cubeFacesText[i].setFont(font);
        cubeFacesText[i].setCharacterSize(22);
        cubeFacesText[i].setFillColor(sf::Color(27,27,27));

        // Set positions based on the order you described
        switch (i) {
            case 0: // Upper face
                cubeFaces[i].setPosition(100, 100);
                cubeFacesText[i].setString("U");
                cubeFacesText[i].setPosition(100 +  cubeFacesText[i].getCharacterSize()/2 +2,100 + cubeFacesText[i].getCharacterSize()/2);
                break;
            case 1: // Left face
                cubeFaces[i].setPosition(50, 150);
                cubeFacesText[i].setString("L");
                cubeFacesText[i].setPosition(50 +  cubeFacesText[i].getCharacterSize()/2 + 2,150 + cubeFacesText[i].getCharacterSize()/2);
                break;
            case 2: // Front face
                cubeFaces[i].setPosition(100,150);
                cubeFacesText[i].setString("F");
                cubeFacesText[i].setPosition(100 +  cubeFacesText[i].getCharacterSize()/2 +2,150 + cubeFacesText[i].getCharacterSize()/2);
                break;
            case 3: // Right face
                cubeFaces[i].setPosition(150,150);
                cubeFacesText[i].setString("R");
                cubeFacesText[i].setPosition(150 +  cubeFacesText[i].getCharacterSize()/2 +2,150 + cubeFacesText[i].getCharacterSize()/2);
                break;
            case 4: // Bottom face
                cubeFaces[i].setPosition(200,150);
                cubeFacesText[i].setString("B");
                cubeFacesText[i].setPosition(200 +  cubeFacesText[i].getCharacterSize()/2 +2,150 + cubeFacesText[i].getCharacterSize()/2);
                break;
            case 5: // Down face
                cubeFaces[i].setPosition(100,200);
                cubeFacesText[i].setString("D");
                cubeFacesText[i].setPosition(100 +  cubeFacesText[i].getCharacterSize()/2 +2,200 + cubeFacesText[i].getCharacterSize()/2);
                break;
        }
    }


    this->solving = false;
    this->goToNextMove = false;
}


void Engine::mainLoop()
{
    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;

    while (m_window.isOpen())
    {
        pollEvents();
        elapsed += clock.restart();

        while (elapsed >= FRAME_TIME)
        {
            elapsed -= FRAME_TIME;
            update();
        }

        render(); // Add this line to render the cube
    }
}

void Engine::scramble(size_t movesAmount)
{
    SearchUtil searchUtil;
    RandomNumGenerator generator(1, 18);

    size_t movesPerformed = 0;

    Rubiks::EMOVE last = Rubiks::EMOVE::NO_MOVE;
    Rubiks::EMOVE curr = Rubiks::EMOVE::NO_MOVE;

    std::cout << "Scrambled with:" << std::endl;

    while (movesPerformed <= movesAmount)
    {
        curr = static_cast<Rubiks::EMOVE>(generator.getNum());
        if (!searchUtil.isRedundant(curr, last))
        {
            m_cube.performMove(curr);
            if (movesPerformed == movesAmount / 2)
                std::cout << std::endl;
            std::cout << m_cube.getMoveName(curr);

            last = curr;
            movesPerformed++;
        }
    }
    std::cout << std::endl;
}


void Engine::pollEvents(){
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if (event.type == sf::Event::Resized)
        {
            view = getLetterboxView(view, event.size.width, event.size.height);
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                const sf::Vector2f mousePosition = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                // Check if the mouse is over the buttons and perform the click action
                for (size_t i = 0; i < 48; ++i) {
                    if (m_facelets[i].getGlobalBounds().contains(mousePosition)) {
                        m_cube.toggleColor(i);
                        break;
                    }
                }

                if (resetButton.isMouseOver(mousePosition)) {
                    resetButton.onClickCallback();
                }
                if (shuffleButton.isMouseOver(mousePosition)) {
                    shuffleButton.onClickCallback();
                }
                if (solveButton.isMouseOver(mousePosition)) {
                    solveButton.onClickCallback();
                }
                if (returnButton.isMouseOver(mousePosition)) {
                    returnButton.onClickCallback();
                }
                if(nextMoveButton.isMouseOver(mousePosition)){
                    if(solving){
                         goToNextMove = true;
                        m_cube.performMove(currentMove);
                    }

                }

            }


        }
        else if (event.type == sf::Event::MouseMoved)
        {
            const sf::Vector2f mousePosition = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

            // Check if the mouse is over the buttons and update their hover state
            resetButton.isMouseOver(mousePosition);
            shuffleButton.isMouseOver(mousePosition);
            solveButton.isMouseOver(mousePosition);
            returnButton.isMouseOver(mousePosition);
            nextMoveButton.isMouseOver(mousePosition);

            bool isOverFacelet = false;

            // Check if the mouse is over any facelets
            for (size_t i = 0; i < 48; ++i) {
                if (m_facelets[i].getGlobalBounds().contains(mousePosition)) {
                    isOverFacelet = true;
                    break;
                }
            }

            if (isOverFacelet) {
                // If the mouse is over a facelet, set it to the hand cursor
                sf::Cursor handCursor;
                if (!handCursor.loadFromSystem(sf::Cursor::Hand)) {
                    std::cerr << "Error loading hand cursor." << std::endl;
                }
                m_window.setMouseCursor(handCursor);
            } else {
                // If not over any facelets, set it back to the arrow cursor
                sf::Cursor arrowCursor;
                if (!arrowCursor.loadFromSystem(sf::Cursor::Arrow)) {
                    std::cerr << "Error loading arrow cursor." << std::endl;
                }
                m_window.setMouseCursor(arrowCursor);
            }



        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::R)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    m_cube.Rp();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    m_cube.R2();
                else
                    m_cube.R();
            }
            else if (event.key.code == sf::Keyboard::U)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    m_cube.Up();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    m_cube.U2();
                else
                    m_cube.U();
            }
            else if (event.key.code == sf::Keyboard::L)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    m_cube.Lp();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    m_cube.L2();
                else
                    m_cube.L();
            }
            else if (event.key.code == sf::Keyboard::F)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    m_cube.Fp();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    m_cube.F2();
                else
                    m_cube.F();
            }
            else if (event.key.code == sf::Keyboard::B)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    m_cube.Bp();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    m_cube.B2();
                else
                    m_cube.B();
            }
            else if (event.key.code == sf::Keyboard::D)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    m_cube.Dp();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    m_cube.D2();
                else
                    m_cube.D();
            }
            else if (event.key.code == sf::Keyboard::S)
            {
                scramble(50);
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                m_cube.resetCube();
            }
            else if (event.key.code == sf::Keyboard::F1)
            {
                std::vector<Rubiks::EMOVE> result = m_thistlethwaite.solve(m_cube);
                for (const auto& move : result){
                    m_cube.performMove(move);
                }
            }
        }
    }
}
