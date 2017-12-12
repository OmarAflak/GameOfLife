#include "../include/Board.h"

Board::Board(sf::RenderWindow* window, int cellSize){
    *this = Board(window, cellSize, sf::Color::Black, sf::Color::White);
}

Board::Board(sf::RenderWindow* window, int cellSize, sf::Color cellColor, sf::Color backgroundColor){
    m_window = window;
    m_cellSize = cellSize;

    m_width = window->getSize().x/cellSize;
    m_height = window->getSize().y/cellSize;

    m_cellColor = cellColor;
    m_backgroundColor = backgroundColor;

    sf::RectangleShape emptyCell = sf::RectangleShape(sf::Vector2f(m_cellSize, m_cellSize));
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

int Board::getCellSize(){
    return m_cellSize;
}

bool Board::isCell(int x, int y){
    return m_board[x][y];
}

void Board::putCell(int x, int y){
    m_board[x][y] = true;
}

void Board::removeCell(int x, int y){
    m_board[x][y] = false;
}

void Board::toogleCell(int x, int y){
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
        file << m_cellSize << std::endl;
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
        m_cellSize = toInt(line);

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
            m_rows[i][j].setPosition(sf::Vector2f(i*m_cellSize, j*m_cellSize));
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
