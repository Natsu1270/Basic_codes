//Title:Assignment2-ComputerGraphic
//Bui Duy Hung-1511333

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>										
#include <stdlib.h>
#include <GL/glut.h>

#define PI			3.1415926
#define	COLORNUM		14
#define DEG2RAD 3.1415926/180

using namespace std;


#pragma region Tga.h
typedef	struct
{
	GLubyte	* imageData;
	GLuint	bpp;
	GLuint	width;
	GLuint	height;
	GLuint	texID;
	GLuint	type;
} Texture;

typedef struct
{
	GLubyte Header[12];
} TGAHeader;

typedef struct
{
	GLubyte		header[6];
	GLuint		bytesPerPixel;
	GLuint		imageSize;
	GLuint		temp;
	GLuint		type;
	GLuint		Height;
	GLuint		Width;
	GLuint		Bpp;
} TGA;

TGAHeader tgaheader;
TGA tga;

GLubyte uTGAcompare[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


bool LoadTGA(Texture * texture, char * filename)
{
	FILE * fTGA;
	fTGA = fopen(filename, "rb");
	if (fTGA == NULL)
	{
		return false;
	}
	if (fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)
	{
		if (fTGA != NULL)
		{
			fclose(fTGA);
		}
		return false;
	}

	if (fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)
	{
		if (fTGA != NULL)
		{
			fclose(fTGA);
		}
		return false;
	}
	texture->width = tga.header[1] * 256 + tga.header[0];
	texture->height = tga.header[3] * 256 + tga.header[2];
	texture->bpp = tga.header[4];
	tga.Width = texture->width;
	tga.Height = texture->height;
	tga.Bpp = texture->bpp;

	if ((texture->width <= 0) || (texture->height <= 0) || ((texture->bpp != 24) && (texture->bpp != 32)))
	{
		if (fTGA != NULL)
		{
			fclose(fTGA);													// If so, close it
		}
		return false;														// Return failed
	}
	if (texture->bpp == 24)													// If the BPP of the image is 24...
		texture->type = GL_RGB;											// Set Image type to GL_RGB
	else																	// Else if its 32 BPP
		texture->type = GL_RGBA;											// Set image type to GL_RGBA
	tga.bytesPerPixel = (tga.Bpp / 8);									// Compute the number of BYTES per pixel
	tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute the total amout ofmemory needed to store data
	texture->imageData = (GLubyte *)malloc(tga.imageSize);					// Allocate that much memory

	if (texture->imageData == NULL)											// If no space was allocated
	{
		fclose(fTGA);														// Close the file
		return false;														// Return failed
	}
	if (fread(texture->imageData, 1, tga.imageSize, fTGA) != tga.imageSize)	// Attempt to read image data
	{
		if (texture->imageData != NULL)										// If imagedata has data in it
		{
			free(texture->imageData);										// Delete data from memory
		}
		fclose(fTGA);														// Close file
		return false;														// Return failed
	}

	// switch R and B
	for (int i = 0; i < tga.imageSize; i += tga.bytesPerPixel)
	{
		GLubyte temp = texture->imageData[i];
		texture->imageData[i] = texture->imageData[i + 2];
		texture->imageData[i + 2] = temp;
	}
	fclose(fTGA);															// Close file
	return true;															// All went well, continue on
}

#pragma endregion

#pragma region SupportClass.h

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
	void draw()		{
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
	void draw(){
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int  getWidth(){ return (r - l); }
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
	float  getWidth(){ return (r - l); }
	float  getHeight() { return (t - b); }
	void RealRect::draw(){
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

#pragma region Mesh.h

class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	Vector3		facenorm;

	Face()
	{
		nVerts = 0;
		vert = NULL;
		facenorm = Vector3();
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
	Point3*		pt;

	float		slideX, slideY, slideZ;
	float		rotateX, rotateY, rotateZ;
	float		scaleX, scaleY, scaleZ;

	int		numFaces;
	Face*		face;
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
	void drawFace(int numVerts, int arr_index[], Face &face);
	void drawRec(int index1, int index2, int index3, int index4, Face &face);
	Vector3 CalculateFacesNorm(Face &face);
	void Draw();
	void SetColor(int colorIndex);
	void DrawWireframe();
	void DrawColor();
	void CreateCube(float	fSize);
	void CreateOval(float fsizeX, float fsizeY, float fsizeZ, float deg);
	void CreateOoval(float fsizeX, float fsizeY, float fsizeZ, float deg, float thickness);
	void CreateCuboid(float	fSizeX, float fSizeY, float	fSizeZ);
	void CreateOCuboid(float fSizeX, float fSizeY, float fSizeZ, float thickness);
	void CreateCylinder(float	radius, float height, float degree);

};

#pragma endregion

#pragma region SupportClass.cpp

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

#pragma region Mesh.cpp


float	ColorArr[COLORNUM][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 },
{ 1.0, 1.0, 0.0 }, { 1.0, 0.0, 1.0 }, { 0.0, 1.0, 1.0 },
{ 0.3, 0.3, 0.3 }, { 0.5, 0.5, 0.5 }, { 0.9, 0.9, 0.9 },
{ 1.0, 0.5, 0.5 }, { 0.5, 1.0, 0.5 }, { 0.5, 0.5, 1.0 },
{ 0.0, 0.0, 0.0 }, { 0.75, 0.75, 0.75 } };

//ok
void Mesh::drawFace(int numVerts, int arr_index[], Face &face) {
	face.nVerts = numVerts;
	face.vert = new VertexID[face.nVerts];
	for (int i = 0; i < numVerts; i++) {
		face.vert[i].vertIndex = arr_index[i];
	}
	for (int i = 0; i<face.nVerts; i++)
		face.vert[i].colorIndex = i;
}

void Mesh::drawRec(int index1, int index2, int index3, int index4, Face &face) {
	int arr[4] = { index1, index2, index3, index4 };
	drawFace(4, arr, face);
}

void Mesh::CreateCube(float	fSize)
{
	int i;
	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
	for (int i = 0; i < numFaces; i++) {
		CalculateFacesNorm(face[i]);
	}
}

void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ) {
	int i;
	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX / 2, fSizeY / 2, -fSizeZ / 2);
	pt[1].set(fSizeX / 2, fSizeY / 2, -fSizeZ / 2);
	pt[2].set(fSizeX / 2, fSizeY / 2, fSizeZ / 2);
	pt[3].set(-fSizeX / 2, fSizeY / 2, fSizeZ / 2);
	pt[4].set(-fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
	pt[5].set(fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
	pt[6].set(fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
	pt[7].set(-fSizeX / 2, -fSizeY / 2, fSizeZ / 2);

	numFaces = 6;
	face = new Face[numFaces];
	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 4;
	face[0].vert[2].vertIndex = 7;
	face[0].vert[3].vertIndex = 3;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 2;
	face[1].vert[1].vertIndex = 6;
	face[1].vert[2].vertIndex = 5;
	face[1].vert[3].vertIndex = 1;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 1;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 4;
	face[3].vert[1].vertIndex = 5;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 7;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 3;
	face[4].vert[1].vertIndex = 7;
	face[4].vert[2].vertIndex = 6;
	face[4].vert[3].vertIndex = 2;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 1;
	face[5].vert[1].vertIndex = 5;
	face[5].vert[2].vertIndex = 4;
	face[5].vert[3].vertIndex = 0;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	for (int i = 0; i < numFaces; i++) {
		CalculateFacesNorm(face[i]);
	}

}

void Mesh::CreateOCuboid(float fSizeX, float fSizeY, float fSizeZ, float t) {
	int i;
	numVerts = 16;
	pt = new Point3[16];
	pt[0].set(-fSizeX / 2, fSizeY / 2, -fSizeZ / 2);
	pt[1].set(fSizeX / 2, fSizeY / 2, -fSizeZ / 2);
	pt[2].set(fSizeX / 2, fSizeY / 2, fSizeZ / 2);
	pt[3].set(-fSizeX / 2, fSizeY / 2, fSizeZ / 2);
	pt[4].set(-fSizeX / 2 - t, fSizeY / 2, -fSizeZ / 2 - t);
	pt[5].set(fSizeX / 2 + t, fSizeY / 2, -fSizeZ / 2 - t);
	pt[6].set(fSizeX / 2 + t, fSizeY / 2, fSizeZ / 2 + t);
	pt[7].set(-fSizeX / 2 - t, fSizeY / 2, fSizeZ / 2 + t);

	pt[8].set(-fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
	pt[9].set(fSizeX / 2, -fSizeY / 2, -fSizeZ / 2);
	pt[10].set(fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
	pt[11].set(-fSizeX / 2, -fSizeY / 2, fSizeZ / 2);
	pt[12].set(-fSizeX / 2 - t, -fSizeY / 2, -fSizeZ / 2 - t);
	pt[13].set(fSizeX / 2 + t, -fSizeY / 2, -fSizeZ / 2 - t);
	pt[14].set(fSizeX / 2 + t, -fSizeY / 2, fSizeZ / 2 + t);
	pt[15].set(-fSizeX / 2 - t, -fSizeY / 2, fSizeZ / 2 + t);

	numFaces = 16;
	face = new Face[numFaces];

	int arr_index[16][4] = { { 0, 4, 7, 3 },//ben trai phia tren
	{ 0, 1, 5, 4 },//o xa phia tren 
	{ 2, 6, 5, 1 },//ben phai phia tren
	{ 3, 7, 6, 2 },//o gan phia tren 
	{ 8, 11, 15, 12 },//ben trai o duoi
	{ 8, 12, 13, 9 },// o xa od uoi
	{ 10, 9, 13, 14 },//ben phai o duoi
	{ 11, 10, 14, 15 },//o gan o duoi
	{ 3, 11, 8, 0 },//ben trai o trong
	{ 0, 8, 9, 1 },//o xa o trong
	{ 2, 1, 9, 10 },//ben phai o trong
	{ 3, 2, 10, 11 },//o gan o trong
	{ 7, 4, 12, 15 },//ben trai o ngoai
	{ 4, 5, 13, 12 },//o xa o ngoai
	{ 6, 14, 13, 5 },//ben phai o ngoai
	{ 7, 15, 14, 6 } };//truoc mat				//outer faces

	for (int i = 0; i < numFaces; i++) {
		drawFace(4, arr_index[i], face[i]);
	}

}

void Mesh::CreateCylinder(float deg, float radius, float height) {
	int i;
	numVerts = 360.0f / deg * 2 + 2;
	pt = new Point3[numVerts];
	pt[0].set(0, height / 2, 0);
	pt[numVerts / 2].set(0, -height / 2, 0);
	int ncircle = 360.0f / deg;
	for (int i = 1; i <= ncircle; i++) {
		pt[i].set(radius*sin(DEG2RAD * deg * i), height / 2, radius*cos(DEG2RAD * deg * i));
		pt[i + ncircle + 1].set(radius*sin(DEG2RAD * deg * i), -height / 2, radius*cos(DEG2RAD * deg * i));
	}
	numFaces = (numVerts - 2) / 2 * 3;
	face = new Face[numFaces];

	for (int i = 1; i < numVerts / 2; i++) {
		int arr1[3] = { 0, i, i%ncircle + 1 };
		int arr2[3] = { ncircle + 1, i % ncircle + ncircle + 2, i + ncircle + 1 }; //int arr2[3] = { num_circle + 1,i + num_circle + 1,i % num_circle + 22 };
		drawFace(3, arr1, face[i - 1]);
		drawFace(3, arr2, face[i + ncircle - 1]);
	}
	for (int i = 1; i < numVerts / 2; i++) {
		int arr[4] = { i%ncircle + 1, i, i + ncircle + 1, i % ncircle + ncircle + 2 };
		drawFace(4, arr, face[i + ncircle * 2 - 1]);
	}
	for (int i = 0; i < numFaces; i++) {
		CalculateFacesNorm(face[i]);
	}
}

void Mesh::CreateOval(float fsizeX, float fsizeY, float fsizeZ, float deg) {
	float radius = fsizeZ / 2.0;
	float halfLen = fsizeX / 2.0;
	float halfHeight = fsizeY / 2.0;

	int nPslice = 360.0 / deg + 2;
	numVerts = (360.0 / deg + 2) * 2;
	int nhaftC = 180 / deg + 1;
	pt = new Point3[numVerts];


	for (int i = 0; i < nhaftC; i++) {
		pt[i].set(-halfLen - radius * cos(DEG2RAD * (i * deg - 90)), -halfHeight, radius * sin(DEG2RAD * (i * deg - 90))); //ben duoi o xa ben trai
		pt[i + nhaftC].set(halfLen + radius * cos(DEG2RAD * (i * deg - 90)), -halfHeight, radius * sin(DEG2RAD*(90 - i*deg)));//)));//ben duoi o gan ben phai
		pt[i + nhaftC * 2].set(-halfLen - radius * cos(DEG2RAD * (i * deg - 90)), halfHeight, radius * sin(DEG2RAD * (i * deg - 90)));// ben tren o xa ben trai
		pt[i + nhaftC * 3].set(halfLen + radius * cos(DEG2RAD * (i * deg - 90)), halfHeight, radius * sin(DEG2RAD * (90 - i*deg)));//ben tren o gan ben phai
	}

	numFaces = 2 + nhaftC * 2;
	face = new Face[numFaces];
	int counter = 0;
	//mat ben
	for (int j = 0; j < nPslice; j++) {
		int arr[4] = { j, (j + 1) % nPslice, (j + 1) % nPslice + nPslice, j + nPslice };
		drawFace(4, arr, face[counter++]);
	}
	int* arr_point = new int[nPslice];// use to draw top and bottom
	// bottom face counter clockwise from top look down should reverse
	for (int i = 0; i < nPslice; i++) {
		arr_point[i] = nPslice - 1 - i;
	}
	drawFace(nPslice, arr_point, face[counter++]);

	for (int i = 0; i < nPslice; i++) {
		arr_point[i] = i + nPslice;
	}
	drawFace(nPslice, arr_point, face[counter++]);

	for (int i = 0; i < numFaces; i++) {
		CalculateFacesNorm(face[i]);
	}
}

void Mesh::CreateOoval(float fsizeX, float fsizeY, float fsizeZ, float deg, float thickness) {
	int i;
	numVerts = (360 / deg + 2) * 4;
	int numVerts_circle = 180 / deg + 1;
	pt = new Point3[numVerts];
	float inR = fsizeZ / 2;
	float outR = inR + thickness;
	float halfLen = fsizeX / 2;
	float halfHeight = fsizeY / 2;
	int offTB = numVerts_circle * 4;
	int offIO = numVerts_circle * 2;
	int offFN = numVerts_circle;
	//top inner left half circle
	for (int i = 0; i < numVerts_circle; i++) {
		pt[i].set(-halfLen - inR * cos(DEG2RAD * (i * deg - 90)), halfHeight, inR * sin(DEG2RAD * (i * deg - 90)));//phia tren o xa o trong
		pt[i + numVerts_circle].set(halfLen + inR * cos(DEG2RAD * (i * deg - 90)), halfHeight, inR * sin(DEG2RAD * (90 - i*deg)));// phia tren o gan o trong
		pt[i + numVerts_circle * 2].set(-halfLen - outR * cos(DEG2RAD * (i * deg - 90)), halfHeight, outR * sin(DEG2RAD * (i * deg - 90)));//phia tren o xa ben trai o ngoai
		pt[i + numVerts_circle * 3].set(halfLen + outR * cos(DEG2RAD * (i * deg - 90)), halfHeight, outR * sin(DEG2RAD * (90 - i * deg)));// phia tren o gan ben phai o ngoai
		pt[i + numVerts_circle * 4].set(-halfLen - inR * cos(DEG2RAD * (i * deg - 90)), -halfHeight, inR * sin(DEG2RAD * (i * deg - 90)));//phia duoi o xa o trong
		pt[i + numVerts_circle * 5].set(halfLen + inR * cos(DEG2RAD * (i * deg - 90)), -halfHeight, inR * sin(DEG2RAD * (90 - i * deg)));// phia duoi o gan o trong
		pt[i + numVerts_circle * 6].set(-halfLen - outR * cos(DEG2RAD * (i * deg - 90)), -halfHeight, outR * sin(DEG2RAD * (i * deg - 90)));//phia duoi o xa o ngoai
		pt[i + numVerts_circle * 7].set(halfLen + outR * cos(DEG2RAD * (i * deg - 90)), -halfHeight, outR * sin(DEG2RAD * (90 - i * deg)));// phia duoi o gan o ngoai
	}
	numFaces = (numVerts_circle - 1) * 8 + 8;
	face = new Face[numFaces];
	int counter = 0;
	//circle
	for (int i = 0; i < numVerts_circle - 1; i++) {
		int arr_top_far[4] = { i, i + offIO, i + offIO + 1, i + 1 };
		int arr_top_near[4] = { i + offFN, i + offFN + offIO, i + offFN + offIO + 1, i + offFN + 1 };
		int arr_bottom_far[4] = { i + offTB, i + offTB + 1, i + offTB + offIO + 1, i + offTB + offIO };
		int arr_bottom_near[4] = { i + offTB + offFN, i + offTB + offFN + 1, i + offTB + offIO + offFN + 1, i + offTB + offIO + offFN };
		int arr_side_far_outer[4] = { i + offIO, i + offIO + offTB, i + offIO + offTB + 1, i + offIO + 1 };
		int arr_side_near_outer[4] = { i + offIO + offFN, i + offIO + offTB + offFN, i + offIO + offTB + offFN + 1, i + offIO + offFN + 1 };
		int arr_inner_far[4] = { i, i + 1, i + offTB + 1, i + offTB };
		int arr_inner_near[4] = { i + offFN, i + offFN + 1, i + offFN + offTB + 1, i + offFN + offTB };
		drawFace(4, arr_top_far, face[counter++]);
		drawFace(4, arr_top_near, face[counter++]);
		drawFace(4, arr_bottom_far, face[counter++]);
		drawFace(4, arr_bottom_near, face[counter++]);
		drawFace(4, arr_side_far_outer, face[counter++]);
		drawFace(4, arr_side_near_outer, face[counter++]);
		drawFace(4, arr_inner_far, face[counter++]);
		drawFace(4, arr_inner_near, face[counter++]);
	}
	int offFL = numVerts_circle - 1;
	int* arr_pointer;
	int arr_left_inner[4] = { offFL, offFN, offFN + offTB, offTB + offFL };
	int arr_left_outer[4] = { offFL + offIO, offFL + offIO + offTB, offFN + offIO + offTB, offFN + offIO };
	int arr_top_left[4] = { offFL, offFL + offIO, offIO + offFN, offFN };
	int arr_bottom_left[4] = { offFL, offFL + offIO, offFN + offIO, offFN };
	int arr_right_inner[4] = { 0, offTB, offTB + offFN + offFL, offFN + offFL };
	int arr_right_outer[4] = { offIO, offIO + offFN + offFL, offIO + offTB + offFN + offFL, +offTB + offIO };
	int arr_top_right[4] = { 0, offFN + offFL, offFN + offFL + offIO, offIO };
	int arr_bottom_right[4] = { offTB, offIO + offTB, offTB + offFN + offFL + offIO, offTB + offFN + offFL };
	drawFace(4, arr_left_inner, face[counter++]);
	drawFace(4, arr_left_outer, face[counter++]);
	drawFace(4, arr_top_left, face[counter++]);
	drawFace(4, arr_bottom_left, face[counter++]);
	drawFace(4, arr_right_inner, face[counter++]);
	drawFace(4, arr_right_outer, face[counter++]);
	drawFace(4, arr_top_right, face[counter++]);
	drawFace(4, arr_bottom_right, face[counter++]);
	for (int i = 0; i < numFaces; i++) {
		CalculateFacesNorm(face[i]);
	}
}

void Mesh::Draw() {
	for (int f = 0; f < numFaces; f++){
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++){
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

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
Vector3 Mesh::CalculateFacesNorm(Face &face) {
	face.facenorm.set(0, 0, 0);
	Point3* current;
	Point3* next;
	int cur, ne, a;
	for (int i = 0; i < face.nVerts; i++) {
		current = &pt[face.vert[i].vertIndex];
		next = &pt[face.vert[(i + 1) % face.nVerts].vertIndex];
		cur = face.vert[i].vertIndex;
		ne = face.vert[(i + 1) % face.nVerts].vertIndex;
		face.facenorm.x = face.facenorm.x + (current->y - next->y) * (current->z + next->z);
		face.facenorm.y = face.facenorm.y + (current->z - next->z) * (current->x + next->x);
		face.facenorm.z = face.facenorm.z + (current->x - next->x) * (current->y + next->y);
	}
	face.facenorm.normalize();
	return face.facenorm;
}
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

			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

#pragma endregion

#pragma region ass2.cpp


int		sWidth = 600;
int		sHeight = 600;
float    groundSize = 20;
bool	bWireFrame = false;

float	baseRadius = 0.8;
float	baseHeight = 0.2;
float	baseRotateStep = 5;

float	columnSizeX = 0.25;
float	columnSizeZ = columnSizeX;
float	columnSizeY = 5;
float	cam_angle;
float	cam_height;
float	cam_dis;
float	cam_X, cam_Y, cam_Z;
float	lookAt_X, lookAt_Y, lookAt_Z;
bool	light1 = true;
//bool	b4View = false;
bool	motion = false;
//float	cuboidthickness = 0.25;
Mesh	cbase;
Mesh	ccolumn;
Mesh	cholder1_solid;
Mesh	cholder1_holed;
Mesh	cslider1_handle;
Mesh	cslider1_oval;
Mesh	cholder2_solid;
Mesh	cholder2_holed;
Mesh	cholder2_handle;
Mesh	cslider2_handle;
Mesh	cslider2_oval;
Mesh	ccrank_handle;
Mesh	ccrank;
Mesh ccube;
Texture   floorTex;

GLfloat shade_ground[] = { 0.0f, 1.0f, 0.0f, 0.0f };
GLfloat qaLight0Pos[] = { 5, 7, 7, 1.0 };
GLfloat qaLight1Pos[] = { -5, 7, -3, 1.0 };


void shadeMx(float sg[], float light[])
{
	float a[16];
	const float k = sg[0] * light[0] + sg[1] * light[1]
		+ sg[2] * light[2] + sg[3] * light[3];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			a[4 * i + j] = -sg[i] * light[j];
		}
		a[5 * i] += k;
	}
	glMultMatrixf(a);
}

void loadTextures(void) {
	bool status = LoadTGA(&floorTex, "MARBLE.tga");
	if (status) {
		glGenTextures(1, &floorTex.texID);
		glBindTexture(GL_TEXTURE_2D, floorTex.texID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, floorTex.width,
			floorTex.height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, floorTex.imageData);

		if (floorTex.imageData)
			free(floorTex.imageData);
	}
}

void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shiness);
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		cbase.rotateY += baseRotateStep;
		if (cbase.rotateY > 360)
			cbase.rotateY -= 360;
		break;
	case '2':
		cbase.rotateY -= baseRotateStep;
		if (cbase.rotateY < 0)
			cbase.rotateY += 360;
		break;
	case '3':
		ccrank.rotateY += baseRotateStep;
		if (ccrank.rotateY > 360)
			ccrank.rotateY -= 360;
		break;
	case '4':
		ccrank.rotateY -= baseRotateStep;
		if (ccrank.rotateY < 0)
			ccrank.rotateY += 360;
		break;
	case 'R': case 'r':
		ccrank.rotateY = 0;
		cbase.rotateY = 0;
		break;
	case 'w':case'W':
		bWireFrame = !bWireFrame;
	case '+':
		cam_dis += 0.1;
		break;
	case '-':
		cam_dis -= 0.1;
		break;
		//case 'v':case'V':
		//	b4View = !b4View;
		//	break;
	case 'd': case'D':
		light1 = !light1;
		break;
	case 'a': case 'A':
		motion = !motion;
		break;
	}

	glutPostRedisplay();
}
void mySpecialKeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		cam_angle -= 1;
		break;
	case GLUT_KEY_RIGHT:
		cam_angle += 1;
		break;
	case GLUT_KEY_UP:
		cam_height += 0.1;
		break;
	case GLUT_KEY_DOWN:
		cam_height -= 0.1;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}



void drawBase()
{
	glPushMatrix();

	glTranslated(0, baseHeight / 2.0, 0);
	glRotatef(cbase.rotateY, 0, 1, 0);

	GLfloat	baseDiffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat	baseSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat	baseAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	setupMaterial(baseAmbient, baseDiffuse, baseSpecular, 90);
	if (bWireFrame)
		cbase.DrawWireframe();
	else {
		//base.DrawColor();
		cbase.Draw();
	}
	glPopMatrix();
}
void drawColumn()
{
	glPushMatrix();

	glTranslated(0, baseHeight / 2.0 + columnSizeY / 2, 0);
	glRotatef(cbase.rotateY, 0, 1, 0);
	GLfloat	columnDiffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat	columnSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat	columnAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	setupMaterial(columnAmbient, columnDiffuse, columnSpecular, 90);
	if (bWireFrame)
		ccolumn.DrawWireframe();
	else {
		//column.DrawColor();
		ccolumn.Draw();
	}
	glPopMatrix();
}

void drawHolder1()
{
	glPushMatrix();

	glTranslated(0, baseHeight / 2.0 + 3.25, 0);
	glRotatef(cbase.rotateY, 0, 1, 0);
	glTranslated(0, 0, columnSizeX*1.25);

	GLfloat	diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat	specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat	ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	setupMaterial(ambient, diffuse, specular, 90);
	if (bWireFrame) {
		cholder1_solid.DrawWireframe();
		glTranslatef(0, 0, columnSizeX*1.5);
		cholder1_holed.DrawWireframe();
	}
	else {
		cholder1_solid.Draw();
		glTranslatef(0, 0, columnSizeX*1.5);
		cholder1_holed.Draw();
	}

	glPopMatrix();
}

void drawHolder2()
{
	glPushMatrix();

	glTranslated(0, baseHeight / 2.0 + 1.5, 0);
	glRotatef(cbase.rotateY, 0, 1, 0);
	glTranslated(columnSizeX*6.5, 0, 0);

	GLfloat	diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat	specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat	ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	setupMaterial(ambient, diffuse, specular, 90);

	if (bWireFrame) {
		cholder2_handle.DrawWireframe();
		glTranslatef(0, 0, columnSizeZ*0.75);
		cholder2_solid.DrawWireframe();
		glTranslatef(0, 0, columnSizeZ);
		glRotatef(90, 0, 0, 1);
		cholder2_holed.DrawWireframe();
	}
	else {
		cholder2_handle.Draw();
		glTranslatef(0, 0, columnSizeZ*0.75);//0,0,0.1825
		cholder2_solid.Draw();
		glTranslatef(0, 0, columnSizeZ);
		glRotatef(90, 0, 0, 1);
		cholder2_holed.Draw();
	}

	glPopMatrix();
}

void drawSlider1()
{
	glPushMatrix();

	glTranslated(0, baseHeight / 2.0 + 3.5, 0);
	glRotatef(cbase.rotateY, 0, 1, 0);
	glTranslatef(0, +3.75 * columnSizeZ*cos(DEG2RAD*ccrank.rotateY), 0);
	glTranslated(0, columnSizeY*0.1 + -3.75 * columnSizeZ, columnSizeZ*2.75);

	GLfloat	diffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat	specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat	ambient[] = { 0.05f, 0.05f, 0.05f, 1.0f };
	setupMaterial(ambient, diffuse, specular, 90);

	if (bWireFrame) {
		cslider1_handle.DrawWireframe();
		glTranslatef(0, -columnSizeY*0.55 / 2 - columnSizeZ / 2 - columnSizeZ / 4, 0);
		glRotatef(90, 1, 0, 0);
		cslider1_oval.DrawWireframe();
	}
	else {
		cslider1_handle.Draw();
		glTranslatef(0, -columnSizeY*0.55 / 2 - columnSizeZ / 2 - columnSizeZ / 4, 0);
		glRotatef(90, 1, 0, 0);
		cslider1_oval.Draw();
	}

	glPopMatrix();
}

void drawSlider2()
{
	glPushMatrix();
	glTranslated(0, baseHeight / 2.0 + 1.5, 0);
	glRotatef(cbase.rotateY, 0, 1, 0);
	glTranslated(columnSizeX*6.5 - 3.75*columnSizeZ*sin(DEG2RAD*ccrank.rotateY), 0, columnSizeZ*1.75);
	glRotatef(90, 0, 0, 1);
	glTranslated(0, +columnSizeY*0.025, 0);


	GLfloat	diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat	specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat	ambient[] = { 0.0f, 0.1f, 0.1f, 1.0f };

	setupMaterial(ambient, diffuse, specular, 90);

	if (bWireFrame) {
		cslider2_handle.DrawWireframe();
		glTranslatef(0, columnSizeY*0.55 / 2 + columnSizeZ / 2, 0);
		glRotatef(90, 1, 0, 0);
		cslider2_oval.DrawWireframe();
	}
	else {
		cslider2_handle.Draw();
		glTranslatef(0, columnSizeY*0.55 / 2 + columnSizeZ / 2, 0);
		glRotatef(90, 1, 0, 0);
		cslider2_oval.Draw();
	}

	glPopMatrix();
}

void drawCrank() {
	glPushMatrix();
	glTranslated(0, baseHeight / 2.0 + 1.5, 0);
	glRotatef(cbase.rotateY, 0, 1, 0);
	glTranslated(0, 0, columnSizeZ*0.875);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glRotatef(ccrank.rotateY, 0, 1, 0);
	glTranslatef(columnSizeX * 2, 0, 0);



	if (bWireFrame) {
		GLfloat	diffuseHandle[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		GLfloat	specularHandle[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat	ambientHandle[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		setupMaterial(ambientHandle, diffuseHandle, specularHandle, 90);
		ccrank_handle.DrawWireframe();
		glTranslatef(columnSizeX * 1.7, columnSizeX * 1.625, 0);

		GLfloat	diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		GLfloat	specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat	ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		setupMaterial(ambient, diffuse, specular, 90);
		ccrank.DrawWireframe();
	}
	else {
		GLfloat	diffuseHandle[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		GLfloat	specularHandle[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat	ambientHandle[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		setupMaterial(ambientHandle, diffuseHandle, specularHandle, 90);

		ccrank_handle.Draw();
		glTranslatef(columnSizeX * 1.75, columnSizeX*1.625, 0);

		GLfloat	diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		GLfloat	specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat	ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		setupMaterial(ambient, diffuse, specular, 90);
		ccrank.Draw();
	}

	glPopMatrix();
}

void drawContra() {
	//drawAxis();
	drawBase();
	drawColumn();
	drawHolder1();
	drawHolder2();
	drawSlider1();
	drawSlider2();
	drawCrank();
}

void shadeContra(GLfloat pos[]) {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	shadeMx(shade_ground, pos);
	drawContra();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}
void lightSetting() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	GLfloat qaAmbientLight0[] = { 1, 1, 1, 1.0 };
	GLfloat qaDiffuseLight0[] = { 1, 1, 1, 1.0 };
	GLfloat qaSpecularLight0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight0);
	//GLfloat qaLight0Position[] = { 5, 7, 7, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLight0Pos);
	if (light1) {
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight0);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight0);
		glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight0);
		//GLfloat qaLight1Position[] = { -5, 7, -3, 1.0 };
		glLightfv(GL_LIGHT1, GL_POSITION, qaLight1Pos);
		glColor3f(0.2, 0.2, 0.2);
		shadeContra(qaLight1Pos);
	}
	else {
		glDisable(GL_LIGHT1);
	}
}

void groundContra(){
	loadTextures();
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(cam_X, cam_Y, cam_Z, 0, 1, 0, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floorTex.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-groundSize, -0.01, -groundSize);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(groundSize, -0.01, -groundSize);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(groundSize, -0.01, groundSize);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-groundSize, -0.01, groundSize);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void reflexContra(){
	glColorMask(0, 0, 0, 0);
	glDisable(GL_DEPTH_TEST);
	groundContra();
	glColorMask(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(cam_X, cam_Y, cam_Z, 0, 1, 0, 0, 1, 0);

	glScalef(1, -1, 1);
	drawContra();
	glPopMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 0.85);
	groundContra();
	glDisable(GL_BLEND);
	glPopMatrix();
}
void myDisplay()
{
	float	fHalfSize = 4;
	cam_X = cam_dis*sin(DEG2RAD*(cam_angle));
	cam_Y = cam_height;
	cam_Z = cam_dis*cos(DEG2RAD*(cam_angle));

	glClearDepth(1.0f);
	glClearColor(1.0, 1.0, 1.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //clear the buffers

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, sWidth, sHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, 1, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	gluLookAt(cam_X, cam_Y, cam_Z, 0, 1, 0, 0, 1, 0);
	lightSetting();
	glColor3f(0.2, 0.2, 0.2);
	shadeContra(qaLight0Pos);
	drawContra();
	glPopMatrix();

	reflexContra();

	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;
	cam_angle = 10;
	cam_height = 3;
	cam_dis = 6;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
	loadTextures();
}
void OnTimer(int value)
{
	if (motion) {
		cbase.rotateY += 1;
		ccrank.rotateY += 1;
	}

	glutTimerFunc(100, OnTimer, value);
	glutPostRedisplay();
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "1, 2: Rotate the base \n";
	cout << "3, 4: Rotate the arm \n";
	cout << "R, r: Reset";
	cout << "W, w: Switch between wire frame and solid mode \n";
	cout << "D, d: Switch off 1 light\n";
	cout << "A, a: Start/stop animation\n";
	cout << "+   : to increase camera distance.\n";
	cout << "-   : to decrease camera distance.\n";
	cout << "up arrow	: to increase camera height.\n";
	cout << "down arrow	: to decrease camera height.\n";
	cout << "<-		: to rotate camera clockwise.\n";
	cout << "->		: to rotate camera counterclockwise.\n";

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(sWidth, sHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Assignment 2- Bui Duy Hung (1511333)"); // open the screen window

	cbase.CreateCylinder(20, baseRadius, baseHeight);

	ccolumn.CreateCuboid(columnSizeX, columnSizeY, columnSizeZ);

	cholder1_solid.CreateCuboid(columnSizeX, baseHeight*1.25, columnSizeZ*1.5);
	cholder1_holed.CreateOCuboid(columnSizeX, baseHeight*1.75, columnSizeZ, columnSizeX / 4);

	cholder2_handle.CreateCuboid(columnSizeX * 12, baseHeight, columnSizeZ);
	cholder2_solid.CreateCuboid(columnSizeX, baseHeight, columnSizeZ / 2);
	cholder2_holed.CreateOCuboid(columnSizeX, baseHeight*1.75, columnSizeZ, columnSizeX / 4);

	cslider1_handle.CreateCuboid(columnSizeX, columnSizeY*0.55, columnSizeZ);
	cslider1_oval.CreateOoval(columnSizeX*8.5, columnSizeX, columnSizeZ, 10, columnSizeZ / 2);

	cslider2_handle.CreateCuboid(columnSizeX, columnSizeY*0.55, columnSizeZ);
	cslider2_oval.CreateOoval(columnSizeX*8.5, columnSizeX, columnSizeZ, 10, columnSizeZ * 3 / 6);


	ccrank_handle.CreateOval(columnSizeX * 4, columnSizeX*0.75, columnSizeZ, 10);
	ccrank.CreateCylinder(10, columnSizeZ / 2, columnSizeX*2.5);
	ccube.CreateCube(2);
	myInit();

	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialKeyboard);
	glutTimerFunc(100, OnTimer, 100);
	//glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}

#pragma endregion