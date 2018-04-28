/*
 * object3D.h
 *
 *  Created on: 23 de abr de 2018
 *      Author: karla
 */

#ifndef SRC_OBJECT3D_H_
#define SRC_OBJECT3D_H_

#include "drawableobject.h"
#include "coordinate.h"


class object3D : public DrawableObject {

	public:
	  object3D(std::string name, std::list<Coordinate*> _worldCoordinates, Coordinate _borderColor, Coordinate _fillingColor);
	  ~object3D();
	  virtual void updateClippingCoordinates(const Axes&);

	protected:
	  /**
	   * http://www.pracspedia.com/CG/sutherlandhodgman.html
	   * https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm
	   * https://github.com/nogenem/UFSC_CG-2015-2/blob/master/Projeto_1/Etapa_4/include/Clipping.hpp
	   *
	   * @return true if the line should be drawn, false if the line should be skipped drawing
	   */
	  bool _sutherlandHodgmanPolygonClip(const Axes&);
	  void _sutherlandHodgmanClipLeft(const Axes& axes, std::vector<Coordinate>& input, std::vector<Coordinate>& temporary);
	  void _sutherlandHodgmanClipRight(const Axes& axes, std::vector<Coordinate>& temporary, std::vector<Coordinate>& clippingResult);
	  void _sutherlandHodgmanClipTop(const Axes& axes, std::vector<Coordinate>& clippingResult, std::vector<Coordinate>& temporary);
	  void _sutherlandHodgmanClipBottom(const Axes& axes, std::vector<Coordinate>& temporary, std::vector<Coordinate>& clippingResult);
};

#endif /* SRC_OBJECT3D_H_ */
