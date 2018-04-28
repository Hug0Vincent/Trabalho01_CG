/*
 * object3D.cpp
 *
 *  Created on: 23 de abr de 2018
 *      Author: karla
 */

#include "object3D.h"

object3D::object3D(std::string name, std::list<Coordinate*> _worldCoordinates, Coordinate _borderColor, Coordinate _fillingColor) :
DrawableObject(name, _worldCoordinates, _borderColor, _fillingColor)
{
}


object3D::~object3D() {
	// TODO Auto-generated destructor stub
}


void object3D::updateClippingCoordinates(const Axes& axes)
{
  this->_isDrawable = this->_sutherlandHodgmanPolygonClip(axes);
}

bool object3D::_sutherlandHodgmanPolygonClip(const Axes& axes)
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

void object3D::_sutherlandHodgmanClipLeft(const Axes& axes, std::vector<Coordinate>& input, std::vector<Coordinate>& clippingResult)
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

void object3D::_sutherlandHodgmanClipRight(const Axes& axes, std::vector<Coordinate>& input, std::vector<Coordinate>& clippingResult)
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

void object3D::_sutherlandHodgmanClipTop(const Axes& axes, std::vector<Coordinate>& input, std::vector<Coordinate>& clippingResult)
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

void object3D::_sutherlandHodgmanClipBottom(const Axes& axes, std::vector<Coordinate>& input, std::vector<Coordinate>& clippingResult)
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


