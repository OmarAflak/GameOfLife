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
        sf::Color m_cellColor;
        sf::Color m_backgroundColor;
        int m_width;
        int m_height;
        int m_rowSize;

    public:
        Board(sf::RenderWindow* window, int rowSize);
        Board(sf::RenderWindow* window, int rowSize, sf::Color cellColor, sf::Color backgroundColor);

        int getWidth();
        int getHeight();
        bool get(int x, int y);

        void set(int x, int y);
        void unset(int x, int y);
        void toogle(int x, int y);
        void clear();

        bool save(std::string filename);
        bool load(std::string filename);

        void draw();
};

#endif
