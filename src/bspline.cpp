#include "bspline.h"

Bspline::Bspline(std::string name, std::list<Coordinate*> _worldCoordinates,
						Coordinate _borderColor) :
	DrawableObject(name, _worldCoordinates, _borderColor)
{
}

Bspline::~Bspline()
{
}
void Bspline::updateClippingCoordinates(const Axes& axes)
{
  LOG(4, "Curve clipping update... %s", axes);
  this->_isDrawable = this->_liangBaskyLineClip(axes);
}

bool Bspline::_liangBaskyLineClip(const Axes& axes)
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

void Bspline::fwdDiff(int n, 
                double x, double delta_x, double delta_2x, double delta_3x,
                double y, double delta_y, double delta_2y, double delta_3y,
                double z, double delta_z, double delta_2z, double delta_3z )
{
    double x_old, y_old, z_old;
    x_old = x;
    y_old = y;
    z_old = z;

    for(int i = 0; i < n ; i++){

        //op on x 
        x += delta_x;
        delta_x += delta_2x;
        delta_2x += delta_3x;

        //op on y 
        y += delta_y;
        delta_y += delta_2y;
        delta_2y += delta_3y;

        //op on z
        z += delta_z;
        delta_z += delta_2z;
        delta_2z += delta_3z;

        //this->drawLine();

        x_old = x;
        y_old = y;
        z_old = z;
    }

}
