#include "polygon.h"

Polygon::Polygon(std::string name, std::list<Coordinate*> _worldCoordinates, Coordinate _borderColor, Coordinate _fillingColor) :
      DrawableObject(name, _worldCoordinates, _borderColor, _fillingColor)
{
}

Polygon::~Polygon()
{
}

void Polygon::updateClippingCoordinates(const Axes& axes)
{
  LOG(4, "Polygon clipping update... %s", axes);
  this->_isDrawable = this->_sutherlandHodgmanPolygonClip(axes);
}

bool Polygon::_sutherlandHodgmanPolygonClip(const Axes& axes)
{
  std::vector<Coordinate> input;

  for( auto coordinate : this->_windowCoordinates ) {
    input.push_back(Coordinate(*coordinate));
  }

  std::vector<Coordinate> temporary;
  std::vector<Coordinate> clippingResult;

  this->_sutherlandHodgmanClipLeft(axes, input, temporary);
  this->_sutherlandHodgmanClipRight(axes, temporary, clippingResult);
  this->_sutherlandHodgmanClipTop(axes, clippingResult, temporary);
  this->_sutherlandHodgmanClipBottom(axes, temporary, clippingResult);

  if( clippingResult.size() == 0 ) {
    return false;
  }

  this->destroyList(this->_clippingCoordinates);

  for( auto coordinate : clippingResult ) {
    this->_clippingCoordinates.push_back(new Coordinate(coordinate));
  }
  return true;
}

void Polygon::_sutherlandHodgmanClipLeft(const Axes& axes, std::vector<Coordinate>& input, std::vector<Coordinate>& clippingResult)
{
  if( clippingResult.size() > 0 ) {
    clippingResult.clear();
  }

  if( input.size() == 0 ) {
    return;
  }

  big_double clipX = axes.xWiMin;
  input.push_back(input[0]);

  for( unsigned int i = 0; i < input.size() - 1; i++ )
  {
    Coordinate c0 = input[i];
    Coordinate c1 = input[i+1];

    // Case 1: out -> out
    if( c0.x < clipX && c1.x < clipX ) {
    }

    // Case 2: in -> in
    if( c0.x >= clipX && c1.x >= clipX )
    {
      clippingResult.push_back(c1);
    }

    big_double x = clipX;
    big_double m = (c1.y-c0.y) / (c1.x-c0.x);
    big_double y = m * (x-c0.x) + c0.y;

    // Case 3: in -> out
    if( c0.x >= clipX && c1.x < clipX )
    {
      clippingResult.emplace_back(x,y);
    }

    // Case 4: out -> in
    if( c0.x < clipX && c1.x >= clipX )
    {
      clippingResult.emplace_back(x,y);
      clippingResult.push_back(c1);
    }
  }
}

void Polygon::_sutherlandHodgmanClipRight(const Axes& axes, std::vector<Coordinate>& input, std::vector<Coordinate>& clippingResult)
{
  if( clippingResult.size() > 0 ) {
    clippingResult.clear();
  }

  if( input.size() == 0 ) {
    return;
  }

  big_double clipX = axes.xWiMax;
  input.push_back(input[0]);

  for( unsigned int i = 0; i < input.size()-1; i++ )
  {
    Coordinate c0 = input[i];
    Coordinate c1 = input[i+1];

    // Case 1: out -> out
    if( c0.x >= clipX && c1.x >= clipX ) {
    }

    // Case 2: in -> in
    if( c0.x < clipX && c1.x < clipX )
    {
      clippingResult.push_back(c1);
    }

    big_double x = clipX;
    big_double m = (c1.y-c0.y) / (c1.x-c0.x);
    big_double y = m * (x-c0.x) + c0.y;

    // Case 3: in -> out
    if( c0.x < clipX && c1.x >= clipX )
    {
      clippingResult.emplace_back(x,y);
    }

    // Case 4: out -> in
    if( c0.x >= clipX && c1.x < clipX )
    {
      clippingResult.emplace_back(x,y);
      clippingResult.push_back(c1);
    }
  }
}

