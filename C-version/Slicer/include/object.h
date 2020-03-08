#ifndef OBJECT_H
#define OBJECT_H
#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <assert.h>
#include <sys/time.h>
#include "graphics_headers.h"
#include "SDL.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float offset = 0.0f);
    void Render();

    glm::mat4 GetModel();

		// getters for X, Y, and Z coords of an object
		float getX() const;
		float getY() const;
		float getZ() const;

		// setters for orbit speed, rotation speed, and scale value
		void setOrbitSpeed(float val);
		void setRotateSpeed(float val);
		void setScaleValue(float val);
		
		// lazy function
		void setSpeeds(float o = 1.0, float r = 1.0, float s = 1.0);

		// handlers for inputs
		
		
  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angleOrbit;
		float angleRotate;

		// conditionals for orbit and rotation
		bool orbit = true;			// true = clockwise, false = counterclock
		bool rotation = true;		// true = clockwise, false = counterclock
		bool pauseOrbit = false;			
		bool pauseRotate = false;

		// int conditionals to keep track of orbit and rotation
		int orbit2 = 1;		// 1 = clockwise, -1 = counterclockwise, 0 = paused
		int rotation2 = 1;

		// variables for orbit & rotation speed, and scale value
		float orbitSpeed = 1.0;
		float rotateSpeed = 1.0;
		float scaleVal = 1.0;

		// update functions for each conditional
		void updateOrbitAngle(unsigned int dt);
		void updateRotationAngle(unsigned int dt);

		// util functions for the object
		void keyPress(int keyValue);
};

#endif /* OBJECT_H */
