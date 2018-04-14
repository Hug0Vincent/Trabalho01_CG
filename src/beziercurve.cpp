/*
 * beziercurve.cpp
 *
 *  Created on: 6 de abr de 2018
 *      Author: karla
 */

#include "beziercurve.h"


beziercurve::beziercurve(std::string name, std::list<Coordinate*> _worldCoordinates,
						Coordinate _borderColor) :
	DrawableObject(name, _worldCoordinates, _borderColor)
{
}


beziercurve::~beziercurve() {
	// TODO Auto-generated destructor stub
}

void beziercurve::updateClippingCoordinates(const Axes& axes)
{
  LOG(4, "Curve clipping update... %s", axes);
  this->_isDrawable = this->_liangBaskyLineClip(axes);
}


bool beziercurve::_liangBaskyLineClip(const Axes& axes)
{
  this->destroyList(this->_clippingCoordinates);

  for( auto coordinate : this->_windowCoordinates )
  {
    this->_clippingCoordinates.push_back(new Coordinate(*coordinate));
  }
  auto front = this->_clippingCoordinates.begin();

  auto& c1 = **front; ++front;
  auto& c2 = **front;

  if( c1 == c2 )
  {
    // Point clipping?!
  }

  Coordinate delta = c2 - c1;
  big_double p, q, r;
  big_double u1 = 0.0, u2 = 1.0;

  for( int index = 0; index < 4; index++ )
  {
    if     (index == 0){ p = -delta.x; q = c1.x - axes.xWiMin; }
    else if(index == 1){ p =  delta.x; q = axes.xWiMax - c1.x; }
    else if(index == 2){ p = -delta.y; q = c1.y - axes.yWiMin; }
    else if(index == 3){ p =  delta.y; q = axes.yWiMax - c1.y; }

    if( p == 0 && q < 0 ) {
      return false;
    }

    r = q / p;

    if( p < 0)
    {
      if( r > u1 ) {
        u1 = r;
      }
    }
    else if( p > 0 )
    {
      if( r < u2 ) {
        u2 = r;
      }
    }
  }

  if( u1 > u2 ) { return false; }

  if( u2 < 1 ) {
    c2.x = c1.x + u2 * delta.x;
    c2.y = c1.y + u2 * delta.y;
  }

  if( u1 > 0 ) {
    c1.x = c1.x + u1 * delta.x;
    c1.y = c1.y + u1 * delta.y;
  }

  return true;
}
