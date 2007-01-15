/*
    Enki - a fast 2D robot simulator
    Copyright (C) 1999-2006 Stephane Magnenat <stephane at magnenat dot net>
    Copyright (C) 2004-2005 Markus Waibel <markus dot waibel at epfl dot ch>
    Copyright (c) 2004-2005 Antoine Beyeler <abeyeler at ab-ware dot com>
    Copyright (C) 2005-2006 Laboratory of Intelligent Systems, EPFL, Lausanne
    Copyright (C) 2006 Laboratory of Robotics Systems, EPFL, Lausanne
    See AUTHORS for details

    This program is free software; the authors of any publication 
    arising from research using this software are asked to add the 
    following reference:
    Enki - a fast 2D robot simulator
    http://lis.epfl.ch/enki
    Stephane Magnenat <stephane at magnenat dot net>,
    Markus Waibel <markus dot waibel at epfl dot ch>
    Laboratory of Intelligent Systems, EPFL, Lausanne.

    You can redistribute this program and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __ENKI_GEOMETRY_H
#define __ENKI_GEOMETRY_H

#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <vector>

/*!	\file Geometry.h
	\brief The mathematic classes for 2D geometry
*/

namespace Enki
{
	//! A vector in a 2D space
	/*! \ingroup an 
		Notation of values and constructor order arguments are column based:
		\code
		x
		y
		\endcode
	*/
	struct Vector
	{
		//! x component
		double x;
		//! y component
		double y;
	
		//! Constructor, create vector with coordinates (0, 0)
		Vector() { x = y = 0; }
		//! Constructor, create vector with coordinates (v, v)
		Vector(double v) { this->x = v; this->y = v; }
		//! Constructor, create vector with coordinates (x, y)
		Vector(double x, double y) { this->x = x; this->y = y; }
		//! Constructor, create vector with coordinates (array[0], array[1])
		Vector(double array[2]) { x = array[0]; y = array[1]; }
	
		//! Add vector v component by component
		void operator +=(const Vector &v) { x += v.x; y += v.y; }
		//! Substract vector v component by component
		void operator -=(const Vector &v) { x -= v.x; y -= v.y; }
		//! Multiply each component by scalar f
		void operator *=(double f) { x *= f; y *= f; }
		//! Divive each component by scalar f
		void operator /=(double f) { x /= f; y /= f; }
		//! Add vector v component by component and return the resulting vector
		Vector operator +(const Vector &v) const { Vector n; n.x = x + v.x; n.y = y + v.y; return n; }
		//! Substract vector v component by component and return the resulting vector
		Vector operator -(const Vector &v) const { Vector n; n.x = x - v.x; n.y = y - v.y; return n; }
		//! Multiply each component by scalar f and return the resulting vector
		Vector operator /(double f) const { Vector n; n.x = x/f; n.y = y/f; return n; }
		//! Divive each component by scalar f and return the resulting vector
		Vector operator *(double f) const { Vector n; n.x = x*f; n.y = y*f; return n; }
	
		//! Return the scalar product with vector v
		double operator *(const Vector &v) const { return x*v.x + y*v.y; }
		//! Return the norm of this vector
		double norm(void) const { return sqrt(x*x + y*y); }
		//! Return the square norm of this vector (and thus avoid a square root)
		double norm2(void) const { return x*x+y*y; }
		//! Return the cross product with vector v
		double cross(const Vector &v) const { return x * v.y - y * v.x; }
		//! Return a unitary vector of same direction
		Vector unitary(void) const { Vector n; if (norm()) { n = *this; n /= norm(); } return n; }
		//! Return the angle with the horizontal (arc tangant (y/x))
		double angle(void) const { return atan2(y, x); }
	};
	
	//! A point in a 2D space, another name for a vector
	/*! \ingroup an */
	typedef Vector Point;
	
	//! A 2x2 matrix
	/*! \ingroup an 
		Notation of values and constructor order arguments are column based:
		\code
		a c
		b d
		\endcode
	*/
	struct Matrix22
	{
		//! 11 components
		double a;
		//! 21 components
		double b;
		//! 12 components
		double c;
		//! 22 components
		double d;
	
		//! Constructor, create matrix with 0
		Matrix22() { a = b = c = d = 0; }
		//! Constructor, create matrix with a b c d
		Matrix22(double a, double b, double c, double d) { this->a = a; this->b = b; this->c = c; this->d = d; }
		//! Constructor, create rotation matrix of angle alpha in radian
		Matrix22(double alpha) { a = cos(alpha); b = sin(alpha); c = -b; d = a; }
		//! Constructor, create matrix with array[0] array[1] array[2] array[3]
		Matrix22(double array[4]) { a=array[0]; b=array[1]; c=array[2]; d=array[3]; }
	
