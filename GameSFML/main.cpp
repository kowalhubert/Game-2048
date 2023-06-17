#include "game.h"

int main()
{
    welcome();
    return 0;
}

sf::Vector2i genPos(){
    sf::Vector2i v;
    while(1){
        v.x = rand() % boardSize;
        v.y = rand() % boardSize;
        if (MAP[v.y][v.x] == 0) {
            break;
        }
    }
    return v;
}

int genNewTitle(){
    int t = rand() % 2;
    if(t == 0){
        return 2;
    } else {
        return 4;
    }
}

void placeNewTitle(){
    sf::Vector2i p = genPos();
    MAP[p.y][p.x] = genNewTitle();
}

void shift(Direction d){
    bool didShift = 0;
    if (d == Direction::Up){
        for(int j=0; j<boardSize; j++){  //Every row
            for(int i=0; i<boardSize-1; i++){
                if(MAP[i][j] == 0){
                    bool change = 0;
                    for(int k=i; k<boardSize-1; k++){ //Shift everything up
                        MAP[k][j] = MAP[k+1][j];
                        if(MAP[k][j] != 0){
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP[boardSize-1][j] = 0;
                    if(change){
                        i--;
                    }
                }
            }
            for(int i=0; i<boardSize-1; i++){
                if(MAP[i][j] == MAP[i+1][j] && MAP[i][j] != 0){
                    didShift = 1;
                    for(int k=i; k<boardSize-1; k++){
                        MAP[k][j] = MAP[k+1][j];
                    }
                    MAP[boardSize-1][j] = 0;
                    MAP[i][j] *= 2;
                }
            }
        }
    } else if(d == Direction::Left){
        for(int i=0; i<boardSize; i++){
            for(int j=0; j<boardSize-1; j++){
                if(MAP[i][j] == 0){
                    bool change = 0;
                    for(int k=j; k<boardSize-1; k++){ //Shift everything to the left
                        MAP[i][k] = MAP[i][k+1];
                        if(MAP[i][k] != 0){
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP[i][boardSize-1] = 0;
                    if(change){
                        j--;
                    }
                }
            }
            for(int j=0; j<boardSize-1; j++){
                if(MAP[i][j] == MAP[i][j+1] && MAP[i][j] != 0){
                    didShift = 1;
                    for(int k=j; k<boardSize-1; k++){
                        MAP[i][k] = MAP[i][k+1];
                    }
                    MAP[i][boardSize-1] = 0;
                    MAP[i][j] *= 2;
                }
            }
        }
    } else if(d == Direction::Down){
        for(int j=0; j<boardSize; j++){
            for(int i=boardSize-1; i>=0; i--){
                if(MAP[i][j] == 0){
                    bool change = 0;
                    for(int k=i; k>0; k--){ //Shift everything down
                        MAP[k][j] = MAP[k-1][j];
                        if(MAP[k][j] != 0){
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP[0][j] = 0;
                    if(change){
                        i++;
                    }
                }
            }
            for(int i=boardSize-1; i>0; i--){
                if(MAP[i][j] == MAP[i-1][j] && MAP[i][j] != 0){
                    didShift = 1;
                    for(int k=i; k>=0; k--){
                        MAP[k][j] = MAP[k-1][j];
                    }
                    MAP[0][j] = 0;
                    MAP[i][j] *= 2;
                }
            }
        }
    } else if(d == Direction::Right){
        for(int i=0; i<boardSize; i++){
            for(int j=boardSize-1; j>=0; j--){
                if(MAP[i][j] == 0){
                    bool change = 0;
                    for(int k=j; k>0; k--){ //Shift everything to the right
                        MAP[i][k] = MAP[i][k-1];
                        if(MAP[i][k] != 0){
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP[i][0] = 0;
                    if(change){
                        j++;
                    }
                }
            }
            for(int j=boardSize-1; j>0; j--){
                if(MAP[i][j] == MAP[i][j-1] && MAP[i][j] != 0){
                    didShift = 1;
                    for(int k=j; k>0; k--){
                        MAP[i][k] = MAP[i][k-1];
                    }
                    MAP[i][0] = 0;
                    MAP[i][j] *= 2;
                }
            }
        }
    }
    if(didShift){
        placeNewTitle();
    }
}

void welcome()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "2048 - Welcome");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        return;
    }

    sf::Text welcomeText("WELCOME TO 2048!", font, 50);
    welcomeText.setPosition(170, 200);
    welcomeText.setFillColor(sf::Color::Black);

    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setPosition(300, 420);
    startButton.setFillColor(sf::Color(205, 133, 63));

    sf::Text startButtonText("Start Game", font, 30);
    startButtonText.setPosition(320, 425);
    startButtonText.setFillColor(sf::Color::Black);

    std::string inputStr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (startButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                    {
                        window.close();
                        runGame();
                    }
                }
            }
        }
        window.clear(sf::Color(255, 245, 238));
        window.draw(welcomeText);
        window.draw(startButton);
        window.draw(startButtonText);
        window.display();
    }
}

void cleanBoard(){
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            MAP[i][j] = 0;
        }
    }
}

