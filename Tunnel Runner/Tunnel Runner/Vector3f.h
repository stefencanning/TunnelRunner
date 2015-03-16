#pragma once
#ifndef VECTOR3F_H
#define VECTOR3F_H
class Vector3f
{
public:
	///Destructor method: deletes this object at termination/clean up 
	~Vector3f(void);
	///constructor method: creates a new Vector3f object using the information passed in
	Vector3f(float x, float y,float z);
	///constructor method: creates a new Vector3f object using the information passed in
	Vector3f();
	///stores the x coordinate of the vector
	float x;
	///stores the y coordinate of the vector
	float y;
	///stores the z coordinate of the vector
	float z;
};
#endif

