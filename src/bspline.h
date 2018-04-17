#ifndef GTKMM_APP_BSPLINE
#define GTKMM_APP_BSPLINE

#include "drawableobject.h"
#include "coordinate.h"


#define DELTA_BSPLINE 0.1

class Bspline : public DrawableObject
{
public:
    Bspline(std::string, std::list<Coordinate*>, Coordinate);
    ~Bspline();

    void fwdDiff(int n, 
                double x, double delta_x, double delta_2x, double delta_3x,
                double y, double delta_y, double delta_2y, double delta_3y,
                double z, double delta_z, double delta_2z, double delta_3z );

    bool _liangBaskyLineClip(const Axes& axes);
	void updateClippingCoordinates(const Axes& axes);

private:


   

    /*MatrixForm M_BS = {
                        {-1/6, 1/2, -1/2, 1/6},
                        {1/2  ,-1 , 1/2, 0 },
                        {-1/2, 0, 1/2, 0},
                        {1/6, 2/3, 1/6, 0}
                };*/

    

};

#endif // GTKMM_APP_LINE
