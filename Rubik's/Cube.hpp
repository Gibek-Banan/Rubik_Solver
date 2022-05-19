#ifndef CUBE_HPP
#define CUBE_HPP
#include <iostream>
#include <map>
#include "rubik.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

enum corner
{
	urf,
	ubr,
	dlf,
	dfr,
	ulb,
	ufl,
	drb,
	dbl
};
enum edge
{
	uf,
	ur,
	ub,
	ul,
	df,
	dr,
	db,
	dl,
	fr,
	br,
	bl,
	fl
};
enum notation
{
	U,
	F,
	R,
	D,
	B,
	L
};

class Cube
{
private:
	char cornerFace(corner c, int offset);
	char edgeFace(edge e, int offset);

public:
	corner cPos[8] = {urf, ubr, dlf, dfr, ulb, ufl, drb, dbl};
	char cOri[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	edge ePos[12] = {uf, ur, ub, ul, df, dr, db, dl, fr, br, bl, fl};
	char eOri[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	string cornerNames[8] = {"URF", "UBR", "DLF", "DFR", "ULB", "UFL", "DRB", "DBL"};
	string edgeNames[12] = {"UF", "UR", "UB", "UL", "DF", "DR", "DB", "DL", "FR", "BR", "BL", "FL"};
	string colorTabEncode = "UFRDBL";
	string walls[6] = {"         ", "         ", "         ", "         ", "         ", "         "};
	char color[54];
	string path;
	Cube();
	Cube(const Cube& a);
	~Cube()=default;
	Cube &operator=(const Cube &a);
	bool operator==(const Cube &a);
	void rotCube(char c, int num);
	void rotUp(int);
	void rotDown(int);
	void rotLeft(int);
	void rotRight(int);
	void rotFront(int);
	void rotBack(int);
	void getColor();

	void getPosOri();
	void getPosOri_e();
	void getPosOri_c();
	void wallsToColor();
	void colorToWalls();
	void show(bool fix = true);
	void fixWalls();
	void fixRead();
	void readFromFile(const std::string &path);
	void convertColorsToNotation();
	void rotateR(std::string &wall);
	void rotateL(std::string &wall);
	void offset(std::string &s);
	void animation();
};

#endif