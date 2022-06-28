/*
    Hello_Fltk Xcode project
 
    This project is based on chapters 12 to 16 of Bjarne Stroustrup's book
    "Programming - Principles and Practice Using C++", 2nd edition, Addison
    Wesley, 2014. It is my own implementation of the graphics classes described
    in the book, which I have coded while following along Bjarne's explanations from the
    chapters above.

    Copyright (C) 2022 Michele Iarossi - michele@mathsophy.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/*
    main.cpp
    Hello_Fltk
  
    Created by Michele Iarossi on 06.01.22.
*/

#include "examples.h"

#include <iostream>

int main(int argc, char **argv)
{
    try {
        lines();
        grid();
        polylines();
        rectangles();
        colorgrid();
        text();
        circles();
        ellipses();
        markedpolylines();
        marks();
        circleswithmarks();
        images();
        functions();
        exponentials();
        dataplots();
        buttons();
        inoutbox();
        menu();
        lineswindow();
    } catch (std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Other exception\n";
        return 2;
    }
    
    return 0;
}