		//! Add matrix v component by component
		void operator +=(const Matrix22 &v) { a += v.a; b += v.b; c += v.c; d += v.d; }
		//! Substract matrix v component by component
		void operator -=(const Matrix22 &v) { a -= v.a; b -= v.b; c -= v.c; d -= v.d; }
		//! Multiply each component by scalar f
		void operator *=(double f) { a *= f; b *= f; c *= f; d *= f; }
		//! Divive each component by scalar f
		void operator /=(double f) { a /= f; b /= f; c /= f; d /= f; }
		//! Add matrix v component by component and return the resulting matrix
		Matrix22 operator +(const Matrix22 &v) const { Matrix22 n; n.a = a + v.a; n.b = b + v.b; n.c = c + v.c; n.d = d + v.d; return n; }
		//! Subtract matrix v component by component and return the resulting matrix
		Matrix22 operator -(const Matrix22 &v) const { Matrix22 n; n.a = a - v.a; n.b = b - v.b; n.c = c - v.c; n.d = d - v.d; return n; }
		//! Multiply each component by scalar f and return the resulting matrix
		Matrix22 operator *(double f) const { Matrix22 n; n.a = a * f; n.b = b * f; n.c = c * f; n.d = d * f; return n; }
		//! Divide each component by scalar f and return the resulting matrix
		Matrix22 operator /(double f) const { Matrix22 n; n.a = a / f; n.b = b / f; n.c = c / f; n.d = d / f; return n; }
		
		//! Multiply vector v and return the resulting vector
		Point operator*(const Point &v) { Point n; n.x = v.x*a + v.y*c; n.y = v.x*b + v.y*d; return n; }
	};
	
	//! A segment in a 2D space, basically two points
	/*! \ingroup an */
	struct Segment
	{
		//! Constructor, create segment from point (ax, ay) to point (bx, by)
		Segment(double ax, double ay, double bx, double by) { this->a.x = ax; this->a.y = ay; this->b.x = bx; this->b.y = by; }
		//! Constructor, create segment from point (array[0], array[1]) to point (array[2], array[3])
		Segment(double array[4]) { a.x = array[0]; a.y = array[1]; b.x = array[2]; b.y = array[3]; }
		//! Constructor, create segment from point p1 to point p2
		Segment(const Point &p1, const Point &p2) { a = p1; b = p2; }
		
		//! Start point
		Point a;
		//! End point
		Point b;
	
		//! Compute the distance of p to this segment
		double dist(const Point &p) const
		{
			Vector n(a.y-b.y, b.x-a.x);
			Vector u = n.unitary();
			Vector ap = p-a;
			return ap * u;
		}
	
		//! Return true if o intersect this segment
		bool doesIntersect(const Segment &o) const
		{
			double s2da = dist (o.a);
			double s2db = dist (o.b);
			double s1da = o.dist (a);
			double s1db = o.dist (b);
			return (s2da*s2db<0) && (s1da*s1db<0);
		}
	};
	
	//! Polygone, which is a vector of points. Anti-clockwise, standard trigonometric orientation
	/*! \ingroup an */
	typedef std::vector<Point> Polygone;
	
	//! Normlize an angle to be between -PI and +PI.
	/*! \ingroup an */
	inline double normalizeAngle(double angle)
	{
		while (angle > M_PI)
			angle -= 2*M_PI;
		while (angle < -M_PI)
			angle += 2*M_PI;
		return angle;
	}
  
	//! get the intersection point between two line segments
	//! returns Point(HUGE_VAL, HUGE_VAL) if there's no intersection
	//! added by yvan.bourquin@epfl.ch
	/*! \ingroup an */
	inline Point getIntersection(const Segment &s1, const Segment &s2)
	{
		// compute first segment's equation
		double c1 = s1.a.y + (-s1.a.x / (s1.b.x - s1.a.x)) * (s1.b.y - s1.a.y);
		double m1 = (s1.b.y - s1.a.y) / (s1.b.x - s1.a.x);
 
		// compute second segment's equation
		double c2 = s2.a.y + (-s2.a.x / (s2.b.x - s2.a.x)) * (s2.b.y - s2.a.y);
		double m2 = (s2.b.y - s2.a.y) / (s2.b.x - s2.a.x);

		// are the lines parallel ?
		if (m1 == m2)
			return Point(HUGE_VAL, HUGE_VAL);

		double x1 = s1.a.x;
		double x2 = s1.b.x;
		double x3 = s2.a.x;
		double x4 = s2.b.x;
		double y1 = s1.a.y;
		double y2 = s1.b.y;
		double y3 = s2.a.y;
		double y4 = s2.b.y;

		// make sure x1 < x2
		if (x1 > x2)
		{
			double temp = x1;
			x1 = x2;
			x2 = temp;
		}

		// make sure x3 < x4
		if (x3 > x4)
		{
			double temp = x3;
			x3 = x4;
			x4 = temp;
		}

		// make sure y1 < y2
		if (y1 > y2)
		{
			double temp = y1;
			y1 = y2;
			y2 = temp;
		}

		// make sure y3 < y4
		if (y3 > y4)
		{
			double temp = y3;
			y3 = y4;
			y4 = temp;
		}

		// intersection point in case of infinite slopes
		double x;
		double y;

		// infinite slope m1
		if (x1 == x2)
		{
			x = x1;
			y = m2 * x1 + c2;
			if (x > x3 && x < x4 && y > y1 && y <y2)
				return Point(x, y);
			else
				return Point(HUGE_VAL, HUGE_VAL);
		}

		// infinite slope m2
		if (x3 == x4)
		{
			x = x3;
			y = m1 * x3 + c1;
			if (x > x1 && x < x2 && y > y3 && y < y4)
				return Point(x, y);
			else
				return Point(HUGE_VAL, HUGE_VAL);
		}
		
		// compute lines intersection point
		x = (c2 - c1) / (m1 - m2);

		// see whether x in in both ranges [x1, x2] and [x3, x4]
		if (x > x1 && x < x2 && x > x3 && x < x4)
			return Point(x, m1 * x + c1);
  
		return Point(HUGE_VAL, HUGE_VAL);
	}
}

#endif
