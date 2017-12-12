#include <iostream>
#include <ctime>

#include "include/Board.h"
#include "include/Utils.h"

static const std::string configFolder = "config/";
static const std::string configExt = ".gol";
static const std::string arialFont = "fonts/arial.ttf";

bool nextState(Board &board, int x, int y){
    int xStart = x>0?x-1:0;
    int yStart = y>0?y-1:0;
    int xEnd = x<board.getWidth()-1?x+1:board.getWidth()-1;
    int yEnd = y<board.getHeight()-1?y+1:board.getHeight()-1;

    int counter = 0;
    for(int i=xStart ; i<=xEnd ; i++){
        for(int j=yStart ; j<=yEnd ; j++){
            if(i!=x || j!=y){
                if(board.isCell(i,j)){
                    counter++;
                }
            }
        }
    }

    if(board.isCell(x,y)){
        return (counter==2 || counter==3);
    }
    else{
        return counter==3;
    }
}

void evolve(Board &board){
    std::vector<std::vector<bool> > states(board.getWidth(), std::vector<bool>(board.getHeight()));

    for(int i=0 ; i<board.getWidth() ; i++){
        for(int j=0 ; j<board.getHeight() ; j++){
            states[i][j] = nextState(board, i, j);
        }
    }

    for(int i=0 ; i<board.getWidth() ; i++){
        for(int j=0 ; j<board.getHeight() ; j++){
            if(states[i][j]){
                board.putCell(i,j);
            }
            else{
                board.removeCell(i,j);
            }
        }
    }
}

void helper(){
    std::cout << std::endl;
    std::cout << "################# GAME OF LIFE #################" << std::endl;
    std::cout << "####     [MOUSE]  = add/remove cells        ####" << std::endl;
    std::cout << "####     [SPACE]  = start/stop animation    ####" << std::endl;
    std::cout << "####     [RETURN] = step by step animation  ####" << std::endl;
    std::cout << "####     [CTRL+D] = clear screen            ####" << std::endl;
    std::cout << "####     [CTRL+S] = save configuration      ####" << std::endl;
    std::cout << "####     [CTRL+O] = open configuration      ####" << std::endl;
    std::cout << "####     [CTRL+H] = help                    ####" << std::endl;
    std::cout << "####     [C+MOUSE] = draw                   ####" << std::endl;
    std::cout << "####     [V+MOUSE] = erase                  ####" << std::endl;
    std::cout << "####     [+] = accelerate animation         ####" << std::endl;
    std::cout << "####     [-] = slow animation               ####" << std::endl;
    std::cout << "################################################" << std::endl;
    std::cout << std::endl;
}

int main(){
    srand(time(NULL));

    sf::Clock timer;
    int deltaTime = 5;
    int refreshTimeMilli = 50;
    bool animate = false;
    int generation = 0;
    bool control = false;
    bool typing = false;
    bool typingFinished = false;
    bool saving = false;
    bool opening = false;
    bool drawing = false;
    bool erasing = false;
    int row = 10;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Game Of Life");
    Board board(&window, row, sf::Color::White, sf::Color::Black);

    sf::Font font;
    if(!font.loadFromFile(arialFont)){
        exit(1);
    }
    sf::Text text("0", font, 18);
    text.setColor(sf::Color::Red);
    text.setPosition(sf::Vector2f(0,0));

    helper();

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
                else if(event.key.code == sf::Keyboard::LControl){
                    control = true;
                }
                else if(event.key.code == sf::Keyboard::Space){
                    if(!typing){
                        animate = !animate;
                    }
                }
                else if(event.key.code == sf::Keyboard::Return){
                    if(typing){
                        typing = false;
                        typingFinished = true;
                    }
                    else{
                        evolve(board);
                        generation++;
                        text.setString(toString(generation));
                    }
                }
                else if(event.key.code == sf::Keyboard::Add){
                    if(refreshTimeMilli>=deltaTime){
                        refreshTimeMilli-=deltaTime;
                    }
                }
                else if(event.key.code == sf::Keyboard::Subtract){
                    refreshTimeMilli+=deltaTime;
                }
                else if(control && event.key.code == sf::Keyboard::D){
                    board.clear();
                    animate = false;
                    generation = 0;
                    text.setString("0");
                }
                else if(control && event.key.code == sf::Keyboard::S){
                    animate = false;
                    typing = true;
                    typingFinished = false;
                    saving = true;
                    text.setString("configuration name : ");
                }
                else if(control && event.key.code == sf::Keyboard::O){
                    animate = false;
                    typing = true;
                    typingFinished = false;
                    opening = true;
                    text.setString("configuration name : ");
                }
                else if(control && event.key.code == sf::Keyboard::H){
                    if(!typing){
                        helper();
                    }
                }
                else if(event.key.code == sf::Keyboard::C){
                    drawing = true;
                    erasing = false;
                }
                else if(event.key.code == sf::Keyboard::V){
                    drawing = false;
                    erasing = true;
                }
            }
            else if (event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::LControl){
                    control = false;
                }
                else if(event.key.code == sf::Keyboard::C){
                    drawing = false;
                    erasing = false;
                }
                else if(event.key.code == sf::Keyboard::V){
                    drawing = false;
                    erasing = false;
                }
            }
            else if(event.type == sf::Event::TextEntered){
                if (typing && !control && event.text.unicode>=0 && event.text.unicode<=127){
                    if(event.text.unicode==8){
                        std::string str = text.getString();
                        text.setString(str.substr(0, str.size()-1));
                    } else{
                        text.setString(text.getString() + static_cast<char>(event.text.unicode));
                    }
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    board.toogleCell(event.mouseButton.x/row, event.mouseButton.y/row);
                }
            }
            else if(event.type == sf::Event::MouseMoved){
                if(drawing && !erasing){
                    board.putCell(event.mouseMove.x/row, event.mouseMove.y/row);
                }
                else if(!drawing && erasing){
                    board.removeCell(event.mouseMove.x/row, event.mouseMove.y/row);
                }
            }
        }

        if(typingFinished){
            std::string str = text.getString();
            str = str.substr(str.find_first_of(":")+1);
            std::string filename = configFolder+trim(str)+configExt;

            std::cout << "[" << filename << "]" << std::endl;

            if(saving){
                text.setString(board.save(filename)?"configuration saved.":"could not save configuration");
            }
            else if(opening){
                text.setString(board.load(filename)?"configuration loaded.":"could not load configuration");
            }
            saving = false;
            opening = false;
            typingFinished = false;
        }

        if(animate && timer.getElapsedTime().asMilliseconds()>refreshTimeMilli){
            evolve(board);
            generation++;
            text.setString(toString(generation));
            timer.restart();
        }

        window.clear();
        board.draw();
        window.draw(text);
        window.display();
    }

    return 0;
}
