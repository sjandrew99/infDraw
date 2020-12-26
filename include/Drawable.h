#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <string>


class Drawable
{
 public:
  virtual void draw() = 0;
  std::string id;
   
};

class DTextBox : public Drawable
{
 public:
  DTextBox();
  void draw();
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
  DRectangle();
  void draw();
};

#endif
