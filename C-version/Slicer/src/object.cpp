#include "object.h"

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  angleOrbit = 0.0f;
	angleRotate = 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}


Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt, float X, float Y, float Z, float offset)
{
	// translation
	if (!pauseOrbit)
  	(orbit) ? angleOrbit += ((dt + offset)* M_PI/1000) * orbitSpeed: angleOrbit -= ((dt + offset)* M_PI/1000) * orbitSpeed;
	model = glm::translate(glm::mat4(1.0f), glm::vec3(X + 4.0*sin(angleOrbit), Y + 0.0, Z + 4.0*cos(angleOrbit)));

	// rotation
	if (!pauseRotate)
		(rotation) ? angleRotate += dt * M_PI/1000 : angleRotate -= dt * M_PI/1000;
	model = glm::rotate(model, (rotateSpeed*angleRotate), glm::vec3(0.0, 1.0, 0.0));

	/*
	// scale, right now at 0.5 scale value
	if (scale)
		model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));*/
}


glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

// getters
float Object::getX() const
{
	return model[3][0];
}

float Object::getY() const
{
	return model[3][1];
}

float Object::getZ() const
{
	return model[3][2];
}

// setters
void Object::setOrbitSpeed(float val)
{
	orbitSpeed = val;
}

void Object::setRotateSpeed(float val)
{
	rotateSpeed = val;
}

void Object::setScaleValue(float val)
{
	scaleVal = val;
}

void Object::setSpeeds(float o, float r, float s)
{
	orbitSpeed = o;
	rotateSpeed = r;
	scaleVal = s;
}

// util functions
void Object::keyPress(int keyValue)
{
	switch (keyValue) {
		case 1:
			orbit = !orbit;
			break;
		case 2:
			rotation = !rotation;
			break;
		case 3:
			pauseOrbit = !pauseOrbit;
			break;
		case 4:
			pauseRotate = !pauseRotate;
			break;
		case 5:		// speed up orbit
			orbitSpeed += 0.1;
			break;
		case 6:		// slow down orbit
			orbitSpeed -= 0.1;
			break;
		case 7:
			orbitSpeed = 1.0;
			break;
	}	// end switch
}

// update functions

