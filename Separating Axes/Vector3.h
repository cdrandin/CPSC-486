#include <iostream>
#include <fstream>
#include <cmath>
#include <gl/glut.h>

#ifndef VECTOR3_H
#define VECTOR3_H

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288
#endif

#ifndef DEG2RAD
#define DEG2RAD( theta ) ((theta) * (M_PI/180.0))
#endif

#ifndef RAD2DEG
#define RAD2DEG( theta ) ((theta) * (180.0/M_PI))
#endif

#ifndef ABS
#define ABS( x ) ((x) < (0) ? (-x) : (x))
#endif

#ifndef SQR
#define SQR( x ) ((x) * (x))
#endif

#ifndef MAX
#define MAX( a, b ) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN( a, b ) ((a) < (b) ? (a) : (b))
#endif

#ifndef MSGFX_FP
#define MSGFX_FP

#define FP_EPSILON 1e-9
#define ALMOST_ZERO FP_EPSILON

#define FP_EQUAL(a, b, delta) ( ((a) == (b)) || \
((a)-(delta) < (b) && \
  (a)+(delta) > (b)) )

#define FP_LT(a, b, delta)  (fabs((a) - (b)) < (delta))

#define FP_GT(a, b, delta)  (fabs((a) - (b)) > (delta))

#define IOS_FP_PRECISION 5
#endif

#ifndef XYZW
#define XYZW
  enum{X = 0, Y, Z, W};
#endif

class Vector3
{
	GLfloat _data[3];
public:
	Vector3                         ( void           );
	Vector3                         ( const Vector3& );
	Vector3                         ( const GLfloat&, const GLfloat&, const GLfloat& );
	explicit Vector3                ( const GLfloat* );
	explicit Vector3                ( const Vector3* );
	~Vector3                        ( void           );

	bool operator==                 ( const Vector3& ) const;
	bool operator!=                 ( const Vector3& ) const;
	Vector3& operator=              ( const Vector3& );

	/*    ADDITION    */
	Vector3 operator+               ( const Vector3& ) const;	
	const Vector3& operator +=      ( const Vector3& );
	Vector3 operator+               ( const GLfloat& ) const;
	const Vector3& operator +=      ( const GLfloat& );

	/*    SUBTRACTION    */
	Vector3 operator-               ( const Vector3& ) const;
	const Vector3& operator-=       ( const Vector3& );
	Vector3 operator-               ( const GLfloat& ) const;
	const Vector3& operator-=       ( const GLfloat& );
	Vector3 operator-               ( ) const;

	/*    MULTIPLICATION    */
	Vector3 operator*               ( const GLfloat& ) const;
	const Vector3& operator*=       ( const GLfloat& );
	Vector3 operator*               ( const Vector3& ) const;
	const friend Vector3 operator*  ( GLfloat, Vector3& );// 3 * Vector3(...)

	/*    DIVISION    */
	Vector3 operator/               ( const GLfloat& ) const;
	const Vector3& operator/=       ( const GLfloat& );

	// Set 
	inline const GLfloat operator[] ( const int x ) const;
	// Get
	GLfloat& operator[] ( const int x );

	// Return a pointer
	const double* constPtr          ( ) const;

	// Get
	const double x                  ( ) const;
	const double y                  ( ) const;
	const double z                  ( ) const;

	// Set
	void x                          ( const GLfloat& a );
	void y                          ( const GLfloat& b );
	void z                          ( const GLfloat& c );

	// Vector properties
	GLfloat Magnitude               () const;
	GLfloat MagnitudeSqrd           () const;
	GLfloat Angle                   ( const Vector3& ) const;
	void Normalize                  ();
	GLfloat DistanceFrom            ( const Vector3& ) const;
	GLfloat SquaredDistanceFrom     ( const Vector3& ) const; // Quicker b/c no sqrt cost. Gives direction.
	GLfloat DotProduct              ( const Vector3& ) const;


	void Display                    ();
	void DisplayToFile              ( char* fileName, std::ios::openmode mode );
};

Vector3 CrossProduct                ( Vector3&, Vector3& );
Vector3 Normal                      ( Vector3&, Vector3&, Vector3& );

std::ostream& operator<<            ( std::ostream&, const Vector3& );
#endif