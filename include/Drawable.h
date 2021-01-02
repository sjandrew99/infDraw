#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <string>
#include "common.h"
#include "tabbedNotebook.h"
#include "Artist.h"
//class Tab; //forward declare

class Drawable
{
 public:
  virtual void draw() = 0;
  virtual void select() = 0;
  virtual void highlight() = 0;
  std::string id;
  int type;
  
  int lineWidth;
  int lineColor;
  int lineStyle;
  int selected;
  Tab * parent; 
};

class DTextBox : public Drawable
{
 public:
  DTextBox();
  void draw();
  void select();
  void highlight();
  std::string text; 
};


class DConnector : public Drawable
{
 public:
  DTextBox label;
};

#define DRAWABLE_LINE 1
class DLine : public DConnector
{
 public:
  DLine(Tab * parent, std::string, float,float,float,float);
  void draw();
  void select();
  void unselect();
  void highlight();
  
  d_point_t p1;
  d_point_t p2;
};

class DShape : public Drawable
{
 public:
  DTextBox label;
};

#define DRAWABLE_RECTANGLE 2
class DRectangle : public DShape
{
 public:
  DRectangle(Tab * parent, std::string, float,float,float,float);
  void draw();
  void select();
  void unselect();
  void highlight();

  d_point_t tl; //top-left
  d_point_t tr;
  d_point_t bl;
  d_point_t br;
};

#endif
