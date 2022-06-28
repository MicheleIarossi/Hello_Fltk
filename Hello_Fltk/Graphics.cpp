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
    along with this program.  If not, see <https:www.gnu.org/licenses/>.
*/

/*
    Graphics.cpp
    Hello_Fltk
  
    Created by Michele Iarossi on 21.01.22.
*/

#include "Graphics.hpp"

namespace mathsophy::graphics
{

//
// Equality and inequality operators on points
//

bool operator==(Point& p, Point& q)
{
    return (q.x == p.x) && (q.y == p.y);
}

bool operator!=(Point& q, Point& p)
{
    return (q.x != p.x) || (q.y != p.y);
}

//
// Conversion functions Color_type <-> Fl_Color
//

Color_type to_color_type(Fl_Color c)
{
    return Color_type(c);
}

Fl_Color to_fl_color(Color_type c)
{
    return Fl_Color(c);
}

Fl_Color to_fl_color(int c)
{
    return Fl_Color(c);
}

//
// Conversion functions Style_type <-> int
//

Style_type to_style_type(int s)
{
    return Style_type(s);
}

int to_line_style(Style_type s)
{
    return int(s);
}

//
// Conversion functions Font_type <-> int
//

Font_type to_font_type(int f)
{
    return Font_type(f);
}

int to_fl_font(Font_type f)
{
    return int(f);
}

//
// Conversion functions When_type <-> Fl_When
//

When_type to_when_type(Fl_When w)
{
    return When_type(w);
}

Fl_When to_fl_when(When_type w)
{
    return Fl_When(w);
}

//
// Conversion functions Button_type <-> int
//

Button_type to_button_type(int b)
{
    return Button_type(b);
}

int to_fl_button(Button_type b)
{
    return int(b);
}

//
// Generic window
//

// constructor
Generic_window::Generic_window(Point tl, int w, int h, const char *l = nullptr) : Fl_Window{tl.x,tl.y,w,h,l}
{
    // manual addition of widgets
    Fl_Group::current(NULL);
    // exits when window is closed
    this->callback(static_exit_callback,this);
}

// add to window
void Generic_window::attach(Widget& w)
{
    add(&w);
    w.attach(this);
}

// override show
void Generic_window::show()
{
    Fl_Window::show();
    wait_for_expose();
    Fl::wait(0);
}

// wait for window close
void Generic_window::wait_for_exit()
{
    redraw();
    show();
    while (1) Fl::wait();
}

//
// Simple window
//

// constructor
Simple_window::Simple_window(Point tl, int w, int h, const char *l = nullptr) : Generic_window{tl,w,h,l}
{
    b = new Fl_Button(w-100,0,100,50,"Next");
    b->type(FL_NORMAL_BUTTON);
    b->when(FL_WHEN_RELEASE);
    b->callback(static_next_callback,this);
    add(*b);
}

// redefinition of attach
void Simple_window::attach(Fl_Widget& w)
{
    Generic_window::attach(w);
    // keeps the button in the foreground all the time!
    add(*b);
}

void Simple_window::attach(Widget& w)
{
    Generic_window::attach(w);
    // keeps the button in the foreground all the time!
    add(*b);
}

void Simple_window::wait_for_button()
{
    redraw();
    show();
    while( !is_button_pressed() ) Fl::wait();
}

bool Simple_window::is_button_pressed()
{
    if (button_pressed)
    {
        button_pressed = false;
        return true;
    }
    else return false;
}

//
// Widget
//

// overrides Fl_Widget::redraw()
void Widget::redraw()
{
    Fl_Widget::redraw();
    Fl::wait(0);
}

// getter and setter functions
void Widget::set_transparency(Transparency_type t)
{
    set_transparency_widget(t);
}

// resize functions
void Widget::resize_widget(Point a, Point b)
{
    set_tl(a);
    set_br(b);
    resize(tl.x,tl.y,br.x-tl.x,br.y-tl.y);
}

void Widget::resize_widget(Point p, int w, int h)
{
    set_tl(p);
    set_br(Point{p.x+w,p.y+h});
    resize(p.x,p.y,w,h);
}

// update top-left and bottom-right corners
void Widget:: update_tl_br(const Point& p)
{
    if (p.x < tl.x)      tl.x = p.x;
    else if (p.x > br.x) br.x = p.x;
    if (p.y < tl.y)      tl.y = p.y;
    else if (p.y > br.y) br.y = p.y;
}

//
// Shape
//

// overrides Widget::draw()
void Shape::draw()
{
    set_fl_style();
    if ( is_visible() ) draw_shape();
    restore_fl_style();
}

// moves a shape relative to the current
// top-left corner (call of redraw()
// might be needed)
void Shape::move(int dx, int dy)
{
    hide();
    move_shape(dx,dy);
    show();
}

// setter and getter functions for
// color, style, font, transparency
// (call of redraw() might be needed)
void Shape::set_color(Color_type c)
{
    hide();
    set_color_shape(c);
    show();
}

void Shape::set_color(int c)
{
    hide();
    set_color_shape(c);
    show();
}

void Shape::set_style(Style_type s, int w)
{
    hide();
    set_style_shape(s,w);
    show();
}

void Shape::set_font(Font_type f, int s)
{
    hide();
    set_font_shape(f,s);
    show();
}

void Shape::set_style_shape(Style_type s, int w)
{
    line_style = to_line_style(s);
    line_width = w;
}

void Shape::set_font_shape(Font_type f, int s)
{
    new_font = to_fl_font(f);
    new_fontsize = s;
}

// helper functions for FLTK style and font
void Shape::set_fl_style()
{
    fl_line_style(line_style,line_width);
    old_color = fl_color();
    fl_color(new_color);
}

void Shape::restore_fl_style()
{
    fl_color(old_color);
    fl_line_style(0);
}

void Shape::set_fl_font()
{
    old_font = fl_font();
    old_fontsize = fl_size();
    fl_font(new_font,new_fontsize);
}

void Shape::draw_outline()
{
    // outline in black
    fl_color(FL_BLACK);
    fl_rect(get_tl().x,get_tl().y,w(),h());
}

//
// Line
//

void Line::move_shape(int dx, int dy)
{
    l.first.x  += dx;  l.first.y += dy;
    l.second.x += dx; l.second.y += dy;
    resize_widget(l.first,l.second);
}

//
// Lines
//

void Lines::add_line(pair<Point,Point> line)
{
    pair<Point,Point>* l = new pair<Point,Point>;
    l->first = line.first; l->second = line.second;
    vl.push_back(l);
    resize_widget();
}

void Lines::set_line(size_t i, pair<Point,Point> line)
{
    pair<Point,Point>* l = new pair<Point,Point>;
    l->first = line.first; l->second = line.second;
    delete vl.at(i);
    vl.at(i) = l;
    resize_widget();
}

void Lines::remove_line(size_t i)
{
    delete vl.at(i);
    vl.erase(vl.begin()+i);
    resize_widget();
}

void Lines::resize_widget()
{
    // nothing to do if empty vector of lines
    if (vl.empty())
        return;
    set_tl(vl[0]->first);
    set_br(vl[0]->second);
    for (auto l : vl) {
        update_tl_br(l->first);
        update_tl_br(l->second);
    }
    Widget::resize_widget();
}

void Lines::move_shape(int dx, int dy)
{
    for (auto l : vl) {
        l->first.x += dx; l->first.y += dy;
        l->second.x += dx; l->second.y += dy;
    }
    resize_widget();
}

//
// Open_polyline
//

void Open_polyline::set_point(size_t i, Point pnt)
{
    Point* p = new Point;
    *p = pnt;
    delete vp.at(i);
    vp.at(i) = p;
    resize_widget();
}

void Open_polyline::add_point(Point p)
{
    vp.push_back(new Point{p});
    resize_widget();
}

void Open_polyline::remove_point(size_t i)
{
    delete vp.at(i);
    vp.erase(vp.begin()+i);
    resize_widget();
}

void Open_polyline::draw_shape()
{
    for (size_t n=0; n < vp.size()-1; n++)
        fl_line(vp[n]->x, vp[n]->y, vp[n+1]->x, vp[n+1]->y);
}

void Open_polyline::resize_widget()
{
    // nothing to do if empty vector of points
    if (vp.empty())
        return;
    set_tl(*vp[0]);
    set_br(*vp[0]);
    for (auto p : vp)
        update_tl_br(*p);
    Widget::resize_widget();
}

void Open_polyline::move_shape(int dx,int dy)
{
    for (auto p : vp) {
        p->x += dx;
        p->y += dy;
    }
    resize_widget();
}

//
// Closed_polyline
//

void Closed_polyline::draw_shape()
{
    Open_polyline::draw_shape();
    // last line in order to close the shape
    fl_line(get_point(get_nb_points()-1).x, get_point(get_nb_points()-1).y, get_point(0).x, get_point(0).y);
}

//
// Polygon
//

void Polygon::draw_shape()
{
    if (!intersect())
        Closed_polyline::draw_shape();
    else throw runtime_error("Polygon::draw_shape(): Intersections found!");
}

bool Polygon::intersect()
{
    // build vector of lines
    vector< pair<Point,Point>* > vl;
    for (size_t i=0; i < get_nb_points(); i++)
    {
        // a line is represented as a pair of points
        pair<Point,Point>* l = new pair<Point,Point>;
        l->first  = get_point(i);
        l->second = get_point( (i+1) % get_nb_points() );
        vl.push_back(l);
    }
    
    // double loop over the lines
    for (size_t i=0; i < vl.size(); i++)
    {
        // indeces of the adjacent lines
        size_t prev = (i-1) % vl.size();
        size_t next = (i+1) % vl.size();
        for (size_t j=i+1; j < vl.size(); j++)
        {
            // skip the adjacent lines
            if ( (j != prev) && (j != next) )
            {
                Point Pa = vl[i]->first;
                Point Pb = vl[i]->second;
                Point Pc = vl[j]->first;
                Point Pd = vl[j]->second;
                if (lines_intersect(Pa,Pb,Pc,Pd))
                {
                    // free storage
                    for (auto l : vl) delete l;
                    return true;
                }
            }
        }
    }
    
    // free storage
    for (auto l : vl) delete l;
    return false;
}

bool Polygon::lines_intersect(Point& Pa, Point& Pb, Point& Pc, Point& Pd)
{
    // naive algorithm: standard solution of intersecting lines
    int m1 = Pb.y - Pa.y;
    int m2 = Pb.x - Pa.x;
    int m3 = Pd.y - Pc.y;
    int m4 = Pd.x - Pc.x;
    int m5 = Pc.y - Pa.y;
    int m6 = Pc.x - Pa.x;
    
    long m = m1*m4 - m2*m3;
    long n = m1*m4*Pa.x + m2*(m4*m5 - m3*Pc.x);
    long o = m1*(m4*m5 - m3*m6) + m*Pa.y;
    
    // no division required but we need to check the sign of m
    // xp = double(n)/m
    // yp = double(o)/m
    if (m > 0)
    {
        if ( ((m*Pc.x <= n) && (n <= m*Pd.x)) &&
             ((m*Pa.x <= n) && (n <= m*Pb.x)) &&
             ((m*Pb.y <= o) && (o <= m*Pa.y)) &&
             ((m*Pc.y <= o) && (o <= m*Pd.y))
           ) return true;
        else return false;
    } else
    {
        if ( ((m*Pc.x >= n) && (n >= m*Pd.x)) &&
             ((m*Pa.x >= n) && (n >= m*Pb.x)) &&
             ((m*Pb.y >= o) && (o >= m*Pa.y)) &&
             ((m*Pc.y >= o) && (o >= m*Pd.y))
           ) return true;
        else return false;
    }    
}

//
// Rectangle
//

void Rectangle::draw_shape()
{
    Point tl = get_tl();
    Point br = get_br();
    if (filled)
        fl_rectf(tl.x,tl.y,br.x-tl.x,br.y-tl.y);
    if (outline)
    {
        // outline in black
        fl_color(FL_BLACK);
        fl_rect(tl.x,tl.y,br.x-tl.x,br.y-tl.y);
    }
}

void Rectangle::move_shape(int dx, int dy)
{
    Point tl = get_tl();
    Point br = get_br();
    resize_widget(Point{tl.x+dx,tl.y+dy},Point{br.x+dx,br.y+dy});
}

//
// Text
//

void Text::set_text(const string& s)
{
    if ((bl.x == 0) && (bl.y == 0))
        throw runtime_error("Text::set_text(): bottom left point not set yet!");
    t = s;
    resize_text();
}

void Text::set_bl(Point p)
{
    bl = p;
    resize_text();
}

void Text::draw_shape()
{
    set_fl_font();
    fl_draw(t.c_str(),bl.x,bl.y);
    // now resize with current font style and font size
    resize_text();
    restore_fl_font();
}

void Text::move_shape(int dx,int dy)
{
    bl.x += dx; bl.y += dy;
    resize_text();
}

void Text::resize_text()
{
    int x{0},y{0},w{0},h{0};
    fl_text_extents(t.c_str(),x,y,w,h);
    resize_widget(Point{bl.x+x,bl.y+y},Point{bl.x+x+w,bl.y+y+h});
}

//
// Circle
//

void Circle::set_center(Point p)
{
    c = p;
    resize_widget(Point{c.x-r,c.y-r},Point{c.x+r,c.y+r});
}

void Circle::set_radius(int rr)
{
    r = rr;
    resize_widget(Point{c.x-r,c.y-r},Point{c.x+r,c.y+r});
}

void Circle::draw_shape()
{
    Point tl = get_tl();
    Point br = get_br();
    fl_arc(tl.x,tl.y,br.x-tl.x,br.y-tl.y,0,360);
}

void Circle::move_shape(int dx,int dy)
{
    c.x += dx; c.y += dy;
    resize_widget(Point{c.x-r,c.y-r},Point{c.x+r,c.y+r});
}

//
// Ellipse
//

void Ellipse::set_center(Point p)
{
    c = p;
    resize_widget(Point{c.x-a,c.y-b},Point{c.x+a,c.y+b});
}

void Ellipse::set_major(int aa)
{
    a = aa;
    resize_widget(Point{c.x-a,c.y-b},Point{c.x+a,c.y+b});
}

void Ellipse::set_minor(int bb)
{
    b = bb;
    resize_widget(Point{c.x-a,c.y-b},Point{c.x+a,c.y+b});
}

void Ellipse::draw_shape()
{
    Point tl = get_tl();
    Point br = get_br();
    fl_arc(tl.x,tl.y,br.x-tl.x,br.y-tl.y,0,360);
}

void Ellipse::move_shape(int dx,int dy)
{
    c.x += dx; c.y += dy;
    resize_widget(Point{c.x-a,c.y-b},Point{c.x+a,c.y+b});
}

//
// Marked polyline
//

void Marked_polyline::resize_widget()
{
    Open_polyline::resize_widget();
    
    // nothing to do if empty points or markers
    if (empty_points() || empty_marks())
        return;
    
    // adjust the top-left and bottom-right
    // corners of the widget by taking
    // into account the size of the text markers
    int x{0},y{0},w{0},h{0};
    if (get_nb_points() == get_nb_marks())
        // different markers for every point
        for (size_t i=0; i < get_nb_points(); i++)
        {
            // update dx,dy,w,h for every marker text
            fl_text_extents(m[i].c_str(),x,y,w,h);
            
            // top left corner of enclosing rectangle of the marker text
            update_tl_br(Point{get_point(i).x+x,get_point(i).y+y});
            // bottom right corner of enclosing rectangle of the marker text
            update_tl_br(Point{get_point(i).x+x+w,get_point(i).y+y+h});
        }
    else
    {
        // same marker for all points
        fl_text_extents(m[0].c_str(),x,y,w,h);
        for (size_t i=0; i < get_nb_points(); i++)
        {
            // top left corner of enclosing rectangle of the marker text
            update_tl_br(Point{get_point(i).x+x,get_point(i).y+y});
            // bottom right corner of enclosing rectangle of the marker text
            update_tl_br(Point{get_point(i).x+x+w,get_point(i).y+y+h});
        }
    }
    Widget::resize_widget();
}

void Marked_polyline::set_mark(size_t i, string mrk)
{
    m.at(i) = mrk;
    resize_widget();
}

void Marked_polyline::remove_mark(size_t i)
{
    m.erase(m.begin()+i);
    resize_widget();
}

void Marked_polyline::draw_text()
{
    if (get_nb_points() == get_nb_marks())
        // different markers for every point
        for (size_t i=0; i < get_nb_points(); i++)
            fl_draw(m[i].c_str(),get_point(i).x,get_point(i).y);
    else if (get_nb_marks() == 1)
        // same marker for all points
        for (size_t i=0; i < get_nb_points(); i++)
            fl_draw(m[0].c_str(),get_point(i).x,get_point(i).y);
    else throw runtime_error("Marked_polyline::draw_text(): Unequal number of points and markers!");
}

void Marked_polyline::draw_shape()
{
    set_fl_font();
    draw_text();
    resize_widget(); // final resize for correct sizes
    restore_fl_font();
    Open_polyline::draw_shape();
}

//
// Marks
//

void Marks::draw_shape()
{
    set_fl_font();
    draw_text();
    resize_widget(); // final resize for correct sizes
    restore_fl_font();
}

//
// Image
//

Image::Image(Point pos, string name) : fn{name}
{
    fl_register_images();
    img = Fl_Shared_Image::get(fn.c_str());
    switch ( img->fail() ) {
        case Fl_Image::ERR_NO_IMAGE:
            throw runtime_error("Image::Image(): File " + fn + " not found!");
        case Fl_Image::ERR_FILE_ACCESS:
            throw runtime_error("Image::Image(): File " + fn + " access error!");
        case Fl_Image::ERR_FORMAT:
            throw runtime_error("Image::Image(): File " + fn + " format error!");
    }
    resize_widget(pos,Point{pos.x+img->w(),pos.y+img->h()});
}

void Image::set_mask(Point o, int w, int h)
{
    orig = o;
    resize_widget(get_tl(),Point{get_tl().x+w,get_tl().y+h});
}

void Image::draw_shape()
{
    if (cpy) cpy->draw(get_tl().x,get_tl().y);
    else img->draw(get_tl().x,get_tl().y,get_w(),get_h(),orig.x,orig.y);
}

void Image::move_shape(int dx,int dy)
{
    resize_widget(Point{get_tl().x+dx,get_tl().y+dy},
                 Point{get_tl().x+dx+get_w(),
                 get_tl().y+dy+get_h()});
}

//
// Function
//

Function::Function (Function_type f,pair<double,double> rx, double d, pair<double,double> ry,Point p, int lx, double ar) : func{f},x_range{rx},x_step{d},y_range{ry},orig{p},len_x{lx},ratio{ar}
{
    // y-axis length
    len_y = int(round(len_x*ratio));
    // calculate function values
    calculate_y();
    // calculate points,
    // sets top-left and bottom-right points
    calculate_points();
    // resize
    resize_widget();
}

Function::~Function()
{
    for (auto p : vp) delete p;
    for (auto l : labels) delete l;
}

void Function::add_label(double x,string txt,int dx,int dy)
{
    // add text to the labels array
    Text *label = new Text();
    label->set_bl( Point{orig.x+int(round(x*sx))+dx, orig.y-int(round(func(x)*sy))+dy} );
    label->set_text(txt);
    labels.push_back(label);
    // update widget size
    update_tl_br(Point{label->get_tl()});
    update_tl_br(Point{label->get_br()});
    resize_widget();
}

// calculates the function values
void Function::calculate_y()
{
    x_min = x_range.first;
    x_max = x_range.second;
    double xx = x_min;
    x.push_back(xx);
    y.push_back(func(xx));
    while (xx < x_max) {
        xx += x_step;
        x.push_back(xx);
        y.push_back(func(xx));
    }
    y_min = y_range.first;
    y_max = y_range.second;
}

// calculate points
void Function::calculate_points()
{
    // scale factors for the x- and y-axis
    sx = len_x / (x_max-x_min);
    sy = len_y / (y_max-y_min);
    for (size_t n=0; n<x.size(); n++) {
        int xx = orig.x + int(round(x[n]*sx));
        int yy = orig.y - int(round(y[n]*sy));
        vp.push_back(new Point{xx,yy});
    }
    // set top-left and bottom-right points
    set_tl(Point{orig.x+int(round(x_min*sx)),orig.y-int(round(y_max*sy))});
    set_br(Point{orig.x+int(round(x_max*sx)),orig.y-int(round(y_min*sy))});
}

void Function::draw_shape()
{
    for (size_t n=0; n<x.size()-1; n++) {
        // only draw if the function is in the desired range
        if ( ((y[n]<y_max) && (y[n]>y_min)) &&
             ((y[n+1]<y_max) && (y[n+1]>y_min)) )
            fl_line(vp[n]->x,vp[n]->y,vp[n+1]->x,vp[n+1]->y);
    }
    for (auto label:labels) label->draw();
}

void Function::move_shape(int dx,int dy)
{
    for (auto p : vp) {
        p->x += dx;
        p->y += dy;
    }
    for (auto label:labels) label->move(dx,dy);
    resize_widget(Point{get_tl().x+dx,get_tl().y+dy},
                 Point{get_br().x+dx,get_br().y+dy});
}

//
// XAxis
//

XAxis::XAxis(pair<double,double> rx,double d,Point p,int lx,int ln) :
x_range{rx}, x_step{d},orig{p},len_x{lx},len_n{ln}
{
    // determine notches positions
    calculate_x();
    // calculate notches lines,
    // set top-left and bottom-right points
    calculate_notches();
    // resize
    resize_widget();
    // main axis
    axis.set_line({ Point{get_tl().x,orig.y},Point{get_br().x,orig.y} });
}

void XAxis::add_label(double x,string txt,int dx,int dy)
{
    // add text to the labels array
    Text *label = new Text();
    label->set_bl( Point{orig.x+int(round(x*sx))+dx,orig.y+dy} );
    label->set_text(txt);
    labels.push_back(label);
    // update widget size
    update_tl_br(Point{label->get_tl()});
    update_tl_br(Point{label->get_br()});
    resize_widget();
}

void XAxis::calculate_x()
{
    x_min = x_range.first;
    x_max = x_range.second;
    // sanity check on x-range
    if (x_max<x_min) throw runtime_error("XAxis::calculate_x(): xmax cannot be less than xmin!");
    double xx = x_min;
    x.push_back(xx);
    while (xx < x_max) {
        xx += x_step;
        x.push_back(xx);
    }
}

void XAxis::calculate_notches()
{
    // scale factor for the x-axis
    sx = len_x / (x_max-x_min);
    // if 0 is not in the range recalculate the origin
    if ( (x_min>0) || (x_max<0) )
        orig.x = orig.x - int(round(x_min*sx));
    for (size_t n=0; n<x.size(); n++) {
        int xx = orig.x + int(round(x[n]*sx));
        notches.add_line({Point{xx,orig.y+len_n},
                          Point{xx,orig.y-len_n}});
    }
    // set top-left and bottom-right points
    set_tl(Point{orig.x+int(round(x_min*sx)),orig.y-len_n});
    set_br(Point{orig.x+int(round(x_max*sx)),orig.y+len_n});
}

void XAxis::draw_shape()
{
    axis.draw();
    notches.draw();
    for (auto label:labels) label->draw();
}

void XAxis::move_shape(int dx,int dy)
{
    axis.move(dx,dy);
    notches.move(dx,dy);
    for (auto label:labels) label->move(dx,dy);
    resize_widget(Point{get_tl().x+dx,get_tl().y+dy},
                 Point{get_br().x+dx,get_br().y+dy});
}

void XAxis::set_color_shape(Color_type c)
{
    axis.set_color(c);
    notches.set_color(c);
    for (auto label:labels) label->set_color(c);
}

//
// YAxis
//

YAxis::YAxis(pair<double,double> ry,double d,Point p,int ly,int ln) :
y_range{ry}, y_step{d},orig{p},len_y{ly},len_n{ln}
{
    // determine notches positions
    calculate_y();
    // calculate notches lines,
    // set top-left and bottom-right points
    calculate_notches();
    // resize
    resize_widget();
    // main axis
    axis.set_line({ Point{orig.x,get_tl().y},Point{orig.x,get_br().y} });
}

void YAxis::add_label(double y,string txt,int dx,int dy)
{
    // add text to the labels array
    Text *label = new Text();
    label->set_bl( Point{orig.x+dx,orig.y-int(round(y*sy))+dy} );
    label->set_text(txt);
    labels.push_back(label);
    // update widget size
    update_tl_br(Point{label->get_tl()});
    update_tl_br(Point{label->get_br()});
    resize_widget();
}

void YAxis::calculate_y()
{
    y_min = y_range.first;
    y_max = y_range.second;
    // sanity check on x-range
    if (y_max<y_min) throw runtime_error("YAxis::calculate_y(): ymax cannot be less than ymin!");
    double yy = y_min;
    y.push_back(yy);
    while (yy < y_max) {
        yy += y_step;
        y.push_back(yy);
    }
}

void YAxis::calculate_notches()
{
    // scale factor for the y-axis
    sy = len_y / (y_max-y_min);
    // if 0 is not in the range recalculate the origin
    if ( (y_min>0) || (y_max<0) )
        orig.y = orig.y + int(round(y_min*sy));
    for (size_t n=0; n<y.size(); n++) {
        int yy = orig.y - int(round(y[n]*sy));
        notches.add_line({Point{orig.x+len_n,yy},
                          Point{orig.x-len_n,yy}});
    }
    // set top-left and bottom-right points
    set_tl(Point{orig.x-len_n,orig.y-int(round(y_min*sy))});
    set_br(Point{orig.x+len_n,orig.y-int(round(y_max*sy)),});
}

void YAxis::draw_shape()
{
    axis.draw();
    notches.draw();
    for (auto label:labels) label->draw();
}

void YAxis::move_shape(int dx,int dy)
{
    axis.move(dx,dy);
    notches.move(dx,dy);
    for (auto label:labels) label->move(dx,dy);
    resize_widget(Point{get_tl().x+dx,get_tl().y+dy},
                 Point{get_br().x+dx,get_br().y+dy});
}

void YAxis::set_color_shape(Color_type c)
{
    axis.set_color(c);
    notches.set_color(c);
    for (auto label:labels) label->set_color(c);
}

//
// Button
//

Button::Button(Point p,int w,int h,const string s,Callback_type cb,void *d)
{
    text = s;
    data = d;
    b = new Fl_Button(p.x,p.y,w,h,text.c_str());
    if (b)
    {
        b->callback(cb,data);
        b->type(fl_button);
        b->when(fl_when);
        resize_widget(p,w,h);
    }
    else throw runtime_error("Button::Button(): Button allocation failed!");
}

void Button::set_when(When_type w)
{
    hide();
    fl_when = to_fl_when(w);
    show();
}

void Button::set_button(Button_type b)
{
    hide();
    fl_button = to_fl_button(b);
    show();
}

void Button::draw()
{
    b->type(fl_button);
    b->when(fl_when);
    b->label(text.c_str());
    if (is_visible())
        b->show();
    else
        b->hide();
}

void Button::move(int dx, int dy)
{
    hide();
    b->resize(get_tl().x+dx,get_tl().y+dy,get_w(),get_h());
    resize_widget(Point{get_tl().x+dx,get_tl().y+dy},get_w(),get_h());
    show();
}

//
// In_box
//

In_box::In_box(Point p,int w,int h,const string s)
{
    text = s;
    in = new Fl_Input(p.x,p.y,w,h,text.c_str());
    if (in)
    {
        in->callback(static_input_callback, (void *)this);
        in->when( to_fl_when(When_type::changed) );
        resize_widget(p,w,h);
    }
    else throw runtime_error("In_box::In_box(): In_box allocation failed!");
}

void In_box::draw()
{
    in->label(text.c_str());
    if (is_visible()) in->show();
    else in->hide();
}

void In_box::move(int dx, int dy)
{
    hide();
    in->resize(get_tl().x+dx,get_tl().y+dy,get_w(),get_h());
    resize_widget(Point{get_tl().x+dx,get_tl().y+dy},get_w(),get_h());
    show();
}

//
// Out_box
//

Out_box::Out_box(Point p,int w,int h,const string s)
{
    text = s;
    out = new Fl_Output(p.x,p.y,w,h,text.c_str());
    if (out)
    {
        out->value(out_text.c_str());
        resize_widget(p,w,h);
    }
    else throw runtime_error("Out_box::Out_box(): Out_box allocation failed!");
}

void Out_box::draw()
{
    out->label(text.c_str());
    out->value(out_text.c_str());
    if (is_visible()) out->show();
    else out->hide();
}

void Out_box::move(int dx, int dy)
{
    hide();
    out->resize(get_tl().x+dx,get_tl().y+dy,get_w(),get_h());
    resize_widget(Point{get_tl().x+dx,get_tl().y+dy},get_w(),get_h());
    show();
}

//
// Menu
//

void Menu::add_button(Button *b)
{
    selection.push_back(b);
    if (type == Menu_type::horizontal)
    {
        b->Widget::move(Point{get_tl().x+width,get_tl().y});
        width += b->get_w()+gap;
        if (b->get_h() > height)
            height = b->get_h();
    }
    else if (type == Menu_type::vertical)
    {
        b->Widget::move(Point{get_tl().x,get_tl().y+height});
        height += b->get_h()+gap;
        if (b->get_w() > width)
            width = b->get_w();
    }
    resize_widget(get_tl(),width,height);
}

void Menu::attach(Generic_window* w)
{
    Widget::attach(w);
    for (auto b:selection) w->attach(*b);
}

void Menu::move(int dx, int dy)
{
    for (auto b:selection)
        b->move(dx,dy);
    resize_widget(Point{get_tl().x+dx,get_tl().y+dy},width,height);
}

void Menu::destroy()
{
    for (auto b:selection)
        if (b) delete(b);
}

void Menu::draw()
{
    if (is_visible())
        for (auto b:selection) b->set_transparency(Transparency_type::visible);
    else
        for (auto b:selection) b->set_transparency(Transparency_type::invisible);
}

} // namespace mathsophy::graphics

