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
    demoapp.hpp
    Hello_Fltk
  
    Created by Michele Iarossi on 16.08.22.
*/

#ifndef demoapp_hpp
#define demoapp_hpp

// Class definition for a little demo application
class Lines_window : public Simple_window
{
public:
    // constructor
    Lines_window(Point xy,int w,int h,const char* title);
    // virtual destructor
    virtual ~Lines_window() { color_menu.destroy(); }
private:
    Open_polyline lines;    // the polyline
    Button add_button;      // button for adding a point to the polyline
    Button menu_button;     // button for revealing the color buttons
    Menu color_menu;        // menu of the color buttons
    In_box next_x;          // input box for reading the abscissa
    In_box next_y;          // input box for reading the ordinate
    Out_box xy_out;         // output box for showing the point added
    void add_pressed();     // callback for the add button
    void menu_pressed();    // callback for the menu button
    void red_pressed();     // callback for the red color button
    void blue_pressed();    // callback for the blue color button
    void green_pressed();   // callback for the green color button
};

#endif /* demoapp_hpp */
