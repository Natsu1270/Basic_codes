/*
TITLE: ASSIGNMENT1-COMPUTER GRAPHICS
*/
#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#define PI			3.1415926
#define	COLORNUM		14
#define DEG2RAD 3.14159f/180.0f


using namespace std;

#pragma region Support.h

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}
	void set(Color3& c)
	{
		r = c.r; g = c.g; b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}

};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw() {
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
private:
	float 	x, y;
};
class IntRect
{
public:
	IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void draw() {
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int  getWidth() { return (r - l); }
	int  getHeight() { return (t - b); }
private:
	int	l, r, b, t;
};
class RealRect
{
public:
	RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	float  getWidth() { return (r - l); }
	float  getHeight() { return (t - b); }
	void RealRect::draw() {
		glRectf(l, b, r, t);
		glFlush();
	};// draw this rectangle using OpenGL
private:
	float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	void flip()
	{
		x = -x; y = -y; z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};
#pragma endregion

#pragma region Support.cpp

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x*b.x + y*b.y + z*b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x*x + y*y + z*z);
	x = x / temp;
	y = y / temp;
	z = z / temp;
}

#pragma endregion

#pragma region Mesh.h

class VertexID  //Tập đỉnh
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face //Tập mặt 
{
public:
	int		nVerts;
	VertexID*	vert;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt; // Mảng các điểm Point3D.

	int		numFaces;
	Face*		face;

	float		slideX, slideY, slideZ;
	float		rotateX, rotateY, rotateZ;
	float		scaleX, scaleY, scaleZ;

public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
		slideX = 1;
		slideY = 1;
		slideZ = 1;
		rotateX = 10;
		rotateY = 10;
		rotateZ = 10;
		scaleX = scaleY = scaleZ = 2;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void SetColor(int colorIndex);
	void CreateMobiusStrip(int degree, int v);
	void CreateHoleOval(float r, float len, float h, float rr);
	void DrawWireframe(); //vẽ khung lưới đa giác
	void DrawColor(); // Tô màu lưới đa giác
	void CreateTetrahedron(); //Vẽ hình Tetrahedron
	void CreateCube(float	fSize); //Vẽ hình Cube
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateHoleCuboid(float x, float y, float z, float l);
	void CreateCylinder(float radius, float height, float degree);
	//void CreateOvan(float fHeight, float fLength, float fRadius,int nSegment);
	void CreateOval(float r, float len, float h);
	//void CreateOvan2(float , float , float , float );
};
#pragma endregion

#pragma region Mesh.cpp

float	ColorArr[COLORNUM][3] = {
	{ 1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },
	{ 0.0,  0.0, 1.0 },{ 1.0, 1.0, 0.0 },
	{ 1.0, 0.0, 1.0 },{ 0.0, 1.0, 1.0 },
	{ 0.3, 0.3, 0.3 },{ 0.5, 0.5, 0.5 },
	{ 0.9,  0.9, 0.9 },{ 1.0, 0.5, 0.5 },
	{ 0.5, 1.0, 0.5 },{ 0.5, 0.5, 1.0 },
	{ 0.0, 0.0, 0.0 },{ 0.5, 1.0, 0.3 }
};

