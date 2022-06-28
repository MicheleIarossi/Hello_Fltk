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
    examples.cpp
    Hello_Fltk
  
    Created by Michele Iarossi on 16.04.22.
*/

#include "Graphics.hpp"
#include "examples.h"

#include <sstream>

using namespace mathsophy::graphics;

// factorial
static double fact(int n) {
    int r = 1;
    while (n>1) {
        r*=n;
        --n;
    }
    return r;
}

// exponential function to the precision of n terms
static double expe(double x, int n) {
    double sum = 0;
    for (int i=0; i<n; ++i) sum += pow(x,i)/fact(i);
    return sum;
}

// example usage of Line and Lines classes
void lines()
{
    Simple_window win(Point{100,100},640,480,"Lines");

    // a cross made of 2 lines
    Line horizontal{ {Point{100,300},Point{200,300}} };
    horizontal.set_color(Color_type::blue);
    horizontal.set_style(Style_type::solid, 2);
    Line vertical{ {Point{150,50},Point{150,150}} };
    vertical.set_color(Color_type::blue);
    vertical.set_style(Style_type::solid, 2);
    win.attach(horizontal);
    win.attach(vertical);

    Line diagonal { {Point{200,200},Point{250,250}} };
    diagonal.set_color(Color_type::blue);
    diagonal.set_style(Style_type::solid, 2);
    win.attach(diagonal);
    
    Lines cross;
    cross.add_line( {Point{300,300},Point{400,300}} );
    cross.add_line( {Point{350,250},Point{350,350}} );
    win.attach(cross);

    win.wait_for_button();
}

// example usage of the Lines class
void grid()
{
    Simple_window win(Point{100,100},640,480,"Grid");
    
    Lines grid;
    int x_size = win.w();
    int y_size = win.h();
    int x_grid = 80;
    int y_grid = 40;
    for (int x=x_grid; x<x_size; x+=x_grid)
        grid.add_line( {Point{x,0},Point{x,y_size}} );
    for (int y=y_grid; y<y_size; y+=y_grid)
        grid.add_line( {Point{0,y},Point{x_size,y}} );
    
    grid.set_color(Color_type::red);
    grid.set_style(Style_type::dash, 4);
    
    win.attach(grid);
    
    win.wait_for_button();
}

// example usage of the polyline classes:
// Open_polyline, Closed_polyline, Polygon
void polylines()
{
    Simple_window win(Point{100,100},640,480,"Polylines and polygon");
    
    Open_polyline open_poly = { Point{100,100}, Point{200,100},
                                Point{150,50},  Point{150,150} };
    open_poly.set_color(Color_type::magenta);
    open_poly.set_style(Style_type::solid, 4);
    win.attach(open_poly);
    
    Closed_polyline closed_poly = { Point{300,300}, Point{400,300},                                           Point{350,250}, Point{350,350} };
    closed_poly.set_color(Color_type::green);
    closed_poly.set_style(Style_type::solid, 4);
    win.attach(closed_poly);
    
    Polygon poly = { Point{200,150},Point{250,25},
                     Point{250,300}, Point{150,350} };
    poly.set_color(Color_type::yellow);
    poly.set_style(Style_type::solid, 4);
    win.attach(poly);
    
    win.wait_for_button();
}

// example usage of the Rectangle class
void rectangles()
{
    Simple_window win(Point{100,100},640,480,"Rectangles 1");
    
    Rectangle rect00{Point{150,100},200,100};
    Rectangle rect11{Point{50,50},200,100};
    Rectangle rect12{Point{50,150},200,100};
    Rectangle rect21{Point{250,50},200,100};
    Rectangle rect22{Point{250,150},200,100};
    
    rect00.set_color(Color_type::yellow);
    rect11.set_color(Color_type::blue);
    rect12.set_color(Color_type::red);
    rect21.set_color(Color_type::green);
    rect22.set_filled(false);
    
    win.attach(rect00);
    win.attach(rect11);
    win.attach(rect12);
    win.attach(rect21);
    win.attach(rect22);
    
    win.wait_for_button();
    
    win.set_title("Rectangles 2");
    win.show();
    
    rect11.set_color(Color_type::white);
    rect11.move(400,0);
    rect11.redraw();
    
    win.wait_for_button();
    
    win.set_title("Rectangles 3");
    win.put_on_top(rect00);
    
    win.wait_for_button();
    
    win.set_title("Rectangles 4");
    
    rect00.set_outline(false);
    rect11.set_outline(false);
    rect12.set_outline(false);
    rect21.set_outline(false);
    rect22.set_outline(false);
    
    win.wait_for_button();
}