void runGame(){

    cleanBoard();

    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "2048");
    window.setSize(sf::Vector2u(800,800));

    sf::Texture tblank, t2, t4, t8, t16, t32, t64, t128, t256, t512, t1024, t2048;
    tblank.loadFromFile("images/blank.png");
    t2.loadFromFile("images/2.png");
    t4.loadFromFile("images/4.png");
    t8.loadFromFile("images/8.png");
    t16.loadFromFile("images/16.png");
    t32.loadFromFile("images/32.png");
    t64.loadFromFile("images/64.png");
    t128.loadFromFile("images/128.png");
    t256.loadFromFile("images/256.png");
    t512.loadFromFile("images/512.png");
    t1024.loadFromFile("images/1024.png");
    t2048.loadFromFile("images/2048.png");

    sf::Sprite sprite_blank(tblank);
    sf::Sprite sprite_2(t2);
    sf::Sprite sprite_4(t4);
    sf::Sprite sprite_8(t8);
    sf::Sprite sprite_16(t16);
    sf::Sprite sprite_32(t32);
    sf::Sprite sprite_64(t64);
    sf::Sprite sprite_128(t128);
    sf::Sprite sprite_256(t256);
    sf::Sprite sprite_512(t512);
    sf::Sprite sprite_1024(t1024);
    sf::Sprite sprite_2048(t2048);

    placeNewTitle();
    placeNewTitle();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && !g_win) {
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                    shift(Direction::Left);
                }
                else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                    shift(Direction::Right);
                }
                else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                    shift(Direction::Up);
                }
                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    shift(Direction::Down);
                }
            }
            else if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (!g_win) {
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (MAP[i][j] == 2048) {
                        g_win = true;
                        window.close();
                        winOrLoseWindow(0);
                        break;
                    }
                }
            }
        }

        if(checkLose()){
            window.close();
            winOrLoseWindow(1);
            break;
        }

        window.clear();
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (MAP[i][j] == 0) {
                    sprite_blank.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_blank);
                }
                else if (MAP[i][j] == 2) {
                    sprite_2.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_2);
                }
                else if (MAP[i][j] == 4) {
                    sprite_4.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_4);
                }
                else if (MAP[i][j] == 8) {
                    sprite_8.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_8);
                }
                else if (MAP[i][j] == 16) {
                    sprite_16.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_16);
                }
                else if (MAP[i][j] == 32) {
                    sprite_32.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_32);
                }
                else if (MAP[i][j] == 64) {
                    sprite_64.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_64);
                }
                else if (MAP[i][j] == 128) {
                    sprite_128.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_128);
                }
                else if (MAP[i][j] == 256) {
                    sprite_256.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_256);
                }
                else if (MAP[i][j] == 512) {
                    sprite_512.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_512);
                }
                else if (MAP[i][j] == 1024) {
                    sprite_1024.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_1024);
                }
                else if (MAP[i][j] == 2048) {
                    sprite_2048.setPosition(j * TITLESIZE, i * TITLESIZE);
                    window.draw(sprite_2048);
                }
            }
        }
        window.display();
    }
}

void winOrLoseWindow(int a)
{
    sf::RenderWindow window;
    if (a == 0) {
        window.create(sf::VideoMode(800, 400), "Congratulations!");
    } else if (a == 1) {
        window.create(sf::VideoMode(800, 400), "Game Over!");
    } else {
        return;
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return;
    }

    sf::Text text;
    if (a == 0) {
        text.setString("CONGRATULATIONS! YOU WON!");
        text.setFillColor(sf::Color::Green);
        text.setPosition(20, 120);
    } else if (a == 1) {
        text.setString("GAME OVER! YOU LOST!");
        text.setFillColor(sf::Color::Red);
        text.setPosition(100, 120);
    }
    text.setFont(font);
    text.setCharacterSize(50);

    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setPosition(300, 240);
    startButton.setFillColor(sf::Color(205, 133, 63));

    sf::Text startButtonText("New Game", font, 30);
    startButtonText.setPosition(320, 245);
    startButtonText.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (startButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                    {
                        window.close();
                        welcome();
                    }
                }
            }
        }
        window.clear(sf::Color(255, 245, 238));
        window.draw(text);
        window.draw(startButton);
        window.draw(startButtonText);
        window.display();
    }
}

bool checkLose() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (MAP[i][j] == 0) {
                return false;
            }
            if (i < boardSize - 1 && MAP[i][j] == MAP[i + 1][j]) {
                return false;
            }
            if (j < boardSize - 1 && MAP[i][j] == MAP[i][j + 1]) {
                return false;
            }
        }
    }
    return true;
}