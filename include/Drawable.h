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
  void toggleSelection();
  virtual void highlight() = 0;
  virtual void toJson(FILE *) = 0;
  std::string id;
  int type;
  
  int lineWidth;
  int lineColor;
  int lineStyle;
  int selected;
  Tab * parent;
  std::vector<d_point_t> clickablePoints; 
};

class DTextBox : public Drawable
{
 public:
  DTextBox(Tab * parent, std::string text,float,float);
  void draw();
  void select();
  void highlight();
  std::string text; 
  float x; float y; //top left
  void toJson(FILE *);
};


/*class DConnector : public Drawable
{
 public:
  DTextBox label;
};*/

#define DRAWABLE_LINE 1
class DLine : public Drawable //: public DConnector
{
 public:
  DLine(Tab * parent, std::string, float,float,float,float);
  void draw();
  void select();
  void unselect();
  void highlight();
  
  d_point_t p1;
  d_point_t p2;
  float slope;
  float intrcpt;
  DTextBox * label;
  void toJson(FILE *);
};

/*class DShape : public Drawable
{
 public:
  DTextBox label;
};*/

#define DRAWABLE_RECTANGLE 2
class DRectangle : public Drawable //public DShape
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
  DTextBox * label;
  void toJson(FILE *);
};

#define DRAWABLE_ARROW_LINE 1
class DArrowLine : public Drawable //: public DConnector
{
 public:
  DArrowLine(Tab * parent, std::string, float,float,float,float);
  void draw();
  void select();
  void unselect();
  void highlight();
  
  d_point_t p1;
  d_point_t p2;
  float slope;
  float intrcpt;
  DTextBox * label;
  void toJson(FILE *);
};

#endif