// another example usage of the Rectangle class
void colorgrid()
{
    Simple_window win(Point{100,100},640,480,"16x16 color grid");
    
    vector<Rectangle*> v;
    
    // shows a 16x16 color grid
    for (int i=0; i<16; ++i)
        for (int j=0; j<16; ++j)
        {
            v.push_back(new Rectangle{Point{i*20,j*20},20,20});
            v[v.size()-1]->set_color((i*16+j));
            win.attach(*v[v.size()-1]);
        }
    
    win.wait_for_button();
}

// example usage of the Text class
void text()
{
    Simple_window win(Point{100,100},640,480,"Closed polyline with text");
    
    Closed_polyline closed_poly = { Point{300,300}, Point{400,300},                                           Point{350,250}, Point{350,350} };
    closed_poly.set_color(Color_type::green);
    closed_poly.set_style(Style_type::solid, 4);
    
    Text t{Point{200,200}," A closed polyline that isn't a polygon"};
    t.set_font(Font_type::times_bold_italic,18);
    t.set_color(Color_type::blue);
    
    win.attach(closed_poly);
    win.attach(t);
    
    win.wait_for_button();
}

// example usage of the Circle class
void circles()
{
    Simple_window win(Point{100,100},640,480,"Circles");
    
    Circle c1{Point{100,200},50};
    Circle c2{Point{150,200},100};
    Circle c3{Point{200,200},150};
    
    win.attach(c1);
    win.attach(c2);
    win.attach(c3);
    
    win.wait_for_button();
}

// example usage of the Ellipse class
void ellipses()
{
    Simple_window win(Point{100,100},640,480,"Ellipses");
    
    Ellipse e1{Point{200,200},50,50};
    Ellipse e2{Point{200,200},100,50};
    Ellipse e3{Point{200,200},100,150};
    
    win.attach(e1);
    win.attach(e2);
    win.attach(e3);
    
    win.wait_for_button();
}

// example usage of the Marked_polyline class
void markedpolylines()
{
    Simple_window win(Point{100,100},640,480,"Marked polylines");
    
    Marked_polyline marked_poly{ {"one","two","three","four"}, {Point{100,100},Point{200,100}, Point{150,50}, Point{150,150}}};
    marked_poly.set_color(Color_type::magenta);
    marked_poly.set_style(Style_type::solid, 2);
    marked_poly.set_font(Font_type::times_bold_italic,12);
    win.attach(marked_poly);
    
    Marked_polyline marked_poly2{ {"{250,200}","{300,75}","{300,350}","{200,400}"} };
    marked_poly2.add_point(Point{250,200});
    marked_poly2.add_point(Point{300,75});
    marked_poly2.add_point(Point{300,350});
    marked_poly2.add_point(Point{200,400});
    marked_poly2.set_color(Color_type::yellow);
    marked_poly2.set_style(Style_type::solid, 4);
    marked_poly2.set_font(Font_type::times_bold_italic,28);
    win.attach(marked_poly2);
    
    win.wait_for_button();
}

// example usage of the Marks class
void marks()
{
    Simple_window win(Point{100,100},640,480,"Marks");
    
    Marks marks{"x",{Point{250,200},Point{300,75},Point{300,350},Point{200,400}}};
    marks.set_color(Color_type::red);
    marks.set_style(Style_type::solid, 4);
    marks.set_font(Font_type::times_bold_italic,28);
    win.attach(marks);
    
    win.wait_for_button();
}

