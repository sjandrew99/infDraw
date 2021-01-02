#include "Drawable.h"
//#include "common.h"
/////////// TEXTBOX //////////////

DTextBox::DTextBox()
{
 
}

void DTextBox::draw()
{

}

void DTextBox::select()
{
 
}

void DTextBox::highlight()
{

}

/////////// LINE //////////////

DLine::DLine(Tab * parent,std::string id, float x1, float y1, float x2, float y2)
{
 this->parent = parent;
 this->id = id;
 type = DRAWABLE_LINE; 
 p1 = {x1,y1};
 p2 = {x2,y2};
 lineWidth = LINE_WIDTH; //TODO - pass this in
 selected = 0;
}

void DLine::draw() 
{

}

void DLine::select()
{
 //TODO - set something in the tab to show that this is the selected drawable
 selected = 1;
 highlight();
}
void DLine::unselect()
{
 selected = 0;
}

void DLine::highlight()
{
 
}

/////////// RECTANGLE //////////////

DRectangle::DRectangle(Tab * parent, std::string id, float x1, float y1, float x2, float y2)
{
 this->parent = parent;
 this->id = id;
 type = DRAWABLE_RECTANGLE; 
 float _x1 = min(x1,x2);
 float _x2 = max(x1,x2);
 float _y1 = min(y1,y2);
 float _y2 = max(y2,y1); 
 tl = {_x1,_y1};
 tr = {_x2,_y1};
 bl = {_x1,_y2};
 br = {_x2,_y2};
 lineWidth = LINE_WIDTH; //TODO - pass this in
 selected = 0;
 //fprintf(stderr,"ADD RECT: %f %f %f %f\n",_x1,_y1,_x2,_y2);
}

void DRectangle::draw()
{

}

void DRectangle::select()
{
 //TODO - set something in the tab to show that this is the selected drawable
 selected=1;
 highlight();
}
void DRectangle::unselect()
{
 selected=0;
}

void DRectangle::highlight()
{
 //fprintf(stderr,"HIGHLIGHT RECT: %f %f %f %f\n",tl.x-2,tl.y-2,br.x+2,);
 Artist::drawRectangle(parent->imgMgr->frame, tl.x-lineWidth,tl.y-lineWidth,br.x+lineWidth,br.y+lineWidth,0,0,255); 
}