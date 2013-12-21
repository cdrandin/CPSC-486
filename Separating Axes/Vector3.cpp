#include "Vector3.h"

// Set vector to all 0
Vector3::Vector3 (void)
{ 
	_data[X] = static_cast<GLfloat>(0.0f);
	_data[Y] = static_cast<GLfloat>(0.0f);
	_data[Z] = static_cast<GLfloat>(0.0f);
}

Vector3::Vector3 ( const Vector3& myVector )
{
	_data[X] = myVector._data[X];
	_data[Y] = myVector._data[Y];
	_data[Z] = myVector._data[Z];
}

// Set vector by given value
Vector3::Vector3 ( const GLfloat& x, const GLfloat& y, const GLfloat& z)
{
	_data[X] = x;
	_data[Y] = y;
	_data[Z] = z;
}

Vector3::Vector3 ( const GLfloat* myVector )
{
	_data[X] = *(myVector+X);
	_data[Y] = *(myVector+Y);
	_data[Z] = *(myVector+Z);
}

Vector3::Vector3 ( const Vector3* myVector )
{
	_data[X] = myVector->_data[X];
	_data[Y] = myVector->_data[Y];
	_data[Z] = myVector->_data[Z];
}

Vector3::~Vector3 (void)
{}

bool Vector3::operator== ( const Vector3 & myVector ) const
{
	for(int i=X;i<=Z;++i)
		if(_data[i] != myVector._data[i])
			return false;

	return true;
}	

bool Vector3::operator!= ( const Vector3 & myVector ) const
{
	for(int i=X;i<=Z;++i)
		if(_data[i] != myVector._data[i])
			return true;

	return false;
}	
// Copy vector to new vector
// If vector is the same, return it back
Vector3& Vector3::operator= (const Vector3 &myVector)
{
	if (this == &myVector)
		return *this;

	for(int i=X;i<=Z;++i)
	{
		this->_data[i] = myVector._data[i];
	}

	return *this;
}

// Vector addition
Vector3 Vector3::operator+ (const Vector3& myVector) const
{
	Vector3 temp;

	temp._data[X] = this->_data[X] + myVector._data[X];
	temp._data[Y] = this->_data[Y] + myVector._data[Y];
	temp._data[Z] = this->_data[Z] + myVector._data[Z];

	return temp;
}

const Vector3& Vector3::operator += ( const Vector3& myVector )
{
	*this = *this + myVector;
	return *this;
}

// Value addition
Vector3 Vector3::operator+ (const GLfloat& value) const
{
	Vector3 temp;

	temp._data[X] = this->_data[X] + value;
	temp._data[Y] = this->_data[Y] + value;
	temp._data[Z] = this->_data[Z] + value;

	return temp;
}

const Vector3& Vector3::operator += (const GLfloat& scalar)
{
	*this = *this + scalar;
	return *this;
}
// Vector subtraction
Vector3 Vector3::operator- (const Vector3& myVector) const
{
	Vector3 temp;

	temp._data[X] = this->_data[X] - myVector._data[X];
	temp._data[Y] = this->_data[Y] - myVector._data[Y];
	temp._data[Z] = this->_data[Z] - myVector._data[Z];

	return temp;
}

const Vector3& Vector3::operator-= ( const Vector3& myVector)
{
	*this = *this - myVector;
	return *this;
}

// Value subtraction
Vector3 Vector3::operator- (const GLfloat& value) const
{
	Vector3 temp;

	temp._data[X] = this->_data[X] - value;
	temp._data[Y] = this->_data[Y] - value;
	temp._data[Z] = this->_data[Z] - value;

	return temp;
}

const Vector3& Vector3::operator-= ( const GLfloat& scalar)
{
	*this = *this - scalar;
	return *this;
}

// Allow negate operator
Vector3 Vector3::operator- () const
{
	Vector3 temp;

	temp._data[X] = this->_data[X]*-1;
	temp._data[Y] = this->_data[Y]*-1;
	temp._data[Z] = this->_data[Z]*-1;

	return temp;
}

// Vector multiplication with a scalar
Vector3 Vector3::operator* (const GLfloat& scalar) const
{
	Vector3 temp;

	temp._data[X] = this->_data[X]*scalar;
	temp._data[Y] = this->_data[Y]*scalar;
	temp._data[Z] = this->_data[Z]*scalar;

	return temp;
}

Vector3 Vector3::operator* (const Vector3& myVector) const
{
	Vector3 temp;

	temp._data[X] = this->_data[X] * myVector._data[X];
	temp._data[Y] = this->_data[Y] * myVector._data[Y];
	temp._data[Z] = this->_data[Z] * myVector._data[Z];

	return temp;
}

