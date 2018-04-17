#include "world.h"

World::World()
{
  draw_xy_axes();
  // this->_displayFile.push_back(this->_points);
  // this->_displayFile.push_back(this->_lines);
  // this->_displayFile.push_back(this->_polygons);
}

World::~World()
{
}

void World::addLine(std::string name, int x1_cord, int y1_cord, int x2_cord, int y2_cord, Coordinate _borderColor, LineClippingType type)
{
  Coordinate* point_cord1 = new Coordinate(x1_cord, y1_cord);
  Coordinate* point_cord2 = new Coordinate(x2_cord, y2_cord);

  Line* line = new Line(name, point_cord1, point_cord2, _borderColor, type);

  this->_displayFile.addObject(line);
  this->_updateObjectCoordinates(line);
}

void World::addPoint(std::string name, int x_coord, int y_coord, Coordinate _borderColor)
{
  Coordinate* point_cord = new Coordinate(x_coord, y_coord);
  Point* point = new Point(name, point_cord, _borderColor);

  this->_displayFile.addObject(point);
  this->_updateObjectCoordinates(point);
}

void World::addPolygon(std::string name, std::vector<big_double> polygon_coord_list, Coordinate _borderColor, Coordinate  _fillingColor)
{
  int unsigned coordinates_size = polygon_coord_list.size();
  std::list<Coordinate*> coordinates;

  for( unsigned int index = 2; index < coordinates_size; index++, index++, index++ )
  {
    LOG(1, "Currently we do not support 3D, forcing z `%s` to be 1", polygon_coord_list.at(index-2));
    coordinates.push_back( new Coordinate( polygon_coord_list.at(index-2), polygon_coord_list.at(index-1), 1 ) );
  }

  Polygon* polygon = new Polygon(name, coordinates, _borderColor, _fillingColor);

  this->_displayFile.addObject(polygon);
  this->_updateObjectCoordinates(polygon);
}

void World::addCurveBezier(std::string name, std::vector<std::pair<Coordinate, Coordinate>> curve_vector_list, Coordinate _borderColor)
{
  std::list<Coordinate*> cord_list;

  /// LIDA COM CURVA FORMADA POR MAIS DE UMA CURVA!!!!
  for(int v = 0; v< curve_vector_list.size()-1 ; v++){
	  std::list<Coordinate*> more_cord_list = blendCurveBezier(curve_vector_list[v],curve_vector_list[v+1]);
	  cord_list.merge(more_cord_list);
  }

  beziercurve* curve = new beziercurve(name, cord_list, _borderColor);

  this->_displayFile.addObject(curve);
  this->_updateObjectCoordinates(curve);
}

void World::addCurveBSpline(std::string name, std::vector<Coordinate> bspline_point_list, Coordinate _borderColor)
{
  std::list<Coordinate*> cord_list;

  for(int v = 0; v< bspline_point_list.size() - 3 ; v++){
	  
    this->setBSplineParameters(bspline_point_list[v], bspline_point_list[v+1], bspline_point_list[v+2],bspline_point_list[v+3]);

    std::list<Coordinate*> more_cord_list = fwdDiff(1/DELTA_BSPLINE, this->f0);

    if(v==0)cord_list.push_back(new Coordinate(this->f0));


    std::list<Coordinate*>::iterator it;
    it = cord_list.end();

    cord_list.insert(it, more_cord_list.begin(), more_cord_list.end());
    more_cord_list.clear();

  }
  

  Bspline* bspline = new Bspline(name, cord_list, _borderColor);

  this->_displayFile.addObject(bspline);
  this->_updateObjectCoordinates(bspline);
}


std::list<Coordinate*> World::blendCurveBezier(std::pair<Coordinate, Coordinate> vector1, std::pair<Coordinate, Coordinate> vector2)
{
  std::list<Coordinate*> cord_list;

  	Coordinate p1 = vector1.first;

  	Coordinate p2 = vector1.second;

  	Coordinate p3 = vector2.first;

  	Coordinate p4 = vector2.second;

  	Coordinate t_coord;

  for(big_double t = 0; t <= 1; t += DELTA)
  {
	  t_coord = Coordinate(t, t, 1);

	  Coordinate p11 = p1 + ((p2 - p1) * t_coord);
	  Coordinate p21 = p2 + ((p3 - p2) * t_coord);
	  Coordinate p31 = p3 + ((p4 - p3) * t_coord);

	  Coordinate p22 = p11 + ((p21 - p11) * t_coord);
	  Coordinate p32 = p21 + ((p31 - p21) * t_coord);

	  Coordinate p33 = p22 + ((p32 - p22) * t_coord);

    cord_list.push_back( new Coordinate(p33));
  }
  return cord_list;
}