// example usage of the Circle and Marks classes
void circleswithmarks()
{
    Simple_window win(Point{100,100},640,480,"Circles with centers");
    
    Circle c1{Point{100,200},50};
    Circle c2{Point{150,200},100};
    Circle c3{Point{200,200},150};
    c1.set_color(Color_type::blue);
    c2.set_color(Color_type::red);
    c3.set_color(Color_type::green);
    win.attach(c1);
    win.attach(c2);
    win.attach(c3);
    
    Mark m1{Point{100,200},'x'};
    Mark m2{Point{150,200},'y'};
    Mark m3{Point{200,200},'z'};
    win.attach(m1);
    win.attach(m2);
    win.attach(m3);
    
    win.wait_for_button();
}

// example usage of the Image class
void images()
{
    Simple_window win(Point{100,100},640,480,"Images");
    
    Image milky_way(Point{0,0},"MilkyWay.jpg");
    milky_way.scale(win.w(),win.h());
    Image moon(Point{0,0},"Moon.jpg");
    moon.set_mask(Point{350,350},300,300);
    
    win.attach(milky_way);
    win.attach(moon);
    
    win.wait_for_button();
}

// example usage of the Function, XAxis, and YAxis classes
void functions()
{
    Simple_window win(Point{100,100},640,480,"Functions");
    
    // constant
    Function fg_1{[](double x){return 1;},{-2.0,2.0},0.001,{-2.0,2.0},
        {320,240},200};
    fg_1.add_label(-1.5,"1");
    fg_1.set_color(Color_type::red);
    
    // line
    Function fg_2{[](double x){return 2*x;},{-2.0,2.0},0.001,{-2.0,2.0},
        {320,240},200};
    fg_2.add_label(-1.0,"2x");
    fg_2.set_color(Color_type::green);
    
    // parabola
    Function fg_3{[](double x){return x*x;},{-2.0,2.0},0.001,{-2.0,2.0},
        {320,240},200};
    fg_3.add_label(-0.5,"x^2");
    fg_3.set_color(Color_type::blue);
    
    // x axis
    XAxis xaxis{{-2.0,2.0},1,Point{320,240},200};
    xaxis.add_label(1.0,"1");
    xaxis.set_color(Color_type::magenta);
    
    // y-axis
    YAxis yaxis{{-2.0,2.0},1,Point{320,240},200};
    yaxis.add_label(0,"O");
    yaxis.add_label(1,"1");
    yaxis.set_color(Color_type::magenta);
    
    win.attach(fg_1);
    win.attach(fg_2);
    win.attach(fg_3);
    win.attach(xaxis);
    win.attach(yaxis);
    
    win.wait_for_button();
    
    // move the graphs around
    fg_1.move(100,-50);
    fg_2.move(100,-50);
    fg_3.move(100,-50);
    xaxis.move(100,-50);
    yaxis.move(100,-50);
    
    win.wait_for_button();
}

// another example usage of the Function, XAxis, and YAxis classes
void exponentials()
{
    Simple_window win(Point{100,100},640,480,"Exponential functions");
    
    Function e_gr{[](double x){return exp(x);},{-8.0,8.0},0.001,{-8.0,8.0},
        {320,240},400};
    e_gr.set_color(Color_type::red);
    e_gr.add_label(2,"e^x");
    
    // x axis
    XAxis xaxis{{-8.0,8.0},1,Point{320,240},400};
    xaxis.add_label(1.0,"1");
    xaxis.set_color(Color_type::magenta);
    
    // y-axis
    YAxis yaxis{{-8.0,8.0},1,Point{320,240},400};
    yaxis.add_label(0,"O");
    yaxis.add_label(1,"1");
    yaxis.set_color(Color_type::magenta);
    
    win.attach(e_gr);
    win.attach(xaxis);
    win.attach(yaxis);
    
    for (int n=0; n<10; n++) {
        ostringstream ss;
        ss << "exponential approx n= " << n;
        string t{ss.str()};
        win.set_title(t);
        Function ee_gr{[n](double x){return expe(x,n);},{-8.0,8.0},0.001,{-8.0,8.0},
            {320,240},400};
        win.attach(ee_gr);
        win.wait_for_button();
        win.detach(ee_gr);
    }
}