const Vector3& Vector3::operator*= (const GLfloat& scalar)
{
      *this = *this * scalar;
	  return *this;
}

// Vector multiplication with a scalar
const Vector3 operator* (GLfloat scalar, Vector3& myVector)
{
	Vector3 temp = myVector;

	temp._data[X] = myVector._data[X]*scalar;
	temp._data[Y] = myVector._data[Y]*scalar;
	temp._data[Z] = myVector._data[Z]*scalar;

	return temp;
}

// Division by scalar
Vector3 Vector3::operator/ ( const GLfloat& scalar ) const
{
	Vector3 temp;

	temp._data[X] = this->_data[X]/scalar;
	temp._data[Y] = this->_data[Y]/scalar;
	temp._data[Z] = this->_data[Z]/scalar;

	return temp;
}

const Vector3& Vector3::operator/= (const GLfloat& scalar )
{
	*this = *this/scalar;
	return *this;
}

const GLfloat Vector3::operator[] ( const int x ) const
{	return _data[x];   }

GLfloat& Vector3::operator[] ( const int x )
{
	return _data[x];
}

const double* Vector3::constPtr( ) const
{
	double* xyz = new double[3];

	*(xyz+X) = _data[X];
	*(xyz+Y) = _data[Y];
	*(xyz+Z) = _data[Z];

	return xyz;
}

double const Vector3::x ( ) const
{
	return this->_data[X];
}

double const Vector3::y ( ) const
{
	return this->_data[Y];
}

double const Vector3::z ( ) const
{
	return this->_data[Z];
}

void Vector3::x ( const GLfloat& a ) 
{   _data[X]=a;   }

void Vector3::y ( const GLfloat& b ) 
{	_data[Y]=b;   }

void Vector3::z ( const GLfloat& c ) 
{	_data[Z]=c;   }

// Print as line
std::ostream& operator<<( std::ostream& out, const Vector3& myVector)
{
	out<<"< "<<myVector.x()<<' '<<myVector.y()<<' '<<myVector.z()<<" >";
	return out;
}

// find the magnitude of the vector
GLfloat Vector3::Magnitude () const
{
	return ( sqrt(this->MagnitudeSqrd()) );
}

// find the direction of the vector
GLfloat Vector3::MagnitudeSqrd () const
{
	return ( _data[0] * _data[0] + _data[1] * _data[1] + _data[2] * _data[2] );
}

GLfloat Vector3::Angle ( const Vector3& myVector ) const
{
	GLfloat dot = this->DotProduct(myVector);
	GLfloat a = this->Magnitude();
	GLfloat b = myVector.Magnitude();

	return( dot/(a*b) );
}

// return the normalized value of the vector
void Vector3::Normalize ()
{
	_data[X] /= this->Magnitude();
	_data[Y] /= this->Magnitude();
	_data[Z] /= this->Magnitude();
}

GLfloat Vector3::DistanceFrom ( const Vector3& myVector ) const
{
	return sqrt( this->SquaredDistanceFrom(myVector) );
}

GLfloat Vector3::SquaredDistanceFrom ( const Vector3& myVector ) const
{
	return SQR(this->_data[X] - myVector._data[X]) + SQR(this->_data[Y] - myVector._data[Y]) + SQR(this->_data[Z] - myVector._data[Z]) ;
}

GLfloat Vector3::DotProduct ( const Vector3& myVector ) const
{
	    
		return ( this->_data[X] * myVector._data[X] +
			     this->_data[Y] * myVector._data[Y] +
			     this->_data[Z] * myVector._data[Z] );
}

// Nicely print out vector
void Vector3::Display ()
{
	std::cout<<"< ";
	for(int i=X;i<=Z;++i)
		std::cout<<this->_data[i]<<' ';
	std::cout<<'>'<<std::endl;
}

// Nicely print out vector in file
void Vector3::DisplayToFile ( char* fileName, std::ios::openmode mode )
{
	std::ofstream outfile;
	outfile.open(fileName, mode);
	outfile<<"< ";
	for(int i=X;i<=Z;++i)
		outfile<<this->_data[i]<<' ';
	outfile<<'>'<<std::endl;
	outfile.close();
}

// Cross Product between two vectors
Vector3 CrossProduct( Vector3& v1, Vector3& v2 )
{
	return ( Vector3(v1[Y]*v2[Z] - v1[Z]*v2[Y],
			         v1[Z]*v2[X] - v1[X]*v2[Z], 
					 v1[X]*v2[Y] - v1[Y]*v2[X]) );
}

//Vector3 Normal ( Vector3& a, Vector3& b, Vector3& c )
//{
//}