void World::removeObject(std::string name)
{
  // LOG(4, "Removing an object by name is faster than by pointer because it internally calls `removeObjectByName()`");
  this->_displayFile.removeObjectByName(name);
  this->_updateObjectCoordinates(nullptr);
}

World::UpdateObjectCoordinates::Connection World::addObserver(const World::UpdateObjectCoordinates::Callback& callback)
{
  return this->_updateObjectCoordinates.connect(callback);
}

void World::updateAllObjectCoordinates(const Transformation& transformation, const Axes& axes)
{
  LOG(4, "Updating all objects clipping...");
  auto objects = this->_displayFile.getObjects();

  for (auto object : objects)
  {
    object->updateWindowCoordinates(transformation);
    object->updateClippingCoordinates(axes);
  }
}

void World::updateObjectCoordinates(DrawableObject* object, const Transformation& transformation, const Axes& axes)
{
  if( object == nullptr )
  {
    LOG(1, "");
    LOG(1, "");
    LOG(1, "ERROR: Null pointer object passed by: %s", object);
    return;
  }

  if( object->worldCoordinates().size() == 0 )
  {
    LOG(1, "");
    LOG(1, "");
    LOG(1, "ERROR: The object `%s` has no coordinates.", *object);
  }
  else
  {
    LOG(4, "Updating the object `%s`", *object);
  }

  object->updateWindowCoordinates(transformation);
  object->updateClippingCoordinates(axes);
}

void World::apply(const std::string object_name, Transformation &transformation)
{
  if( this->_displayFile.isObjectOnByName(object_name) )
  {
    if( transformation.size() )
    {
      DrawableObject* object = this->_displayFile.apply(object_name, transformation);
      this->_updateObjectCoordinates(object);
    }
    else
    {
      LOG(4, "There are no transformations available to be applied on your object: `%s` %s", object_name, transformation);
    }
  }
  else
  {
    LOG(4, "No object was found within the name: `%s`", object_name);
  }
}

void World::draw_xy_axes()
{
  LOG(4, "Drawing the X T axes as world objects.");
  this->addLine("Y Axe", 0, -WORLD_AXES_SIZE, 0, WORLD_AXES_SIZE, Coordinate(0.741176, 0.717647, 0.419608));
  this->addLine("X Axe", -WORLD_AXES_SIZE, 0, WORLD_AXES_SIZE, 0, Coordinate(0.741176, 0.717647, 0.419608));
}

void World::setBSplineParameters(Coordinate p1, Coordinate p2, Coordinate p3, Coordinate p4){

  this->a = p1*M_BS[0][0] + p2*M_BS[0][1] + p3*M_BS[0][2] + p4*M_BS[0][3];
  this->b = p1*M_BS[1][0] + p2*M_BS[1][1] + p3*M_BS[1][2] + p4*M_BS[1][3];
  this->c = p1*M_BS[2][0] + p2*M_BS[2][1] + p3*M_BS[2][2] + p4*M_BS[2][3];
  this->d = p1*M_BS[3][0] + p2*M_BS[3][1] + p3*M_BS[3][2] + p4*M_BS[3][3];

  this->f0 = this->d;
  this->delta_f0 = (a*(pow(DELTA_BSPLINE,3))) + (b*(pow(DELTA_BSPLINE,2))) + (c*DELTA_BSPLINE);
  this->delta_2f0 = (a*6*pow(DELTA_BSPLINE,3)) + (b*2*pow(DELTA_BSPLINE,2)); 
  this->delta_3f0 = a*6*pow(DELTA_BSPLINE,3);

  LOG(4, "F0 -----------: `%s`", this->f0);
  LOG(4, "delta_f0 -----------: `%s`", this->delta_f0);
  LOG(4, "delta_2f0 -----------: `%s`", this->delta_2f0);
  LOG(4, "delta_3f0 -----------: `%s`", this->delta_3f0);
  

}

std::list<Coordinate*> World::fwdDiff(int n, Coordinate point)
{
  
  std::list<Coordinate*> cord_list;
  cord_list.clear();

    double x = point[0];
    double y = point[1];
    double z = point[2];

    double delta_x = this->delta_f0[0];
    double delta_2x = this->delta_2f0[0];
    double delta_3x = this->delta_3f0[0];

    double delta_y = this->delta_f0[1];
    double delta_2y = this->delta_2f0[1];
    double delta_3y = this->delta_3f0[1];

    double delta_z = this->delta_f0[2];
    double delta_2z = this->delta_2f0[2];
    double delta_3z = this->delta_3f0[2];


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

        Coordinate intermediate(x,y,z);
        cord_list.push_back(new Coordinate(intermediate));

        x_old = x;
        y_old = y;
        z_old = z;
    }

    return cord_list;

}