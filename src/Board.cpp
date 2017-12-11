#include "../include/Board.h"

Board::Board(sf::RenderWindow* window, int rowSize){
    *this = Board(window, rowSize, sf::Color::Black, sf::Color::White);
}

Board::Board(sf::RenderWindow* window, int rowSize, sf::Color cellColor, sf::Color backgroundColor){
    m_window = window;
    m_rowSize = rowSize;

    m_width = window->getSize().x/rowSize;
    m_height = window->getSize().y/rowSize;

    m_cellColor = cellColor;
    m_backgroundColor = backgroundColor;

    m_rows = std::vector<std::vector<sf::RectangleShape> >(m_width, std::vector<sf::RectangleShape>(m_height));

    for(int i=0 ; i<m_width ; i++){
        for(int j=0 ; j<m_height ; j++){
            m_rows[i][j] = sf::RectangleShape(sf::Vector2f(m_rowSize, m_rowSize));
            m_rows[i][j].setFillColor(m_backgroundColor);
        }
    }
}

int Board::getWidth(){
    return m_width;
}

int Board::getHeight(){
    return m_height;
}

bool Board::get(int x, int y){
    return m_rows[x][y].getFillColor()==m_cellColor;
}

void Board::set(int x, int y){
    m_rows[x][y].setFillColor(m_cellColor);
}

void Board::unset(int x, int y){
    m_rows[x][y].setFillColor(m_backgroundColor);
}

void Board::toogle(int x, int y){
    if(m_rows[x][y].getFillColor()==m_cellColor){
        m_rows[x][y].setFillColor(m_backgroundColor);
    }
    else{
        m_rows[x][y].setFillColor(m_cellColor);
    }
}

void Board::clear(){
    for(int i=0 ; i<m_width ; i++){
        for(int j=0 ; j<m_height ; j++){
            m_rows[i][j].setFillColor(m_backgroundColor);
        }
    }
}

bool Board::save(std::string filename){
    std::ofstream file(filename.c_str());
    if(file){
        file << m_width << std::endl;
        file << m_height << std::endl;
        file << m_rowSize << std::endl;
        for(int i=0 ; i<m_width ; i++){
            for(int j=0 ; j<m_height ; j++){
                file << (m_rows[i][j].getFillColor()==m_cellColor) << std::endl;
            }
        }
        file.close();
        return true;
    }
    return false;
}

bool Board::load(std::string filename){
    std::ifstream file(filename.c_str());
    if(file){
        std::string line;
        getline(file, line);
        m_width = toInt(line);
        getline(file, line);
        m_height = toInt(line);
        getline(file, line);
        m_rowSize = toInt(line);

        m_rows = std::vector<std::vector<sf::RectangleShape> >(m_width, std::vector<sf::RectangleShape>(m_height));

        bool state;
        for(int i=0 ; i<m_width ; i++){
            for(int j=0 ; j<m_height ; j++){
                m_rows[i][j] = sf::RectangleShape(sf::Vector2f(m_rowSize, m_rowSize));

                getline(file, line);
                state = toBool(line);
                if(state){
                    m_rows[i][j].setFillColor(m_cellColor);
                }
                else{
                    m_rows[i][j].setFillColor(m_backgroundColor);
                }
            }
        }

        file.close();
        return true;
    }
    return false;
}

void Board::draw(){
    for(int i=0 ; i<m_width ; i++){
        for(int j=0 ; j<m_height ; j++){
            m_rows[i][j].setPosition(sf::Vector2f(i*m_rowSize, j*m_rowSize));
            m_window->draw(m_rows[i][j]);
        }
    }
}