//Ham setColor
void Mesh::SetColor(int colorIdx) {
	for (int f = 0; f < numFaces; f++) {
		for (int v = 0; v < face[f].nVerts; v++) {
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

//Tao hinh hop

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
int a = 0;
void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			ic = a % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
	a+=3;
}

void setface(Face *face, int nVerts, int faceindex, int vertindex[]) {
	face[faceindex].nVerts = nVerts;
	face[faceindex].vert = new VertexID[face[0].nVerts];
	face[faceindex].vert[0].vertIndex = 1;
	face[faceindex].vert[1].vertIndex = 5;
	face[faceindex].vert[2].vertIndex = 6;
	face[faceindex].vert[3].vertIndex = 2;
	for (int i = 0; i < face[faceindex].nVerts; i++) {
		face[faceindex].vert[i].vertIndex = vertindex[i];
		face[faceindex].vert[i].colorIndex = faceindex;
	}
}

void setrecface(Face *face, int faceindex, int vertindex, int offset) {
	face[faceindex].nVerts = 4;
	face[faceindex].vert = new VertexID[face[faceindex].nVerts];
	face[faceindex].vert[0].vertIndex = vertindex;
	face[faceindex].vert[1].vertIndex = vertindex + 1;
	face[faceindex].vert[2].vertIndex = vertindex + 1 + offset;
	face[faceindex].vert[3].vertIndex = vertindex + offset;
	for (int j = 0; j<face[faceindex].nVerts; j++)
		face[faceindex].vert[j].colorIndex = faceindex;
}

void iterativeSetRecFace(Face *face, int &faceindex, int vertindex, int offset, int iterative) {
	for (int i = 0; i < iterative; i++) {
		setrecface(face, faceindex, vertindex, offset);
		faceindex++;
		vertindex++;
	}
}

void Mesh::CreateCuboid(float fSizeX, float fSizeY, float	fSizeZ) {

	int i;
	float x = fSizeX / 2, y = fSizeY / 2, z = fSizeZ / 2;
	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-x, y, z);
	pt[1].set(x, y, z);
	pt[2].set(x, y, -z);
	pt[3].set(-x, y, -z);
	pt[4].set(-x, -y, z);
	pt[5].set(x, -y, z);
	pt[6].set(x, -y, -z);
	pt[7].set(-x, -y, -z);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	/*for (i = 0; i<face[0].nVerts; i++)
	face[0].vert[i].colorIndex = 0;*/

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	/*for (i = 0; i<face[1].nVerts; i++)
	face[1].vert[i].colorIndex = 1;*/

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	/*for (i = 0; i<face[2].nVerts; i++)
	face[2].vert[i].colorIndex = 2;*/

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	/*for (i = 0; i<face[3].nVerts; i++)
	face[3].vert[i].colorIndex = 3;*/

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	/*for (i = 0; i<face[4].nVerts; i++)
	face[4].vert[i].colorIndex = 4;*/

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	/*for (i = 0; i<face[5].nVerts; i++)
	face[5].vert[i].colorIndex = 5;*/
}
void Mesh::CreateHoleCuboid(float	fSizeX, float fSizeY, float	fSizeZ, float thick) {
	int i;
	float x = fSizeX / 2, y = fSizeY / 2, z = fSizeZ / 2;
	float holeX = x + thick, holeY = y, holeZ = z + thick;
	numVerts = 16;
	int outerleftvertindex[4] = { 1,5,6,2 };
	int topleftvertindex[4] = { 1,2,10,9 };
	int bottomleftvertindex[4] = { 5,6,14,13 };
	int innerleftvertindex[4] = { 9,13,14,10 };

	int outerrightvertindex[4] = { 0,3,7,4 };
	int toprightvertindex[4] = { 0,3,11,8 };
	int bottomrightvertindex[4] = { 4,7,15,12 };
	int innerrightvertindex[4] = { 8,11,15,12 };

	int outernearvertindex[4] = { 0,4,5,1 };
	int topnearvertindex[4] = { 0,1,9,8 };
	int bottomnearvertindex[4] = { 4,5,13,12 };
	int innernearvertindex[4] = { 8,9,13,12 };

	int outerfarvertindex[4] = { 2,3,7,6 };
	int topfarvertindex[4] = { 2,3,11,10 };
	int bottomfarvertindex[4] = { 6,7,15,14 };
	int innerfarvertindex[4] = { 10,11,15,14 };

	pt = new Point3[numVerts];
	pt[0].set(-x, y, z);
	pt[1].set(x, y, z);
	pt[2].set(x, y, -z);
	pt[3].set(-x, y, -z);
	pt[4].set(-x, -y, z);
	pt[5].set(x, -y, z);
	pt[6].set(x, -y, -z);
	pt[7].set(-x, -y, -z);

	pt[8].set(-holeX, holeY, holeZ);
	pt[9].set(holeX, holeY, holeZ);
	pt[10].set(holeX, holeY, -holeZ);
	pt[11].set(-holeX, holeY, -holeZ);
	pt[12].set(-holeX, -holeY, holeZ);
	pt[13].set(holeX, -holeY, holeZ);
	pt[14].set(holeX, -holeY, -holeZ);
	pt[15].set(-holeX, -holeY, -holeZ);

	numFaces = 16;
	face = new Face[numFaces];

	//Outer Left face
	setface(face, 4, 0, outerleftvertindex);
	//Top Left face
	setface(face, 4, 1, topleftvertindex);
	//Bottom Left face
	setface(face, 4, 2, bottomleftvertindex);
	//Inner Left face
	setface(face, 4, 3, innerleftvertindex);

	//Outer Right face
	setface(face, 4, 4, outerrightvertindex);
	//Top Right face
	setface(face, 4, 5, toprightvertindex);
	//Bottom Right face
	setface(face, 4, 6, bottomrightvertindex);
	//Inner Right face
	setface(face, 4, 7, innerrightvertindex);

	//Outer Near face
	setface(face, 4, 8, outernearvertindex);
	//Top Near face
	setface(face, 4, 9, topnearvertindex);
	//Bottom Near face
	setface(face, 4, 10, bottomnearvertindex);
	//Inner Near face
	setface(face, 4, 11, innernearvertindex);


	//Outer Far face
	setface(face, 4, 12, outerfarvertindex);
	//Top Far face
	setface(face, 4, 13, topfarvertindex);
	//Bottom Far face
	setface(face, 4, 14, bottomfarvertindex);
	//Inner Far face
	setface(face, 4, 15, innerfarvertindex);
}
void Mesh::CreateCylinder(float	radius, float height, float degree) {
	numVerts = (360 / degree) * 2 + 2;
	int numVertsSurround = (360 / degree) * 2;
	int bottom_center_index = numVerts - 2;
	int top_center_index = numVerts - 1;
	pt = new Point3[numVerts];
	numFaces = (360 / degree) * 3;
	face = new Face[numFaces];
	//set 2 center points
	pt[bottom_center_index].set(0, -height / 2, 0);
	pt[top_center_index].set(0, height / 2, 0);

	//set bottom points
	for (int i = 0; i < numVertsSurround / 2; i++) {
		float x = pt[bottom_center_index].x + sin(DEG2RAD * i * degree)*radius;
		float y = pt[bottom_center_index].y;
		float z = pt[bottom_center_index].z + cos(DEG2RAD * i * degree)*radius;
		pt[i].set(x, y, z);
	}
	//set top points
	for (int i = numVertsSurround / 2; i < numVertsSurround; i++) {
		float x = pt[top_center_index].x + sin(DEG2RAD * i * degree)*radius;
		float y = pt[top_center_index].y;
		float z = pt[top_center_index].z + cos(DEG2RAD * i * degree)*radius;
		pt[i].set(x, y, z);
	}

	//set bottom face 
	for (int i = 0; i < numFaces / 3; i++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		if (i == numFaces / 3 - 1) {
			face[i].vert[0].vertIndex = bottom_center_index;
			face[i].vert[1].vertIndex = i;
			face[i].vert[2].vertIndex = 0;
		}
		else {
			face[i].vert[0].vertIndex = bottom_center_index;
			face[i].vert[1].vertIndex = i;
			face[i].vert[2].vertIndex = i + 1;
		}
		/*for (int j = 0; j<face[i].nVerts; j++)
		face[i].vert[j].colorIndex = i;*/
	}

	//set top face
	for (int i = numFaces / 3; i < numFaces * 2 / 3; i++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		if (i == numFaces * 2 / 3 - 1) {
			face[i].vert[0].vertIndex = top_center_index;
			face[i].vert[1].vertIndex = i;
			face[i].vert[2].vertIndex = numVertsSurround / 2;
		}
		else {
			face[i].vert[0].vertIndex = top_center_index;
			face[i].vert[1].vertIndex = i;
			face[i].vert[2].vertIndex = i + 1;
		}
		/*for (int j = 0; j<face[i].nVerts; j++)
		face[i].vert[j].colorIndex = i;*/
	}
	//set surround face
	int j;
	j = 0;
	for (int i = numFaces * 2 / 3; i < numFaces; i++) {
		int offset_top_bottom = numVertsSurround / 2;
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		if (i == numFaces - 1) {
			face[i].vert[0].vertIndex = j;
			face[i].vert[1].vertIndex = 0;
			face[i].vert[2].vertIndex = offset_top_bottom;
			face[i].vert[3].vertIndex = j + offset_top_bottom;
		}
		else {
			face[i].vert[0].vertIndex = j;
			face[i].vert[1].vertIndex = j + 1;
			face[i].vert[2].vertIndex = j + 1 + offset_top_bottom;
			face[i].vert[3].vertIndex = j + offset_top_bottom;
		}
		/*for (int k = 0; k<face[i].nVerts; k++)
		face[i].vert[k].colorIndex = i;*/
		j++;
	}
}
void Mesh::CreateOval(float R, float len, float height) {
	int degree = 5;
	numVerts = ((360 / degree) / 2 + 1) * 2 * 2;
	pt = new Point3[numVerts];
	numFaces = (360 / degree) + 4;
	face = new Face[numFaces];
	int counter = 0;
	//set bottom near points
	for (int i = 0; i < numVerts / 4; i++) {
		float x = sin(DEG2RAD * (i * degree - 90))*R;
		float y = -height / 2;
		float z = len / 2 + cos(DEG2RAD *(i * degree - 90))*R;
		pt[counter].set(z, y, x);
		counter++;
	}
	//set top near points
	for (int i = 0; i < numVerts / 4; i++) {
		float x = sin(DEG2RAD *(i * degree - 90))*R;
		float y = height / 2;
		float z = len / 2 + cos(DEG2RAD *(i * degree - 90))*R;
		pt[counter].set(z, y, x);
		counter++;
	}
	//set bottom far points
	for (int i = 0; i < numVerts / 4; i++) {
		float x = sin(DEG2RAD * (i * degree + 90))*R;
		float y = -height / 2;
		float z = -len / 2 + cos(DEG2RAD * (i * degree + 90))*R;
		pt[counter].set(z, y, x);
		counter++;
	}
	//set top far points
	for (int i = 0; i < numVerts / 4; i++) {
		float x = sin(DEG2RAD * (i * degree + 90))*R;
		float y = height / 2;
		float z = -len / 2 + cos(DEG2RAD *(i * degree + 90))*R;
		pt[counter].set(z, y, x);
		counter++;
	}
	int offset_top_bottom = numVerts / 4;
	int offset_near_far = numVerts / 2;
	int nearvertindex = 0;
	for (int i = 0; i < (numFaces - 4) / 2; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = nearvertindex;
		face[i].vert[1].vertIndex = nearvertindex + 1;
		face[i].vert[2].vertIndex = nearvertindex + 1 + offset_top_bottom;
		face[i].vert[3].vertIndex = nearvertindex + offset_top_bottom;
		nearvertindex++;
		/*for (int j = 0; j<face[i].nVerts; j++)
		face[i].vert[j].colorIndex = i;*/
	}
	int farvertindex = numVerts / 2;
	for (int i = (numFaces - 4) / 2; i < (numFaces - 4); i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = farvertindex;
		face[i].vert[1].vertIndex = farvertindex + 1;
		face[i].vert[2].vertIndex = farvertindex + 1 + offset_top_bottom;
		face[i].vert[3].vertIndex = farvertindex + offset_top_bottom;
		farvertindex++;
		/*for (int j = 0; j<face[i].nVerts; j++)
		face[i].vert[j].colorIndex = i;*/
	}
	int rightfacevertindex[4] = { 0,numVerts / 4,numVerts - 1,numVerts * 3 / 4 - 1 };
	int leftfacevertindex[4] = { numVerts / 4 - 1,numVerts / 2 - 1,numVerts * 3 / 4 ,numVerts / 2 };
	setface(face, 4, numFaces - 4, rightfacevertindex);
	setface(face, 4, numFaces - 3, leftfacevertindex);

	//bottom face
	face[numFaces - 2].nVerts = numVerts / 2;
	face[numFaces - 2].vert = new VertexID[face[numFaces - 2].nVerts];
	for (int j = 0; j<numVerts / 4; j++) {
		face[numFaces - 2].vert[j].vertIndex = j;
		face[numFaces - 2].vert[j + numVerts / 4].vertIndex = j + offset_near_far;
	}
	/*for (int j = 0; j<face[numFaces - 2].nVerts; j++)
	face[numFaces - 2].vert[j].colorIndex = numFaces - 2;*/
	//top face
	face[numFaces - 1].nVerts = numVerts / 2;
	face[numFaces - 1].vert = new VertexID[face[numFaces - 1].nVerts];
	for (int j = 0; j<numVerts / 4; j++) {
		face[numFaces - 1].vert[j].vertIndex = j + numVerts / 4;
		face[numFaces - 1].vert[j + numVerts / 4].vertIndex = j + offset_near_far + numVerts / 4;
	}
	for (int j = 0; j<face[numFaces - 1].nVerts; j++)
		face[numFaces - 1].vert[j].colorIndex = numFaces - 1;
}
void Mesh::CreateMobiusStrip(int degree, int v) {
	float* vValue;
	vValue = new float[v + 1];
	float tmpstep = 2.0f / v;
	vValue[0] = -1;
	vValue[v] = 1;
	for (int i = 1; i < v; i++) {
		float value = -1 + tmpstep*i;
		vValue[i] = value;
	}
	float b = vValue[0];
	float c = vValue[1];
	float d = vValue[2];
	float e = vValue[3];
	numVerts = (360 / degree)*(v + 1);
	pt = new Point3[numVerts];
	numFaces = (360 / degree)*v;
	face = new Face[numFaces];
	int offset = 360 / degree;
	int vertIndex = 0;
	for (int i = 0; i < v + 1; i++) {
		for (int j = 0; j < 360 / degree; j++) {
			float x = (1 + (vValue[i] / 2)*cos(((float)degree*j*DEG2RAD) / 2))*cos((float)degree*j*DEG2RAD);
			float y = (1 + (vValue[i] / 2)*cos(((float)degree*j*DEG2RAD) / 2))*sin((float)degree*j*DEG2RAD);
			float z = (vValue[i] / 2)*sin((float)degree*j*DEG2RAD / 2);
			pt[vertIndex++].set(x, y, z);
		}
	}
	int faceIndex = 0;
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < 360 / degree; j++) {
			face[faceIndex].nVerts = 4;
			face[faceIndex].vert = new VertexID[4];
			face[faceIndex].vert[0].vertIndex = faceIndex;
			face[faceIndex].vert[1].vertIndex = faceIndex + offset;
			face[faceIndex].vert[2].vertIndex = faceIndex + offset + 1;
			face[faceIndex].vert[3].vertIndex = faceIndex + 1;
			for (int k = 0; k < face[faceIndex].nVerts; k++)
				face[faceIndex].vert[k].colorIndex = numFaces - 1;
			faceIndex++;
		}
	}
}
void Mesh::CreateHoleOval(float outerRadius, float innerRadius, float len, float height) {
	int degree = 5;
	numVerts = ((360 / degree) / 2 + 1) * 2 * 2 * 2;
	pt = new Point3[numVerts];
	numFaces = (360 / degree) * 4 + 4 * 2;
	face = new Face[numFaces];
	int counter = 0;
	int offset_top_bottom = numVerts / 8;
	int offset_near_far = numVerts / 4;
	int offset_outer_inner = numVerts / 2;
	//set bottom near outer points
	for (int i = 0; i < numVerts / 8; i++) {
		float x = sin(DEG2RAD * (i * degree - 90))*outerRadius;
		float y = -height / 2;
		float z = len / 2 + cos(DEG2RAD *(i * degree - 90))*outerRadius;
		pt[counter].set(z, y, x);
		counter++;
	}
	//set top near outer points
	for (int i = 0; i < numVerts / 8; i++) {
		float x = sin(DEG2RAD *(i * degree - 90))*outerRadius;
		float y = height / 2;
		float z = len / 2 + cos(DEG2RAD *(i * degree - 90))*outerRadius;
		pt[counter].set(z, y, x);
		counter++;
	}
	//set bottom far outer points
	for (int i = 0; i < numVerts / 8; i++) {
		float x = sin(DEG2RAD * (i * degree + 90))*outerRadius;
		float y = -height / 2;
		float z = -len / 2 + cos(DEG2RAD * (i * degree + 90))*outerRadius;
		pt[counter].set(z, y, x);
		counter++;
	}
	//set top far outer points
	for (int i = 0; i < numVerts / 8; i++) {
		float x = sin(DEG2RAD * (i * degree + 90))*outerRadius;
		float y = height / 2;
		float z = -len / 2 + cos(DEG2RAD *(i * degree + 90))*outerRadius;
		pt[counter].set(z, y, x);
		counter++;
	}


	//set bottom near inner points
	for (int i = 0; i < numVerts / 8; i++) {
		float x = sin(DEG2RAD * (i * degree - 90))*innerRadius;
		float y = -height / 2;
		float z = len / 2 + cos(DEG2RAD *(i * degree - 90))*innerRadius;
		pt[counter].set(z, y, x);
		counter++;
	}
	//set top near inner points
	for (int i = 0; i < numVerts / 8; i++) {
		float x = sin(DEG2RAD *(i * degree - 90))*innerRadius;
		float y = height / 2;
		float z = len / 2 + cos(DEG2RAD *(i * degree - 90))*innerRadius;
		pt[counter].set(z, y, x);
		counter++;
	}
	//set bottom far inner points
	for (int i = 0; i < numVerts / 8; i++) {
		float x = sin(DEG2RAD * (i * degree + 90))*innerRadius;
		float y = -height / 2;
		float z = -len / 2 + cos(DEG2RAD * (i * degree + 90))*innerRadius;
		pt[counter].set(z, y, x);
		counter++;
	}
	//set top far inner points
	for (int i = 0; i < numVerts / 8; i++) {
		float x = sin(DEG2RAD * (i * degree + 90))*innerRadius;
		float y = height / 2;
		float z = -len / 2 + cos(DEG2RAD *(i * degree + 90))*innerRadius;
		pt[counter].set(z, y, x);
		counter++;
	}
	int facecounter = 0;
	//set surround outer near face
	iterativeSetRecFace(face, facecounter, 0, offset_top_bottom, (numFaces - 4 * 2) / 8);

	//set surround outer far face
	iterativeSetRecFace(face, facecounter, offset_near_far, offset_top_bottom, (numFaces - 4 * 2) / 8);

	//set surround inner near face
	iterativeSetRecFace(face, facecounter, offset_outer_inner, offset_top_bottom, (numFaces - 4 * 2) / 8);

	//set surround inner far face
	iterativeSetRecFace(face, facecounter, offset_outer_inner + offset_near_far, offset_top_bottom, (numFaces - 4 * 2) / 8);

	//set bottom surround near face
	iterativeSetRecFace(face, facecounter, 0, offset_outer_inner, (numFaces - 4 * 2) / 8);

	//set bottom surround far face
	iterativeSetRecFace(face, facecounter, offset_near_far, offset_outer_inner, (numFaces - 4 * 2) / 8);

	//set top surround near face
	iterativeSetRecFace(face, facecounter, offset_top_bottom, offset_outer_inner, (numFaces - 4 * 2) / 8);

	//set top surround far face
	iterativeSetRecFace(face, facecounter, offset_top_bottom + offset_near_far, offset_outer_inner, (numFaces - 4 * 2) / 8);

	//set top left long face
	int offset_first_last = numVerts / 8 - 1;
	int rightouterfacevertindex[4] = { 0,numVerts / 8,numVerts / 2 - 1,numVerts * 3 / 8 - 1 };
	int leftouterfacevertindex[4] = { numVerts / 8 - 1,numVerts / 4 - 1,numVerts * 3 / 8 ,numVerts / 4 };
	int rightinnerfacevertindex[4] = { offset_outer_inner,offset_outer_inner + numVerts / 8,offset_outer_inner + numVerts / 2 - 1,offset_outer_inner + numVerts * 3 / 8 - 1 };
	int leftinnerfacevertindex[4] = { offset_outer_inner + numVerts / 8 - 1,offset_outer_inner + numVerts / 4 - 1,offset_outer_inner + numVerts * 3 / 8 ,offset_outer_inner + numVerts / 4 };
	int bottomrightfacevertindex[4] = { 0,offset_outer_inner,offset_near_far + offset_outer_inner + offset_first_last,offset_near_far + offset_first_last };
	int bottomleftfacevertindex[4] = { offset_first_last,offset_outer_inner + offset_first_last,offset_near_far + offset_outer_inner,offset_near_far };
	int toprightfacevertindex[4] = { offset_top_bottom,offset_outer_inner + offset_top_bottom,offset_top_bottom + offset_near_far + offset_outer_inner + offset_first_last,offset_top_bottom + offset_near_far + offset_first_last };
	int topleftfacevertindex[4] = { offset_top_bottom + offset_first_last,offset_outer_inner + offset_top_bottom + offset_first_last,offset_top_bottom + offset_near_far + offset_outer_inner,offset_top_bottom + offset_near_far };
	setface(face, 4, facecounter, rightouterfacevertindex);
	facecounter++;
	setface(face, 4, facecounter, leftouterfacevertindex);
	facecounter++;
	setface(face, 4, facecounter, rightinnerfacevertindex);
	facecounter++;
	setface(face, 4, facecounter, leftinnerfacevertindex);
	facecounter++;
	setface(face, 4, facecounter, bottomrightfacevertindex);
	facecounter++;
	setface(face, 4, facecounter, bottomleftfacevertindex);
	facecounter++;
	setface(face, 4, facecounter, toprightfacevertindex);
	facecounter++;
	setface(face, 4, facecounter, topleftfacevertindex);
	facecounter++;
}
#pragma endregion

