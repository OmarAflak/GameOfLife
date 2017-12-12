#ifndef DEF_BOARD
#define DEF_BOARD

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>

#include "Utils.h"

class Board {
    private:
        sf::RenderWindow* m_window;
        std::vector<std::vector<sf::RectangleShape> > m_rows;
        std::vector<std::vector<bool> > m_board;
        sf::Color m_cellColor;
        sf::Color m_backgroundColor;
        int m_width;
        int m_height;
        int m_cellSize;

        void update();

    public:
        Board(sf::RenderWindow* window, int cellSize);
        Board(sf::RenderWindow* window, int cellSize, sf::Color cellColor, sf::Color backgroundColor);

        int getWidth();
        int getHeight();
        int getCellSize();
        bool isCell(int x, int y);

        void putCell(int x, int y);
        void removeCell(int x, int y);
        void toogleCell(int x, int y);
        void clear();

        bool save(std::string filename);
        bool load(std::string filename);

        void draw();
};

#endif
