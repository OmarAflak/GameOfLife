#include <iostream>
#include <ctime>

#include "include/Board.h"
#include "include/Utils.h"

static const std::string configFolder = "config";

bool nextState(Board &board, int x, int y){
    int xStart = x>0?x-1:0;
    int yStart = y>0?y-1:0;
    int xEnd = x<board.getWidth()-1?x+1:board.getWidth()-1;
    int yEnd = y<board.getHeight()-1?y+1:board.getHeight()-1;

    int counter = 0;
    for(int i=xStart ; i<=xEnd ; i++){
        for(int j=yStart ; j<=yEnd ; j++){
            if(i!=x || j!=y){
                if(board.get(i,j)){
                    counter++;
                }
            }
        }
    }

    if(board.get(x,y)){
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
                board.set(i,j);
            }
            else{
                board.unset(i,j);
            }
        }
    }
}

void helper(){
    std::cout << std::endl;
    std::cout << "################# GAME OF LIFE #################" << std::endl;
    std::cout << "####     [MOUSE] = add/remove cells         ####" << std::endl;
    std::cout << "####     [SPACE] = start/stop animation     ####" << std::endl;
    std::cout << "####     [RETURN] = step by step animation  ####" << std::endl;
    std::cout << "####     [DELETE] = clear screen            ####" << std::endl;
    std::cout << "####     [+] = accelerate animation         ####" << std::endl;
    std::cout << "####     [-] = slow animation               ####" << std::endl;
    std::cout << "####     [S] = save current configuration   ####" << std::endl;
    std::cout << "####     [O] = load configuration           ####" << std::endl;
    std::cout << "################################################" << std::endl;
    std::cout << std::endl;
}

int main(){
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 800), "Game Of Life");
    sf::Clock timer;
    int deltaTime = 5;
    int refreshTimeMilli = 50;
    bool animate = false;

    int row = 10;
    Board board(&window, row, sf::Color::White, sf::Color::Black);

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
                else if(event.key.code == sf::Keyboard::Space){
                    animate = !animate;
                }
                else if(event.key.code == sf::Keyboard::Return){
                    evolve(board);
                }
                else if(event.key.code == sf::Keyboard::Delete){
                    board.clear();
                    animate = false;
                }
                else if(event.key.code == sf::Keyboard::Add){
                    if(refreshTimeMilli>=deltaTime){
                        refreshTimeMilli-=deltaTime;
                    }
                }
                else if(event.key.code == sf::Keyboard::Subtract){
                    refreshTimeMilli+=deltaTime;
                }
                else if(event.key.code == sf::Keyboard::S){
                    std::stringstream ss;
                    ss << configFolder << "/" << time(0) << ".gol";
                    if(board.save(ss.str())){
                        std::cout << "configuration saved." << std::endl;
                    }
                    else{
                        std::cout << "could not save current configuration" << std::endl;
                    }
                }
                else if(event.key.code == sf::Keyboard::O){
                    std::string filename;
                    std::cout << "configuration name : ";
                    getline(std::cin, filename);
                    filename = configFolder+"/"+filename+".gol";
                    if(board.load(filename)){
                        std::cout << "configuration loaded." << std::endl;
                    }
                    else{
                        std::cout << "could not load configuration " << filename << std::endl;
                    }
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    board.toogle(event.mouseButton.x/row, event.mouseButton.y/row);
                }
            }
        }

        if(animate && timer.getElapsedTime().asMilliseconds()>refreshTimeMilli){
            evolve(board);
            timer.restart();
        }

        window.clear();
        board.draw();
        window.display();
    }

    return 0;
}