#pragma region Ass1.cpp

int		screenWidth = 600;
int		screenHeight = 600;

bool	bWireFrame = 0;

float	baseRadius = 0.8;
float	baseHeight = 0.2;
float	baseRotateStep = 5;

float	columnSizeX = 0.25;
float	columnSizeZ = columnSizeX;
float	columnSizeY = 5;

float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool	b4View = false;
bool	bAnimated = false;

class MeshXYZ : public Mesh {
public:
	float xSize, ySize, zSize;
	void set(float x, float y, float z) {
		xSize = x;
		ySize = y;
		zSize = z;
	}
};

class Giado1 {
public:
	MeshXYZ cuboid;
	MeshXYZ holecuboid;
	MeshXYZ* base;
	float giado1_holecuboidthick;
	virtual void set(float giado1_holecuboidthick, float giado1_cuboidSizeX, float giado1_cuboidSizeY, float giado1_cuboidSizeZ,
		float giado1_holecuboidSizeX, float giado1_holecuboidSizeY,
		float giado1_holecuboidSizeZ, MeshXYZ* base) {
		this->giado1_holecuboidthick = giado1_holecuboidthick;
		cuboid.set(giado1_cuboidSizeX, giado1_cuboidSizeY, giado1_cuboidSizeZ);
		holecuboid.set(giado1_holecuboidSizeX, giado1_holecuboidSizeY, giado1_holecuboidSizeZ);
		this->base = base;
		cuboid.CreateCuboid(giado1_cuboidSizeX, giado1_cuboidSizeY, giado1_cuboidSizeZ);
		holecuboid.CreateHoleCuboid(giado1_holecuboidSizeX, giado1_holecuboidSizeY, giado1_holecuboidSizeZ, giado1_holecuboidthick);
		cuboid.SetColor(9);
		holecuboid.SetColor(9);
	}
	virtual void SetColor(int coloridx) {
		cuboid.SetColor(coloridx);
		holecuboid.SetColor(coloridx);
	}
	virtual void Draw() {
		float giado1_cuboidZ = cuboid.zSize / 2;
		float giado1_holeCuboidZ = holecuboid.zSize / 2;
		float columnZ = base->zSize / 2;
		glPushMatrix();
		glRotatef(base->rotateY, 0, 1, 0);
		glTranslated(0, base->ySize * 2 / 3, giado1_cuboidZ + columnZ);

		if (bWireFrame) {
			cuboid.DrawWireframe();
			glTranslated(0, 0, giado1_cuboidZ + giado1_holeCuboidZ + giado1_holecuboidthick);
			holecuboid.DrawWireframe();
		}
		else {
			cuboid.DrawColor();
			glTranslated(0, 0, giado1_cuboidZ + giado1_holeCuboidZ + giado1_holecuboidthick);
			holecuboid.DrawColor();
		}

		glPopMatrix();
	}
};
class Giado2 :Giado1 {
public:
	MeshXYZ thanhngang;
	MeshXYZ* basethanhngang;
	void set(float giado1_holecuboidthick, float giado1_cuboidSizeX,
		float giado1_cuboidSizeY, float giado1_cuboidSizeZ,
		float giado1_holecuboidSizeX, float giado1_holecuboidSizeY,
		float giado1_holecuboidSizeZ, MeshXYZ* base, float giado2_thanhngangX, float giado2_thanhngangY,
		float giado2_thanhngangZ) {
		Giado1::set(giado1_holecuboidthick, giado1_cuboidSizeX, giado1_cuboidSizeY, giado1_cuboidSizeZ, giado1_holecuboidSizeX, giado1_holecuboidSizeY, giado1_holecuboidSizeZ, &thanhngang);
		Giado1::SetColor(2);
		thanhngang.set(giado2_thanhngangX, giado2_thanhngangY, giado2_thanhngangZ);
		this->basethanhngang = base;
		thanhngang.CreateCuboid(giado2_thanhngangX, giado2_thanhngangY, giado2_thanhngangZ);
		thanhngang.SetColor(2);
		thanhngang.slideX = columnSizeY / 3;
		thanhngang.slideY = thanhngang.ySize / 2 + basethanhngang->zSize / 2;
	}
	void Draw() {
		glPushMatrix();
		glRotatef(90, 0, 0, 1);

		glRotatef(basethanhngang->rotateY, 1, 0, 0);
		glScalef(1, -1, 1);

		glTranslated(thanhngang.slideX, thanhngang.slideY, 0);
		//glTranslated(, baseHeight / 2.0 + columnSizeY * 1 / 3, 0);
		if (bWireFrame) {
			thanhngang.DrawWireframe();
		}
		else {
			thanhngang.DrawColor();
		}
		glTranslated(0, -thanhngang.slideY, 0);
		Giado1::Draw();

		glPopMatrix();
	}
};
class Tayquay {
public:
	MeshXYZ hinhtru1;
	MeshXYZ hinhtru2;
	MeshXYZ hinhoval;
	MeshXYZ* base;
	void set(float y1, float ovalr, float ovallen, float ovalh, MeshXYZ *base) {
		//hinhtru2.CreateCuboid(ovalr, ovalh, ovalr);
		hinhtru2.CreateCylinder(ovalr / 2, ovalh, 10);
		hinhtru2.set(ovalr / 2, ovalh, ovalr);
		hinhtru1.CreateCylinder(ovalr / 2, y1, 10);
		hinhtru1.set(ovalr / 2, y1, ovalr / 2);
		hinhoval.CreateOval(ovalr, ovallen, ovalh);
		hinhoval.set(ovallen, ovalh, ovalr);
		hinhoval.rotateX = 90;
		hinhtru2.slideX = ovallen / 2;
		hinhtru1.slideX = -ovallen / 2;
		this->base = base;
		hinhoval.SetColor(3);
		hinhtru2.SetColor(3);
		hinhtru1.SetColor(4);
	}
	void Draw() {
		glPushMatrix();
		glRotatef(base->rotateY, 0, 1, 0);
		glTranslatef(0, columnSizeY / 3, columnSizeZ);

		glRotatef(hinhoval.rotateX, 1, 0, 0);//rotate 90 do
		glRotatef(hinhtru2.rotateY, 0, 1, 0);
		glTranslatef(-hinhtru2.slideX, 0, 0);
		glPushMatrix();
		glTranslatef(hinhtru2.slideX, 0, 0);
		if (bWireFrame) {
			hinhtru2.DrawWireframe();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(hinhtru1.slideX, hinhtru1.ySize / 2, 0);
			hinhtru1.DrawWireframe();
			glPopMatrix();
			hinhoval.DrawWireframe();
		}
		else {
			hinhtru2.DrawColor();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(hinhtru1.slideX, hinhtru1.ySize / 2, 0);
			hinhtru1.DrawColor();
			glPopMatrix();
			hinhoval.DrawColor();
		}
		glPopMatrix();
	}
};
MeshXYZ	base;
MeshXYZ	column;
Giado1	giado1;
Giado2	giado2;
Tayquay tayquay;
class ThanhTruot1 {
public:
	MeshXYZ holeoval;
	MeshXYZ cuboid;
	MeshXYZ* base;
	Tayquay* tayquay;
	int index;
	virtual void set(float x1, float y1, float z1, float outerR, float innerR, float ovallen, float ovalh, MeshXYZ*base, Tayquay &tayquay) {
		cuboid.CreateCuboid(x1, y1, z1);
		cuboid.set(x1, y1, z1);
		holeoval.CreateHoleOval(outerR, innerR / 2, ovallen, ovalh);
		holeoval.set(outerR * 2, ovalh, ovallen + outerR * 2);
		this->base = base;
		this->tayquay = &tayquay;
		holeoval.SetColor(1);
		cuboid.SetColor(1);
	}

