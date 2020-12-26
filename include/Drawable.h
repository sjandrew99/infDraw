#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <string>

class Drawable
{
 public:
  virtual void draw() = 0;
  std::string id;
   
};

class TextBox : public Drawable
{
 public:
  void draw();
  std::string text; 
};

class Connector : public Drawable
{
 public:
  TextBox label;
};

class Shape : public Drawable
{
 public:
  TextBox label;
};

#endif
