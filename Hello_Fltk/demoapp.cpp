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
    demoapp.cpp
    Hello_Fltk
  
    Created by Michele Iarossi on 16.08.22.
*/

#include "Graphics.hpp"

using namespace mathsophy::graphics;

#include "demoapp.hpp"

// constructor
Lines_window::Lines_window(Point xy,int w,int h,const char* title) :
    Simple_window(xy, w, h, title),
    add_button{Point{x_max()-250,0},100,50,"Add point",
        [](Fl_Widget* w, void* lw) {static_cast<Lines_window*>(lw)->add_pressed();},this},
    menu_button{Point{x_max()-250,100},100,50,"Menu color",
    [](Fl_Widget* w, void* lw) {static_cast<Lines_window*>(lw)->menu_pressed();},this},
    color_menu(Point{x_max()-250,100},Menu_type::vertical),
    next_x{Point{100,0},50,20,"next x:"},
    next_y{Point{250,0},50,20,"next y:"},
    xy_out{Point{100,50},100,20,"current (x,y):"}
{
    // add buttons to the menu
    color_menu.add_button(new Button{Point{0,0},100,50,"Red",[](Fl_Widget* w, void* lw) {static_cast<Lines_window*>(lw)->red_pressed();},this});
    color_menu.add_button(new Button{Point{0,0},100,50,"Blue",[](Fl_Widget* w, void* lw) {static_cast<Lines_window*>(lw)->blue_pressed();},this});
    color_menu.add_button(new Button{Point{0,0},100,50,"Green",[](Fl_Widget* w, void* lw) {static_cast<Lines_window*>(lw)->green_pressed();},this});
    // hide the color menu
    color_menu.hide();
    // attach all the widgets to the window
    attach(add_button);
    attach(menu_button);
    attach(color_menu);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    attach(lines);
}

// callback called when the add button is pressed
void Lines_window::add_pressed()
{
    int x = next_x.get_input_integer();
    int y = next_y.get_input_integer();
    lines.add_point(Point{x,y});
    xy_out.set_output_text(string{"("+to_string(x)+","+
        to_string(y)+")"});
    redraw();
}

// callback called when the menu button is pressed
void Lines_window::menu_pressed()
{
    // hide the menu button and show now the color buttons
    menu_button.hide();
    color_menu.show();
    redraw();
}

// callback called when the red button is pressed
void Lines_window::red_pressed()
{
    // change the polyline color to red
    lines.set_color(Color_type::red);
    // hide the color buttons and show the menu button
    color_menu.hide();
    menu_button.show();
    redraw();
}

// callback called when the blue button is pressed
void Lines_window::blue_pressed()
{
    // change the polyline color to blue
    lines.set_color(Color_type::blue);
    // hide the color buttons and show the menu button
    color_menu.hide();
    menu_button.show();
    redraw();
}

// callback called when the green button is pressed
void Lines_window::green_pressed()
{
    // change the polyline color to green
    lines.set_color(Color_type::green);
    // hide the color buttons and show the menu button
    color_menu.hide();
    menu_button.show();
    redraw();
}