	virtual void Draw() {
		float y = sin(DEG2RAD*tayquay->hinhtru2.rotateY)*tayquay->hinhoval.xSize;
		glPushMatrix();
		glRotatef(base->rotateY, 0, 1, 0);
		glTranslatef(0, columnSizeY / 3, columnSizeZ * 3);
		glTranslatef(0, -y, 0);
		glRotatef(90, 1, 0, 0);
		if (bWireFrame) {
			holeoval.DrawWireframe();
			glRotatef(-90, 1, 0, 0);
			glTranslatef(0, cuboid.ySize / 2 + holeoval.xSize / 2, 0);
			cuboid.DrawWireframe();
		}
		else {
			holeoval.DrawColor();
			glRotatef(-90, 1, 0, 0);
			glTranslatef(0, cuboid.ySize / 2 + holeoval.xSize / 2, 0);
			cuboid.DrawColor();
		}
		glPopMatrix();
	}
};
class ThanhTruot2 :public ThanhTruot1 {
public:
	void Draw() {
		cuboid.SetColor(3);
		holeoval.SetColor(2);
		float y = cos(DEG2RAD*tayquay->hinhtru2.rotateY)*tayquay->hinhoval.xSize;
		glPushMatrix();
		glRotatef(base->rotateY, 0, 1, 0);
		glTranslatef(-y, columnSizeY / 3, columnSizeZ * 2);
		glRotatef(90, 1, 0, 0);
		glRotatef(-90, 0, 1, 0);
		if (bWireFrame) {
			holeoval.DrawWireframe();
			glRotatef(-90, 1, 0, 0);
			glTranslatef(0, cuboid.ySize / 2 + holeoval.xSize / 2, 0);
			cuboid.DrawWireframe();
		}
		else {
			holeoval.DrawColor();
			glRotatef(-90, 1, 0, 0);
			glTranslatef(0, cuboid.ySize / 2 + holeoval.xSize / 2, 0);
			cuboid.DrawColor();
		}
		glPopMatrix();
	}
};
ThanhTruot1 thanhtruot1;
ThanhTruot2 thanhtruot2;
float giado1_holecuboidthick = 0.1;
float giado1_cuboidSizeX = columnSizeX;
float giado1_cuboidSizeY = baseHeight * 3 / 2;
float giado1_cuboidSizeZ = columnSizeZ * 2 - giado1_holecuboidthick;
float giado1_holecuboidSizeX = columnSizeX;
float giado1_holecuboidSizeY = baseHeight * 2;
float giado1_holecuboidSizeZ = columnSizeZ;

