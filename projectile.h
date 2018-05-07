#pragma once
#include <unistd.h> //For sleep()
#include <string>
#include <iostream> //Required for cout
#include <GL/glut.h> //apt install freeglut3-dev for Debian based systems

class Projectile{
	private:
		float x,y,diameter;
	public:
		Projectile();
		Projectile(float startX,float startY,float startDiameter);
		void output();
		Projectile duplicate(Projectile& pro);

		//Mutator methods
		void movePosition(float x,float y,float radius);
		void setPosition(float x,float y,float radius);;

		//Accessor methods
		float getDiameter();
		float getX();
		float getY();
		std::string describe();
};
