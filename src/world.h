#ifndef GTKMM_APP_WORLD
#define GTKMM_APP_WORLD

#include "debugger.h"

#include "line.h"
#include "point.h"
#include "polygon.h"
#include "beziercurve.h"
#include "bspline.h"
#include "object3D.h"

#include "displayfile.h"
#include "subject_controller.h"

class World
{
public:
  World();
  ~World();

  void addPoint(const std::string name, const int, const int, Coordinate _borderColor);
  void addLine(const std::string name, const int, const int, const int, const int,
      Coordinate _borderColor, LineClippingType type=LineClippingType::LIANG_BARSKY);

  void addPolygon(const std::string name, const std::vector<big_double>, Coordinate _borderColor, Coordinate _fillingColor);

  void addCurveBSpline(const std::string name, const std::vector<Coordinate>, Coordinate _borderColor);
  std::list<Coordinate*> fwdDiff(int n, Coordinate point);

  void addCurveBezier(const std::string name, const std::vector<std::pair<Coordinate, Coordinate>>, Coordinate _borderColor);
  std::list<Coordinate*> blendCurveBezier(std::pair<Coordinate, Coordinate>, std::pair<Coordinate, Coordinate>);

  void addObject3D(const std::string name, const std::list<Coordinate>, Coordinate _borderColor, Coordinate _fillingColor);

  void removeObject(const std::string name);

  const DisplayFile& displayFile() const { return this->_displayFile; }

  void draw_xy_axes();
  void apply(const std::string object_name, Transformation& matrices);

  void updateAllObjectCoordinates(const Transformation&, const Axes&);
  static void updateObjectCoordinates(DrawableObject*, const Transformation&, const Axes&);

  /**
   * Implementations types for the Observer Design Pattern with C++ 11 templates and function
   * pointers, instead of tight coupled inheritance.
   */
  typedef Signal<DrawableObject*> UpdateObjectCoordinates;
  UpdateObjectCoordinates::Connection addObserver(const UpdateObjectCoordinates::Callback&);

protected:
  // /**
  //  * List of references to display files lists.
  //  */
  // std::vector< std::reference_wrapper< DisplayFile > > _displayFile;
  DisplayFile _displayFile;
  UpdateObjectCoordinates _updateObjectCoordinates;

  void setBSplineParameters(Coordinate p1, Coordinate p2, Coordinate p3, Coordinate p4);
  

  // DisplayFile _lines;
  // DisplayFile _points;
  // DisplayFile _polygons;

  private:

    Coordinate f0;
    Coordinate delta_f0;
    Coordinate delta_2f0;
    Coordinate delta_3f0;

    Coordinate a;
    Coordinate b;
    Coordinate c;
    Coordinate d;

     double M_BS[4][4] = {
                        {-1.0/6.0, 1.0/2.0, -1.0/2.0, 1.0/6.0},
                        {1.0/2.0  ,-1.0 , 1.0/2.0, 0.0 },
                        {-1.0/2.0, 0.0, 1.0/2.0, 0.0},
                        {1.0/6.0, 2.0/3.0, 1.0/6.0, 0.0}
                };

};

#endif // GTKMM_APP_WORLD