float giado2_thanhngangX = columnSizeX;
float giado2_thanhngangY = columnSizeY * 3 / 5;
float giado2_thanhngangZ = columnSizeZ;

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		base.rotateY += baseRotateStep;
		if (base.rotateY > 360)
			base.rotateY -= 360;
		break;
	case '2':
		base.rotateY -= baseRotateStep;
		if (base.rotateY < 0)
			base.rotateY += 360;
		break;
	case '3':
		tayquay.hinhtru2.rotateY += baseRotateStep;
		if (tayquay.hinhtru2.rotateY > 360)
			tayquay.hinhtru2.rotateY -= 360;
		break;
	case '4':
		tayquay.hinhtru2.rotateY -= baseRotateStep;
		if (tayquay.hinhtru2.rotateY < 0)
			tayquay.hinhtru2.rotateY += 360;
		break;
	case 'a':
	case 'A':
		if (!bAnimated) {
		}
		bAnimated = !bAnimated;
		break;
	case 'w': case 'W':
		bWireFrame = !bWireFrame;
		break;
	case 'r': case 'R':
		base.rotateY = 0;
		tayquay.hinhtru2.rotateY = 0;
		break;
	case '+':
		camera_dis += 0.1;
		break;
	case '-':
		camera_dis -= 0.1;
		break;
	case 'v':case'V':
		b4View = !b4View;
	}
	glutPostRedisplay();
}
void mySpecialKeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		camera_angle -= 1;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 1;
		break;
	case GLUT_KEY_UP:
		camera_height += 0.1;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.1;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);//x
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);//y
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);//z
	glVertex3f(0, 0, 4);
	glEnd();
}