// example usage of polylines for representing data
void dataplots()
{
    Simple_window win(Point{100,100},640,480,"Data");
    
    // x axis
    XAxis xaxis{{2000,2009},1,Point{100,430},400};
    xaxis.add_label(2000,"2000",0,20);
    xaxis.add_label(2005,"2005",0,20);
    xaxis.add_label(2009,"2009",0,20);
    xaxis.set_color(Color_type::black);
    Text tx{Point{120,470},"Years"};
    
    // y axis
    YAxis yaxis{{0,100},10,Point{100,430},400};
    yaxis.add_label(0,"0%",-40,0);
    yaxis.add_label(50,"50%",-40,0);
    yaxis.add_label(100,"100%",-40,0);
    yaxis.set_color(Color_type::black);
    Text ty{Point{40,90},"Growth"};
    
    // data set 1
    Open_polyline poly1;
    vector<Point> ds_1 = {Point{2001,78}, Point{2002,70}, Point{2003,83},
                          Point{2004,75}, Point{2005,70}, Point{2006,72},
                          Point{2007,75}, Point{2008,77}, Point{2009,87} };
    for (auto p:ds_1) poly1.add_point(Point{xaxis.pos(p.x),yaxis.pos(p.y)});
    poly1.set_color(Color_type::red);
    Text tds_1{Point{xaxis.pos(2001),yaxis.pos(78)-30},"Dataset 1"};
    tds_1.set_color(Color_type::red);
    
    // data set 2
    Open_polyline poly2;
    vector<Point> ds_2 = {Point{2001,41}, Point{2002,50}, Point{2003,38},
                          Point{2004,51}, Point{2005,43}, Point{2006,52},
                          Point{2007,33}, Point{2008,44}, Point{2009,61} };
    for (auto p:ds_2) poly2.add_point(Point{xaxis.pos(p.x),yaxis.pos(p.y)});
    poly2.set_color(Color_type::yellow);
    Text tds_2{Point{xaxis.pos(2001),yaxis.pos(41)-50},"Dataset 2"};
    tds_2.set_color(Color_type::yellow);
    
    // data set 3
    Open_polyline poly3;
    vector<Point> ds_3 = {Point{2001,22}, Point{2002,14}, Point{2003,32},
                          Point{2004,21}, Point{2005,23}, Point{2006,27},
                          Point{2007,13}, Point{2008,20}, Point{2009,22} };
    for (auto p:ds_3) poly3.add_point(Point{xaxis.pos(p.x),yaxis.pos(p.y)});
    poly3.set_color(Color_type::blue);
    Text tds_3{Point{xaxis.pos(2001),yaxis.pos(22)-30},"Dataset 3"};
    tds_3.set_color(Color_type::blue);
    
    win.attach(tx);
    win.attach(ty);
    win.attach(tds_1);
    win.attach(tds_2);
    win.attach(tds_3);
    win.attach(poly1);
    win.attach(poly2);
    win.attach(poly3);
    win.attach(xaxis);
    win.attach(yaxis);
    
    win.wait_for_button();
}

// example usage of a button
void buttons()
{
    Simple_window win(Point{100,100},640,480,"Click me button");

    Button button{Point{100,100},100,50,"click me",[](Fl_Widget* w, void* a){},nullptr};
    button.set_button(Button_type::normal);
    button.set_when(When_type::release);

    win.attach(button);

    win.wait_for_button();
}

// example usage of an input and output box
void inoutbox()
{
    Simple_window win(Point{100,100},640,480,"Input & output boxes");

    In_box in_box{Point{100,100},100,50,"input:"};
    Out_box out_box{Point{200,300},100,50,"output:"};
    
    win.attach(in_box);
    win.attach(out_box);
    
    for(;;) {
        string input_text = in_box.get_input_text();
        if ( (input_text == string{"quit"}) ||
             win.is_button_pressed() )
            break;
        out_box.set_output_text(input_text);
        win.redraw();
        win.show();
    }
    
    win.hide();
}

