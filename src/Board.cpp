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

    sf::RectangleShape emptyCell = sf::RectangleShape(sf::Vector2f(m_rowSize, m_rowSize));
    emptyCell.setFillColor(m_backgroundColor);

    m_rows = std::vector<std::vector<sf::RectangleShape> >(m_width, std::vector<sf::RectangleShape>(m_height, emptyCell));
    m_board = std::vector<std::vector<bool> >(m_width, std::vector<bool>(m_height, false));
}

int Board::getWidth(){
    return m_width;
}

int Board::getHeight(){
    return m_height;
}

bool Board::get(int x, int y){
    return m_board[x][y];
}

void Board::set(int x, int y){
    m_board[x][y] = true;
}

void Board::unset(int x, int y){
    m_board[x][y] = false;
}

void Board::toogle(int x, int y){
    m_board[x][y] = !m_board[x][y];
}

void Board::clear(){
    for(int i=0 ; i<m_width ; i++){
        for(int j=0 ; j<m_height ; j++){
            m_board[i][j] = false;
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
                file << m_board[i][j] << std::endl;
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
        
        for(int i=0 ; i<m_width ; i++){
            for(int j=0 ; j<m_height ; j++){
                getline(file, line);
                m_board[i][j] = toBool(line);
            }
        }

        file.close();
        return true;
    }
    return false;
}

void Board::update(){
    for(int i=0 ; i<m_width ; i++){
        for(int j=0 ; j<m_height ; j++){
            m_rows[i][j].setFillColor(m_board[i][j]?m_cellColor:m_backgroundColor);
            m_rows[i][j].setPosition(sf::Vector2f(i*m_rowSize, j*m_rowSize));
        }
    }
}

void Board::draw(){
    Board::update();
    for(int i=0 ; i<m_width ; i++){
        for(int j=0 ; j<m_height ; j++){
            m_window->draw(m_rows[i][j]);
        }
    }
}