void drawBase()
{
	glPushMatrix();

	glTranslated(0, baseHeight / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);

	if (bWireFrame)
		base.DrawWireframe();
	else
		base.DrawColor();

	glPopMatrix();
}
void drawColumn()
{
	glPushMatrix();
	column.rotateY = base.rotateY;
	glTranslated(0, baseHeight / 2.0 + columnSizeY / 2, 0);
	glRotatef(column.rotateY, 0, 1, 0);

	if (bWireFrame)
		column.DrawWireframe();
	else
		column.DrawColor();

	glPopMatrix();
}
void drawGiado1()
{
	giado1.Draw();
}
//void drawGiado2() {
//	glPushMatrix();
//	glRotatef(base.rotateY, 0, 1, 0);
//	glTranslated(giado2_thanhngangY/2+columnSizeZ/2, baseHeight / 2.0 + columnSizeY * 1 / 3, 0);
//
//	if (bWireFrame) {
//
//		glRotatef(90, 0, 0, 1);
//		giado2[0].DrawWireframe();
//	}
//	else {
//		glRotatef(90, 0, 0, 1);
//		giado2[0].DrawColor();
//	}
//
//	glPopMatrix();
//}
void drawGiado2() {
	giado2.Draw();
}
void drawContraption() {
	drawAxis();
	drawBase();
	drawColumn();
	drawGiado1();
	drawGiado2();
	tayquay.Draw();
	thanhtruot1.Draw();
	thanhtruot2.Draw();
}