// example usage of a menu
void menu()
{
    Simple_window win(Point{100,100},640,480,"Menu of buttons");

    Rectangle rect00{Point{400,200},200,100};
    rect00.set_color(Color_type::white);
    
    Button button1{Point{100,100}, 100, 50, "Blue", [](Fl_Widget* w, void* r){ static_cast<Rectangle*>(r)->set_color(Color_type::blue);}, (void *)&rect00};
    
    Button button2{Point{100,100}, 100, 50, "Red", [](Fl_Widget* w, void* r){static_cast<Rectangle*>(r)->set_color(Color_type::red);}, (void *)&rect00};
    
    Button button3{Point{100,100}, 100, 50, "Green", [](Fl_Widget* w, void* r){static_cast<Rectangle*>(r)->set_color(Color_type::green);}, (void *)&rect00};
    
    Menu menu(Point{100,100},Menu_type::vertical);
    menu.add_button(&button1);
    menu.add_button(&button2);
    menu.add_button(&button3);
    
    win.attach(rect00);
    win.attach(menu);

    win.wait_for_button();
}

// example of a class definition for a little application
class Lines_window : public Simple_window
{
public:
    Lines_window(Point xy,int w,int h,const char* title);
    virtual ~Lines_window() { color_menu.destroy(); }
    Open_polyline lines;
private:
    Button add_button;
    Button menu_button;
    Menu color_menu;
    In_box next_x;
    In_box next_y;
    Out_box xy_out;
    void add();
    void menu_pressed();
    void red_pressed();
    void blue_pressed();
    void green_pressed();
};

Lines_window::Lines_window(Point xy,int w,int h,const char* title) :
    Simple_window(xy, w, h, title),
    add_button{Point{x_max()-250,0},100,50,"Add point",
        [](Fl_Widget* w, void* lw) {static_cast<Lines_window*>(lw)->add();},this},
    menu_button{Point{x_max()-250,100},100,50,"Menu color",
    [](Fl_Widget* w, void* lw) {static_cast<Lines_window*>(lw)->menu_pressed();},this},
    color_menu(Point{x_max()-250,100},Menu_type::vertical),
    next_x{Point{100,0},50,20,"next x:"},
    next_y{Point{250,0},50,20,"next y:"},
    xy_out{Point{100,50},100,20,"current (x,y):"}
{
    color_menu.add_button(new Button{Point{0,0},100,50,"Red",[](Fl_Widget* w, void* lw) {static_cast<Lines_window*>(lw)->red_pressed();},this});
    color_menu.add_button(new Button{Point{0,0},100,50,"Blue",[](Fl_Widget* w, void* lw) {static_cast<Lines_window*>(lw)->blue_pressed();},this});
    color_menu.add_button(new Button{Point{0,0},100,50,"Green",[](Fl_Widget* w, void* lw) {static_cast<Lines_window*>(lw)->green_pressed();},this});
    color_menu.hide();
    attach(add_button);
    attach(menu_button);
    attach(color_menu);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    attach(lines);
}

void Lines_window::add()
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
    menu_button.hide();
    color_menu.show();
    redraw();
}

// callback called when the red button is pressed
void Lines_window::red_pressed()
{
    lines.set_color(Color_type::red);
    color_menu.hide();
    menu_button.show();
    redraw();
}

// callback called when the blue button is pressed
void Lines_window::blue_pressed()
{
    lines.set_color(Color_type::blue);
    color_menu.hide();
    menu_button.show();
    redraw();
}

// callback called when the green button is pressed
void Lines_window::green_pressed()
{
    lines.set_color(Color_type::green);
    color_menu.hide();
    menu_button.show();
    redraw();
}

// example of an application
void lineswindow()
{
    Lines_window win{Point{100,100},640,480,"lines"};
    
    //win.wait_for_exit();
    win.wait_for_button();
}

