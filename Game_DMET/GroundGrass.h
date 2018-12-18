#pragma once
#include "pch.h"

class GroundGrass : public GameObject {
public:
	GLTexture tex;

	GroundGrass() {
		char buffer[80];
		strcpy(buffer, "Textures/ground.bmp");
		tex.Load(buffer);
		transform.localScale = Vector3f(2, 1, 2);
	}

	void RenderGround()
	{
		glPushMatrix();
		glDisable(GL_LIGHTING);	// Disable lighting 

		glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

		tex.Use();

		glPushMatrix();
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);	// Set quad normal direction.
		glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
		glVertex3f(-20, 0, -20);
		glTexCoord2f(5, 0);
		glVertex3f(20, 0, -20);
		glTexCoord2f(5, 5);
		glVertex3f(20, 0, 20);
		glTexCoord2f(0, 5);
		glVertex3f(-20, 0, 20);
		glEnd();
		glPopMatrix();

		glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

		glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
		glPopMatrix();
	}


	void Display() override
	{
		glPushMatrix();
		glTranslated(0, -1, 0);
		RenderGround();		
		glPopMatrix();
	}
};