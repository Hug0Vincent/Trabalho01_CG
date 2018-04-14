/*
 * beziercurve.h
 *
 *  Created on: 6 de abr de 2018
 *      Author: karla
 */

#ifndef BEZIERCURVE_H_
#define BEZIERCURVE_H_

#include "drawableobject.h"
#include "matrixform.h"

#define DELTA 0.008

class beziercurve : public DrawableObject {
public:
	beziercurve(std::string, std::list<Coordinate*>, Coordinate);
	virtual ~beziercurve();
	bool _liangBaskyLineClip(const Axes& axes);
	void updateClippingCoordinates(const Axes& axes);
private:
};
#endif/* BEZIERCURVE_H_ */