void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera_X = camera_dis*sin(DEG2RAD*camera_angle);
	camera_Y = camera_height;
	camera_Z = camera_dis*cos(DEG2RAD*camera_angle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!b4View) {
		gluLookAt(camera_X, camera_Y, camera_Z, 0, 1, 0, 0, 1, 0);
		glViewport(0, 0, screenWidth, screenHeight);
		drawContraption();
	}
	else {
		gluLookAt(camera_X, camera_Y, camera_Z, 0, 1, 0, 0, 1, 0);
		glViewport(0, 0, screenWidth / 2, screenHeight / 2);
		glRotatef(90, 0, 1, 0);
		drawContraption();
		glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight / 2);
		glRotatef(90, 0, 1, 0);
		drawContraption();
		glViewport(0, screenHeight / 2, screenWidth / 2, screenHeight / 2);
		glRotatef(90, 0, 1, 0);
		drawContraption();
		glViewport(screenWidth / 2, screenHeight / 2, screenWidth / 2, screenHeight / 2);
		glRotatef(90, 0, 1, 0);
		drawContraption();
	}
	//drawAxis();
	//drawBase();
	//drawColumn();
	//drawGiado1();
	//drawGiado2();
	//tayquay.Draw();
	//thanhtruot1.Draw();
	//thanhtruot2.Draw();
	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	camera_angle = 0;
	camera_height = 4;
	camera_dis = 6;
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, 1, 10);
	gluPerspective(90, 1, 0.1, 100);
	//glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}