void Polygon::_sutherlandHodgmanClipTop(const Axes& axes, std::vector<Coordinate>& input, std::vector<Coordinate>& clippingResult)
{
  if( clippingResult.size() > 0 ) {
    clippingResult.clear();
  }

  if( input.size() == 0 ) {
    return;
  }

  big_double clipY = axes.yWiMax;
  input.push_back(input[0]);

  for( unsigned int i = 0; i < input.size()-1; i++ )
  {
    Coordinate c0 = input[i];
    Coordinate c1 = input[i+1];

    // Case 1: out -> out
    if( c0.y > clipY && c1.y > clipY ) {
    }

    // Case 2: in -> in
    if( c0.y <= clipY && c1.y <= clipY )
    {
      clippingResult.push_back(c1);
    }

    big_double y = clipY;
    big_double m = (c1.x-c0.x) / (c1.y-c0.y);
    big_double x = m * (y-c0.y) + c0.x;

    // Case 3: in -> out
    if( c0.y <= clipY && c1.y > clipY )
    {
      clippingResult.emplace_back(x,y);
    }

    // Case 4: out -> in
    if( c0.y > clipY && c1.y <= clipY )
    {
      clippingResult.emplace_back(x,y);
      clippingResult.push_back(c1);
    }
  }
}

void Polygon::_sutherlandHodgmanClipBottom(const Axes& axes, std::vector<Coordinate>& input, std::vector<Coordinate>& clippingResult)
{
  if( clippingResult.size() > 0 ) {
    clippingResult.clear();
  }

  if( input.size() == 0 ) {
    return;
  }

  big_double clipY = axes.yWiMin;
  input.push_back(input[0]);

  for( unsigned int i = 0; i < input.size()-1; i++ )
  {
    Coordinate c0 = input[i];
    Coordinate c1 = input[i+1];

    // Case 1: out -> out
    if( c0.y < clipY && c1.y < clipY ) {
    }

    // Case 2: in -> in
    if( c0.y >= clipY && c1.y >= clipY ) {
      clippingResult.push_back(c1);
    }

    big_double y = clipY;
    big_double m = (c1.x-c0.x) / (c1.y-c0.y);
    big_double x = m * (y-c0.y) + c0.x;

    // Case 3: in -> out
    if( c0.y >= clipY && c1.y < clipY )
    {
      clippingResult.emplace_back(x,y);
    }

    // Case 4: out -> in
    if( c0.y < clipY && c1.y >= clipY )
    {
      clippingResult.emplace_back(x,y);
      clippingResult.push_back(c1);
    }
  }
}

void Polygon::draw(const Cairo::RefPtr<Cairo::Context>& cairo_context, const ViewWindow *viewwindow) const{


   LOG(4, "Draw Polygon");
   if( !this->_isDrawable )
    {
      LOG(8, "Skip objects which were completely clipped out of the Window");
    }else{

    // auto coordinates = object->windowCoordinates();
    auto coordinates = this->clippingCoordinates();
    int coordinates_count = coordinates.size();

    if (coordinates_count == 0)
    {
      LOG(1, "ERROR: The object `%s` has no coordinates.", *this);
    }

    auto border = this->borderColor();
    auto filling = this->fillingColor();

    LOG(8, "Set object border and filing colors: %s %s", border, filling);
    cairo_context->set_source_rgb(border.x, border.y, border.z);

    LOG(8, "object coordinates: %s", *this);
    auto firstCoordinate = viewwindow->convertCoordinateToViewPort(**(coordinates.begin()));
    cairo_context->move_to(firstCoordinate.x, firstCoordinate.y);

    if( coordinates_count == 1 )
    {
      cairo_context->line_to(firstCoordinate.x+1, firstCoordinate.y+1);
    }
    else
    {
      for( auto coordinate : coordinates )
      {
        Coordinate coordinateConverted = viewwindow->convertCoordinateToViewPort(*coordinate);
        cairo_context->line_to(coordinateConverted.x, coordinateConverted.y);
      }

      // https://developer.gnome.org/gtkmm-tutorial/stable/sec-cairo-drawing-arcs.html.en
      // LOG(8, "Line back to start point, closing the polygon")
      cairo_context->save();
      cairo_context->close_path();
      cairo_context->set_source_rgb(filling.x, filling.y, filling.z);
      cairo_context->fill_preserve();
      cairo_context->restore();  // back to opaque black
    }

    cairo_context->stroke(); // outline it
   
    }


 }
