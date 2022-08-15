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
    Graphics.hpp
    Hello_Fltk
  
    Created by Michele Iarossi on 21.01.22.
*/

#ifndef Graphics_hpp
#define Graphics_hpp

#include <string>
#include <vector>
#include <cmath>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

namespace mathsophy::graphics
{

using namespace std;

// typedefs
typedef std::function<double(double)> Function_type;
typedef void(*Callback_type)(Fl_Widget*, void*);

// simple definition of a point
struct Point
{
    // default "origin"
    int x{0};
    int y{0};
};

// declare equality and inequality operators
bool operator==(Point&, Point&);
bool operator!=(Point&, Point&);

//
// color enumerations
//

enum class Color_type
{
    red          = FL_RED,
    blue         = FL_BLUE,
    green        = FL_GREEN,
    yellow       = FL_YELLOW,
    white        = FL_WHITE,
    black        = FL_BLACK,
    magenta      = FL_MAGENTA,
    cyan         = FL_CYAN,
    dark_red     = FL_DARK_RED,
    dark_yellow  = FL_DARK_YELLOW,
    dark_blue    = FL_DARK_BLUE,
    dark_magenta = FL_DARK_MAGENTA,
    dark_cyan    = FL_DARK_CYAN
};

//
// Conversion functions Color_type <-> Fl_Color
//

Color_type to_color_type(Fl_Color);
Fl_Color   to_fl_color(Color_type);
Fl_Color   to_fl_color(int);

//
// style enumerations
//

enum class Style_type
{
    solid      = FL_SOLID,       // -------
    dash       = FL_DASH,        // - - - -
    dot        = FL_DOT,         // .......
    dashdot    = FL_DASHDOT,     // - . - .
    dashdotdot = FL_DASHDOTDOT,  // - . . -
};

//
// Conversion functions Style_type <-> int
//

Style_type to_style_type(int);
int to_line_style(Style_type);

//
// font enumerations
//

enum class Font_type
{
    helvetica             = FL_HELVETICA,
    helvetica_bold        = FL_HELVETICA_BOLD,
    helvetica_italic      = FL_HELVETICA_ITALIC,
    helvetica_bold_italic = FL_HELVETICA_BOLD_ITALIC,
    courier               = FL_COURIER,
    courier_bold          = FL_COURIER_BOLD,
    courier_italic        = FL_COURIER_ITALIC,
    courier_bold_italic   = FL_COURIER_BOLD_ITALIC,
    times                 = FL_TIMES,
    times_bold            = FL_TIMES_BOLD,
    times_italic          = FL_TIMES_ITALIC,
    times_bold_italic     = FL_TIMES_BOLD_ITALIC,
    symbol                = FL_SYMBOL,
    screen                = FL_SCREEN,
    screen_bold           = FL_SCREEN_BOLD,
    zapf_dingbats         = FL_ZAPF_DINGBATS
};

//
// Conversion functions Font_type <-> int
//

Font_type to_font_type(int);
int to_fl_font(Font_type);

//
// transparency enumerations
//

enum class Transparency_type
{
    invisible            = 0,
    visible              = 255
};

//
// callback event enumerations
//

enum class When_type
{
    never             = FL_WHEN_NEVER,
    changed           = FL_WHEN_CHANGED,
    not_changed       = FL_WHEN_NOT_CHANGED,
    release           = FL_WHEN_RELEASE,
    release_always    = FL_WHEN_RELEASE_ALWAYS,
    enter_key         = FL_WHEN_ENTER_KEY,
    enter_key_always  = FL_WHEN_ENTER_KEY_ALWAYS,
    enter_key_changed = FL_WHEN_ENTER_KEY_CHANGED
};

//
// Conversion functions When_type <-> Fl_When
//

When_type to_when_type(Fl_When);
Fl_When  to_fl_when(When_type);

//
// button enumerations
//

enum class Button_type
{
    normal  = FL_NORMAL_BUTTON,
    toggle  = FL_TOGGLE_BUTTON,
    radio   = FL_RADIO_BUTTON,
    hidden  = FL_HIDDEN_BUTTON
};

//
// Conversion functions Button_type <-> int
//

Button_type to_button_type(int);
int to_fl_button(Button_type);

//
// Menu enumerations
//

enum class Menu_type
{
    horizontal  = 0,
    vertical    = 1
};

//
// Generic window
//

class Widget;

class Generic_window : public Fl_Window
{
public:
    // constructor
    Generic_window(Point tl, int w, int h, const char *l);
    // virtual destructor
    virtual ~Generic_window() { clear(); }
    // attach to window
    virtual void attach(Fl_Widget& w) { add(w); }
    virtual void attach(Widget& w);
    // remove from window
    virtual void detach(Fl_Widget& w) { remove(w); }
    // set title of the window
    void set_title(const string& t) { label(t.c_str()); }
    // put on top a widget
    void put_on_top(Fl_Widget& w) { add(w); }
    // callback
    void exit_callback(Fl_Widget *w) { exit(0); }
    static void static_exit_callback(Fl_Widget *w, void *win) {
        static_cast<Generic_window *>(win)->exit_callback(w);
    }
    // override show
    void show();
    // wait for window close
    void wait_for_exit();
    // maximum x and y
    int x_max() { return w(); }
    int y_max() { return h(); }
};

//
// Simple window
//

class Simple_window : public Generic_window
{
public:
    // constructor
    Simple_window(Point tl, int w, int h, const char *l);
    // virtual destructor
    virtual ~Simple_window() { delete b; }
    // override of attach
    void attach(Fl_Widget& w);
    void attach(Widget& w);
    // callbacks
    void next_callback(Fl_Widget *w) { button_pressed = true; }
    static void static_next_callback(Fl_Widget *w, void *win) {
        static_cast<Simple_window *>(win)->next_callback(w);
    }
    // helper methods
    void wait_for_button();
    bool is_button_pressed();
private:
    Fl_Button* b; // the Next button that appears top right
    bool button_pressed = false;
};

//
// Widget
//

class Widget : public Fl_Widget
{
public:
    // no copy constructor allowed
    Widget(const Widget&) = delete;
    // no copy assignment allowed
    Widget& operator=(const Widget&) = delete;
    // virtual destructor
    virtual ~Widget() {}
    // virtual draw() method to be provided by
    // the derived class, overrides Fl_Widget::draw
    virtual void draw() = 0;
    // virtual move() method to be provided by
    // the derived class
    virtual void move(int dx, int dy) = 0;
    virtual void move(Point p) { move(p.x-get_tl().x,p.y-get_tl().y ); }
    // overrides Fl_Widget::redraw()
    void redraw();
    // attach internal FLTK widgets to the window
    virtual void attach(Generic_window* w) { win = w; }
    // getter and setter methods
    Generic_window* get_win() const { return win; }
    void set_transparency(Transparency_type t) { set_transparency_widget(t); }
    Transparency_type get_transparency() const { return trans; }
    int get_w() const {return (br.x-tl.x); }
    int get_h() const {return (br.y-tl.y); }
    Point get_tl() const  { return tl; }
    Point get_br() const  { return br; }
    // helper methods
    bool is_visible() { return (trans == Transparency_type::visible); }
protected:
    // Widget is an abstract class, no instances of Widget can be created!
    Widget() : Fl_Widget(0,0,0,0) {}
    // resize methods to be overridden by derived classes
    virtual void resize_widget(Point a, Point b);
    virtual void resize_widget(Point p, int w, int h);
    // call Fl_Widget::resize
    virtual void resize_widget() { resize(tl.x,tl.y,br.x-tl.x,br.y-tl.y); }
    // protected setter methods
    void set_transparency_widget(Transparency_type t) { trans = t; }
    void set_tl(Point p) { tl = p; }
    void set_br(Point p) { br = p; }
    // other helper methods
    // update top-left and bottom-right corners
    void update_tl_br(const Point& p);
private:
    Transparency_type trans{Transparency_type::visible};
    Point tl{};                       // top-left corner
    Point br{};                       // bottom-right corner
    Generic_window *win;              // pointer to the containing window
};

//
// Shape
//

class Shape : public Widget
{
public:
    // no copy constructor allowed
    Shape(const Shape&) = delete;
    // no copy assignment allowed
    Shape& operator=(const Shape&) = delete;
    // virtual destructor
    virtual ~Shape() {}
    // overrides Fl_Widget::draw()
    void draw();
    // moves a shape relative to the current
    // top-left corner (call of redraw()
    // might be needed)
    void move(int dx, int dy);
    // setter and getter methods for
    // color, style, font, transparency
    // (call of redraw() might be needed)
    void set_color(Color_type c);
    void set_color(int c);
    Color_type get_color() const { return to_color_type(new_color); }
    void set_style(Style_type s, int w);
    Style_type get_style() const { return to_style_type(line_style); }
    void set_font(Font_type f, int s);
protected:
    // Shape is an abstract class, no instances of Shape can be created!
    Shape() : Widget() {}
    // protected virtual methods to be overridden
    // by derived classes
    virtual void draw_shape() = 0;
    virtual void move_shape(int dx, int dy) = 0;
    // protected setter methods
    virtual void set_color_shape(Color_type c) {
        new_color = to_fl_color(c);
    }
    virtual void set_color_shape(int c) {
        new_color = to_fl_color(c);
    }
    virtual void set_style_shape(Style_type s, int w);
    virtual void set_font_shape(Font_type f, int s);
    // helper methods for FLTK style and font
    void set_fl_style();
    void restore_fl_style();
    void set_fl_font();
    void restore_fl_font() { fl_font(old_font,old_fontsize); }
    // test method for checking resize calls
    void draw_outline();
private:
    Fl_Color new_color{Fl_Color()};   // color
    Fl_Color old_color{Fl_Color()};   // old color
    Fl_Font new_font{0};              // font
    Fl_Font old_font{0};              // old font
    Fl_Fontsize new_fontsize{0};      // font size
    Fl_Fontsize old_fontsize{0};      // old font size
    int line_style{0};                // line style
    int line_width{0};                // line width
};

//
// Line
//

class Line : public Shape
{
public:
    // constructors
    Line() {}
    Line(pair<Point,Point> line) : l{line} {
        resize_widget(l.first,l.second);
    }
    // virtual destructor
    virtual ~Line() {}
    // getter and setter methods
    pair<Point,Point> get_line() const { return l; }
    void set_line(pair<Point,Point> line) { l = line; }
protected:
    // overridden member methods
    void draw_shape() { fl_line(l.first.x, l.first.y, l.second.x, l.second.y); }
    void move_shape(int dx, int dy);
private:
    pair<Point,Point> l; // a line is a pair of points
};

//
// Lines
//

class Lines : public Shape
{
public:
    // constructors
    Lines() {}
    Lines(initializer_list< pair<Point,Point> > lst) {
        for (auto line : lst) add_line(line);
    }
    // virtual destructor
    virtual ~Lines() { for (auto l: vl) delete l; }
    // add a line to the vector of lines
    void add_line(pair<Point,Point> line);
    // remove the i-th line
    void remove_line(size_t i);
    // getter and setter methods
    pair<Point,Point> get_line(size_t i) const { return *vl.at(i); }
    void set_line(size_t i, pair<Point,Point> line);
    // helper methods
    size_t get_nb_lines() const { return vl.size(); }
    bool empty_lines() const { return vl.empty(); }
protected:
    // overridden member methods
    void draw_shape() { for (auto l: vl) fl_line(l->first.x, l->first.y, l->second.x, l->second.y); }
    void move_shape(int dx, int dy);
    void resize_widget();
private:
    vector< pair<Point,Point>* > vl; // vector of lines where a line is
                                     // defined by a pair of points
};

//
// Open_polyline
//

class Open_polyline : public Shape
{
public:
    // constructors
    Open_polyline() {}
    Open_polyline(initializer_list<Point> lst) {
        for (auto pnt : lst) add_point(pnt);
    }
    // virtual destructor
    virtual ~Open_polyline()        { for (auto pnt: vp) delete pnt; }
    // add a new point 
    void add_point(Point p);
    // remove the i-th point
    void remove_point(size_t i);
    // getter and setter methods
    Point get_point(size_t i) const { return *vp.at(i);  }
    void set_point(size_t i, Point pnt);
    // helper methods
    size_t get_nb_points() const    { return vp.size();  }
    bool empty_points() const       { return vp.empty(); }
protected:
    // overridden member methods
    void draw_shape();
    void move_shape(int dx,int dy);
    void resize_widget();
private:
    vector<Point*> vp; // vector of points to be connected
};

//
// Closed_polyline
//

class Closed_polyline : public Open_polyline
{
public:
    // use the constructors of Open_polyline
    using Open_polyline::Open_polyline;
    // virtual destructor
    virtual ~Closed_polyline() {}
protected:
    // redefine Open_polyline::draw_shape
    void draw_shape();
};

//
// Polygon
//

class Polygon : public Closed_polyline
{
public:
    // use the constructors of Closed_polyline
    using Closed_polyline::Closed_polyline;
    // virtual destructor
    virtual ~Polygon() {}
protected:
    // redefine Closed_polyline::draw_shape
    void draw_shape();
private:
    // detects if there is an intersection
    bool intersect();
    // given 2 lines tests for intersection
    bool lines_intersect(Point&,Point&,Point&,Point&);
};

//
// Rectangle
//

class Rectangle : public Shape
{
public:
    // constructors
    Rectangle(Point a, int w, int h) { resize_widget(a,Point{a.x+w,a.y+h});}
    Rectangle(Point a, Point b)      { resize_widget(a,b); }
    // virtual destructor
    virtual ~Rectangle() {}
    // getter and setter methods
    void set_outline(bool flag) { outline = flag; }
    bool get_outline() const    { return outline; }
    void set_filled(bool flag)  { filled = flag;  }
    bool get_filled() const     { return filled;  }
protected:
    // overridden member methods
    void draw_shape();
    void move_shape(int dx, int dy);
private:
    bool outline{true}; // outline must be drawn
    bool filled{true};  // inside must be color filled
};

//
// Text
//

class Text : public Shape
{
public:
    // constructors
    Text() {}
    Text(Point a, const string& s) : bl{a}, t{s} {
        // resize once else the text is not shown
        resize_text();
    }
    // virtual destructor
    virtual ~Text() {}
    // getter and setter methods
    void   set_text(const string& s);
    string get_text(void) const { return t; }
    void   set_bl(Point p);
    Point  get_bl() const { return bl; }
protected:
    // overridden member methods
    void draw_shape();
    void move_shape(int dx,int dy);
    // resize according to text size
    void resize_text();
private:
    Point bl{}; // bottom left corner
    string t{}; // text as a string
};

//
// Circle
//

class Circle : public Shape
{
public:
    // constructors
    Circle(Point a, int rr) : c{a}, r{rr} {
        resize_widget(Point{c.x-r,c.y-r}, Point{c.x+r,c.y+r});
    }
    // virtual destructor
    virtual ~Circle() {}
    // getter and setter methods
    Point get_center() const { return c; }
    void  set_center(Point p);
    int   get_radius() const { return r; }
    void  set_radius(int rr);
protected:
    // overridden member methods
    void draw_shape();
    void move_shape(int dx,int dy);
private:
    Point c{}; // center
    int r{0};  // radius
};

//
// Ellipse
//

class Ellipse : public Shape
{
public:
    // constructors
    Ellipse(Point cc, int aa, int bb) : c{cc}, a{aa}, b{bb} {
        resize_widget(Point{c.x-a,c.y-b},Point{c.x+a,c.y+b});
    }
    // virtual destructor
    virtual ~Ellipse() {}
    // getter and setter methods
    Point get_center() const { return c; }
    void  set_center(Point p);
    int   get_major()  const { return a; }
    void  set_major(int aa);
    int   get_minor()  const { return b; }
    void  set_minor(int bb);
protected:
    // overridden member methods
    void draw_shape();
    void move_shape(int dx,int dy);
private:
    Point c{}; // center
    int  a{0}; // width
    int  b{0}; // height
};

//
// Marked polyline
//

class Marked_polyline : public Open_polyline
{
public:
    // constructors
    Marked_polyline(const vector<string>& mm={""}) : m{mm}, Open_polyline() {
        if ( (m.size() == 1) && (m[0] == "") )
            m[0] = "*";
    }
    Marked_polyline(const vector<string>& mm, initializer_list<Point> lst) : m{mm}, Open_polyline(lst) {
        if ( (m.size() == 1) && (m[0] == "") )
            m[0] = "*";
    }
    // virtual destructor
    virtual ~Marked_polyline() {}
    // deletes i-th mark
    void remove_mark(size_t i);
    // getter and setter methods
    string get_mark(size_t i) const { return m.at(i); }
    void   set_mark(size_t i, string mrk);
    // helper methods
    size_t get_nb_marks() const     { return m.size(); }
    bool empty_marks() const { return m.empty(); }
protected:
    // overridden member methods
    void draw_shape();
    void resize_widget();
    // draw all the text markers
    void draw_text();
private:
    vector<string> m; // vector of marks
};

//
// Marks
//

class Marks : public Marked_polyline
{
public:
    // constructors
    Marks(string m="") : Marked_polyline({m}) {}
    Marks(const vector<string>& m, initializer_list<Point> lst) : Marked_polyline(m,lst) {}
    Marks(string m, initializer_list<Point> lst) : Marked_polyline({m},lst) {}
    // virtual destructor
    virtual ~Marks() {}
protected:
    // overridden member methods
    void draw_shape();
};

//
// Mark
//

class Mark : public Marks
{
public:
    // constructor
    Mark(Point p,char c) : Marks({string{1,c}},{p}) {}
    // virtual destructor
    virtual ~Mark() {}
};

//
// Image
//

class Image : public Shape
{
public:
    // constructors
    Image(Point pos, string name);
    // virtual destructor
    virtual ~Image() { if (img) img->release(); }
    // set visible area
    void set_mask(Point o, int w, int h);
    // scale the image
    void scale(int w, int h) { cpy = img->copy(w,h);
        resize_widget(get_tl(),Point{get_tl().x+w,get_tl().y+h});
    }
    // getter and setter methods
    Point get_orig() const { return orig; }
protected:
    // overridden member methods
    void draw_shape();
    void move_shape(int dx,int dy);
private:
    Fl_Shared_Image *img{nullptr}; // FLTK image pointer
    Fl_Image *cpy{nullptr};        // scaled image
    string fn{};                   // file name
    Point orig{};                  // origin
};

//
// Function
//

class Function : public Shape
{
public:
    // constructor
    Function (Function_type f,pair<double,double> rx, double d, pair<double,double> ry,Point p, int lx, double ar=1);
    // virtual destructor
    virtual ~Function();
    // add a label
    void add_label(double x,string txt,int dx=0,int dy=0);
    // getter and setter methods
    Point get_orig() const { return orig; }
    vector<Text*> labels; // public vector of labels
protected:
    // overridden member methods
    void draw_shape();
    void move_shape(int dx,int dy);
    // calculates the function values
    void calculate_y();
    // calculate actual points to be drawn
    void calculate_points();
private:
    Function_type func;                // function
    vector<double> y;                  // function values
    vector<double> x;                  // domain values
    vector<Point*> vp;                 // actual points to be drawn
    pair<double,double> x_range{0,0};  // [x_min,x_max)
    pair<double,double> y_range{0,0};  // (y_min,y_max)
    Point orig{};                      // origin
    int len_x{0};                      // x-axis length in pixels
    int len_y{0};                      // y-axis length in pixels
    double x_min{0};                   // minimum abscissa
    double x_max{0};                   // maximum abscissa
    double x_step{0};                  // x increment
    double y_min{0};                   // minimum function value
    double y_max{0};                   // maximum function value
    double sx{0};                      // scale factor for the x-axis
    double sy{0};                      // scale factor for the y-axis
    double ratio{0};                   // aspect ratio
};

//
// XAxis
//

class XAxis : public Shape
{
public:
    // constructor
    XAxis(pair<double,double> rx, double d, Point p, int lx, int ln=5);
    // virtual destructor
    virtual ~XAxis() { for (auto l : labels) delete l; }
    // add label
    void add_label(double x, string txt, int dx=0, int dy=0);
    // getter and setter methods
    Point get_orig() const { return orig; }
    // helper methods
    int pos(double x) { return orig.x + int(round(x*sx)); }
    vector<Text*> labels;   // vector of labels
    Lines notches;          // lines representing the notches
    Line axis;              // single axis line
protected:
    // overridden member methods
    void draw_shape();
    void move_shape(int dx, int dy);
    void set_color_shape(Color_type c);
    // determine notches positions
    void calculate_x();
    // calculate notches lines
    void calculate_notches();
private:
    Point orig{};                      // origin
    pair<double,double> x_range{0,0};  // [x_min,x_max)
    vector<double> x;                  // position of every notch
    int len_x{0};                      // x-axis length in pixels
    int len_n{0};                      // notch length in pixels
    double x_min{0};                   // minimum abscissa
    double x_max{0};                   // maximum abscissa
    double x_step{0};                  // x increment
    double sx{0};                      // scale factor for the x-axis
};

//
// YAxis
//

class YAxis : public Shape
{
public:
    // constructor
    YAxis(pair<double,double> ry, double d, Point p, int ly, int ln=5);
    // virtual destructor
    virtual ~YAxis() { for (auto l : labels) delete l; }
    // add label
    void add_label(double y,string txt,int dx=0,int dy=0);
    // getter and setter methods
    Point get_orig() const { return orig; }
    // helper methods
    int pos(double y) { return orig.y - int(round(y*sy)); }
    vector<Text*> labels;   // vector of labels
    Lines notches;          // lines representing the notches
    Line axis;              // single axis line
protected:
    // overridden member methods
    void draw_shape();
    void move_shape(int dx, int dy);
    void set_color_shape(Color_type c);
    // determine notches positions
    void calculate_y();
    // calculate notches lines
    void calculate_notches();
private:
    Point orig{};                      // origin
    pair<double,double> y_range{0,0};  // [y_min,y_max)
    vector<double> y;                  // position of every notch
    int len_y{0};                      // y-axis length in pixels
    int len_n{0};                      // notch length in pixels
    double y_min{0};                   // minimum ordinate
    double y_max{0};                   // maximum ordinate
    double y_step{0};                  // y increment
    double sy{0};                      // scale factor for the y-axis
};

//
// Button
//

class Button : public Widget
{
public:
    // constructor
    Button(Point p, int w, int h, const string s, Callback_type cb, void* d);
    // virtual destructor
    virtual ~Button() { if (b) delete b; }
    // show button
    void show() { set_transparency(Transparency_type::visible); }
    // hide button
    void hide() { set_transparency(Transparency_type::invisible); }
    // attach internal button
    void attach(Generic_window* w) { Widget::attach(w); w->add(*b); }
    // overridden member methods
    void draw();
    void move(int dx, int dy);
    // setter and getter functions
    void set_when(When_type w);
    When_type get_when() const { return to_when_type(fl_when); }
    void set_button(Button_type b);
    Button_type get_button() const { return to_button_type(fl_button); }
    void set_label(string s) { text = s; }
    string get_label() const { return text; }
private:
    Fl_Button *b{nullptr};             // pointer to FLTK button
    Fl_When fl_when{FL_WHEN_RELEASE};  // when the callback is to be called
    int fl_button{FL_NORMAL_BUTTON};   // button type
    string text;                       // text to display on the button
    void *data;                        // pointer data to the button callback
};

//
// In_box
//

class In_box : public Widget
{
public:
    // constructor
    In_box(Point p, int w, int h, const string s);
    // virtual destructor
    virtual ~In_box() { if (in) delete in; }
    // callback
    static void static_input_callback(Fl_Widget *fl_w, void *widget) {
        static_cast<In_box*>(widget)->input_callback();
    }
    void input_callback() { in_text = string{in->value()}; }
    // show button
    void show() { set_transparency(Transparency_type::visible); }
    // hide button
    void hide() { set_transparency(Transparency_type::invisible); }
    // attach internal button
    void attach(Generic_window* w) { Widget::attach(w); w->add(in); }
    // overridden member methods
    void draw();
    void move(int dx, int dy);
    // setter and getter functions
    string get_input_text()    { return in_text; }
    int    get_input_integer() { return stoi(in_text); }
    void   set_label(string s) { text = s; }
    string get_label() const   { return text; }
private:
    Fl_Input *in{nullptr};  // pointer to FLTK input box
    string in_text{};       // input text
    string text{};          // label
};

//
// Out_box
//

class Out_box : public Widget
{
public:
    // constructor
    Out_box(Point p, int w, int h, const string s);
    // virtual destructor
    virtual ~Out_box() { if (out) delete out; }
    // show button
    void show() { set_transparency(Transparency_type::visible); }
    // hide button
    void hide() { set_transparency(Transparency_type::invisible); }
    // attach internal button
    void attach(Generic_window* w) { Widget::attach(w); w->add(out); }
    // overridden member methods
    void draw();
    void move(int dx, int dy);
    // setter and getter functions
    void   set_output_text(string s) { out_text = s; }
    void   set_label(string s)       { text = s; }
    string get_label() const         { return text; }
private:
    Fl_Output *out{nullptr};   // pointer to FLTK output box
    string out_text{};         // output text
    string text{};             // label
};

//
// Menu
//

class Menu : public Widget
{
public:
    // constructor
    Menu(Point p, Menu_type t = Menu_type::vertical,
         int g = 5) : type{t}, gap{g} { resize_widget(p,width,height); }
    // vistual destructor
    virtual ~Menu() {}
    // show button
    void show() { set_transparency(Transparency_type::visible); }
    // hide button
    void hide() { set_transparency(Transparency_type::invisible); }
    // attach Menu widget and its button to the window
    void attach(Generic_window* w);
    // add new selection button
    void add_button(Button *b);
    // deallocate all selection buttons
    void destroy();
    // overridden member methods
    void draw();
    void move(int dx, int dy);
private:
    vector<Button*> selection;     // vector of buttons for the available selections
    Menu_type type;                // either vertical or horizontal
    int gap{0};                    // gap between the buttons
    int width{0};                  // total width
    int height{0};                 // total height
};

}
#endif /* Graphics_hpp */