void myDelay()
{
	for (int i = 0; i<20000; i++)
		for (int j = 0; j<30; j++)
			sin(100.0f);
}

void myIdle()
{
	if (bAnimated == false)
		return;
	float rotateStepInc = 2;
	
	baseRotateStep = rotateStepInc;
	tayquay.hinhtru2.rotateY += baseRotateStep;
	if (tayquay.hinhtru2.rotateY > 360)
		tayquay.hinhtru2.rotateY -= 360;
	base.rotateY += baseRotateStep;
	if (base.rotateY > 360)
		base.rotateY -= 360;

	myDelay();

	myDisplay();
}

int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Assignment1-Bui Duy Hung(1511333)"); // open the screen window

	cout << "Press 1, 2 to rotate the base" << endl;
	cout << "Press 3, 4 to rotate the arm" << endl;
	cout << "Press R, r to reset" << endl;
	cout << "Press W, w to switch between wireframe and solid mode" << endl;
	cout << "V, v to switch between 1 and 4 views" << endl;
	cout << "A, a to turn on/off animation" << endl;
	cout << "Press '+' to increase camera distance." << endl;
	cout << "Press '-' to decrease camera distance." << endl;
	cout << "Press 'up arrow' to increase camera height." << endl;
	cout << "Press 'down arrow' to decrease camera height." << endl;
	cout << "Press '<-' to rotate camera clocewise." << endl;
	cout << "Press '->' to rotate camera counterclockwise." << endl;

	base.CreateCylinder(baseRadius, baseHeight, 20);
	base.SetColor(6);
	base.set(baseRadius, baseHeight, 20);
	column.CreateCuboid(columnSizeZ, columnSizeY, columnSizeZ);
	column.SetColor(1);
	column.set(columnSizeZ, columnSizeY, columnSizeZ);

	giado1.set(giado1_holecuboidthick, giado1_cuboidSizeX, giado1_cuboidSizeY, giado1_cuboidSizeZ, giado1_holecuboidSizeX, giado1_holecuboidSizeY, giado1_holecuboidSizeZ, &column);

	giado2.set(giado1_holecuboidthick, giado1_cuboidSizeX, giado1_cuboidSizeY, giado1_cuboidSizeZ / 3, giado1_holecuboidSizeX, giado1_holecuboidSizeY, giado1_holecuboidSizeZ, &column, giado2_thanhngangX, giado2_thanhngangY, giado2_thanhngangZ);
	tayquay.set(columnSizeZ * 3, 0.15, columnSizeY / 6, columnSizeZ, &base);
	thanhtruot1.set(columnSizeZ, columnSizeY / 2, columnSizeZ, 0.15 + 0.05, 0.15, columnSizeY * 2 / 5, columnSizeZ, &base, tayquay);
	thanhtruot2.set(columnSizeZ, columnSizeY / 2, columnSizeZ, 0.15 + 0.05, 0.15, columnSizeY * 2 / 5, columnSizeZ, &base, tayquay);
	myInit();
	glutIdleFunc(myIdle);
	glutSpecialFunc(mySpecialKeyboard);
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);

	glutMainLoop();
	return 0;
}
#pragma endregion
