#include "Cube.hpp"

Cube::Cube(){
	path = "";
	for (char c = 0; c < 6; c++)
		for (int i = 0; i < 9; i++)
			color[c * 9 + i] = colorTabEncode[c];
	colorToWalls();

	
}

Cube& Cube::operator=(const Cube& a){
	for (int i = 0; i < 8; i++){
		cPos[i] = a.cPos[i];
		cOri[i] = a.cOri[i];
	}
	for (int i = 0; i < 12; i++){
		ePos[i] = a.ePos[i];
		eOri[i] = a.eOri[i];
	}
	path = a.path;
	return *this;
}

bool Cube::operator==(const Cube& a){
	for (int i = 0; i < 8; i++)
		if (cPos[i] != a.cPos[i] || cOri[i] != a.cOri[i])
			return 0;
	for (int i = 0; i < 12; i++)
		if (ePos[i] != a.ePos[i] || eOri[i] != a.eOri[i])
			return 0;
	return 1;
}


Cube::~Cube(){
}

void	Cube::rotCube(char c, int amount){
	switch (c){
		case 'F':
			rotFront(amount);
			break;
		case 'R':
			rotRight(amount);
			break;
		case 'U':
			rotUp(amount);
			break;
		case 'B':
			rotBack(amount);
			break;
		case 'L':
			rotLeft(amount);
			break;
		case 'D':
			rotDown(amount);
	}
	getColor();
}

void	Cube::rotUp(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[urf];
		cPos[urf] = cPos[ubr];
		cPos[ubr] = cPos[ulb];
		cPos[ulb] = cPos[ufl];
		cPos[ufl] = tmp;
		
		char tOri = cOri[urf];
		cOri[urf] = cOri[ubr];
		cOri[ubr] = cOri[ulb];
		cOri[ulb] = cOri[ufl];
		cOri[ufl] = tOri;

		tOri = eOri[ub];
		eOri[ub] = eOri[ul];
		eOri[ul] = eOri[uf];
		eOri[uf] = eOri[ur];
		eOri[ur] = tOri;

		edge tmp2 = ePos[ub];
		ePos[ub] = ePos[ul];
		ePos[ul] = ePos[uf];
		ePos[uf] = ePos[ur];
		ePos[ur] = tmp2;
	}
}
		
void	Cube::rotDown(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[dfr];
		cPos[dfr] = cPos[dlf];
		cPos[dlf] = cPos[dbl];
		cPos[dbl] = cPos[drb];
		cPos[drb] = tmp;

		char tOri = cOri[dfr];
		cOri[dfr] = cOri[dlf];
		cOri[dlf] = cOri[dbl];
		cOri[dbl] = cOri[drb];
		cOri[drb] = tOri;

		tOri = eOri[df];
		eOri[df] = eOri[dl];
		eOri[dl] = eOri[db];
		eOri[db] = eOri[dr];
		eOri[dr] = tOri;

		edge tmp2 = ePos[df];
		ePos[df] = ePos[dl];
		ePos[dl] = ePos[db];
		ePos[db] = ePos[dr];
		ePos[dr] = tmp2;
	}
}

void	Cube::rotLeft(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[dlf];
		cPos[dlf] = cPos[ufl];
		cPos[ufl] = cPos[ulb];
		cPos[ulb] = cPos[dbl];
		cPos[dbl] = tmp;

		char tOri = cOri[dlf];
		cOri[dlf] = (1 + cOri[ufl]) % 3;
		cOri[ufl] = (2 + cOri[ulb]) % 3;
		cOri[ulb] = (1 + cOri[dbl]) % 3;
		cOri[dbl] = (2 + tOri) % 3;

		tOri = eOri[bl];
		eOri[bl] = eOri[dl];
		eOri[dl] = eOri[fl];
		eOri[fl] = eOri[ul];
		eOri[ul] = tOri;

		edge tmp2 = ePos[bl];
		ePos[bl] = ePos[dl];
		ePos[dl] = ePos[fl];
		ePos[fl] = ePos[ul];
		ePos[ul] = tmp2;
	}
}

void	Cube::rotRight(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[urf];
		cPos[urf] = cPos[dfr];
		cPos[dfr] = cPos[drb];
		cPos[drb] = cPos[ubr];
		cPos[ubr] = tmp;

		char tOri = cOri[urf];
		cOri[urf] = (1 + cOri[dfr]) % 3;
		cOri[dfr] = (2 + cOri[drb]) % 3;
		cOri[drb] = (1 + cOri[ubr]) % 3;
		cOri[ubr] = (2 + tOri) % 3;

		tOri = eOri[fr];
		eOri[fr] = eOri[dr];
		eOri[dr] = eOri[br];
		eOri[br] = eOri[ur];
		eOri[ur] = tOri;

		edge tmp2 = ePos[fr];
		ePos[fr] = ePos[dr];
		ePos[dr] = ePos[br];
		ePos[br] = ePos[ur];
		ePos[ur] = tmp2;
	}
}

void	Cube::rotFront(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[urf];
		cPos[urf] = cPos[ufl];
		cPos[ufl] = cPos[dlf];
		cPos[dlf] = cPos[dfr];
		cPos[dfr] = tmp;

		char tOri = cOri[urf];
		cOri[urf] = (2 + cOri[ufl]) % 3;
		cOri[ufl] = (1 + cOri[dlf]) % 3;
		cOri[dlf] = (2 + cOri[dfr]) % 3;
		cOri[dfr] = (1 + tOri) % 3;

		tOri = eOri[uf];
		eOri[uf] = 1 - eOri[fl];
		eOri[fl] = 1 - eOri[df];
		eOri[df] = 1 - eOri[fr];
		eOri[fr] = 1 - tOri;

		edge tmp2 = ePos[uf];
		ePos[uf] = ePos[fl];
		ePos[fl] = ePos[df];
		ePos[df] = ePos[fr];
		ePos[fr] = tmp2;
	}
}

void	Cube::rotBack(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[ulb];
		cPos[ulb] = cPos[ubr];
		cPos[ubr] = cPos[drb];
		cPos[drb] = cPos[dbl];
		cPos[dbl] = tmp;

		char tOri = cOri[ulb];
		cOri[ulb] = (2 + cOri[ubr]) % 3;
		cOri[ubr] = (1 + cOri[drb]) % 3;
		cOri[drb] = (2 + cOri[dbl]) % 3;
		cOri[dbl] = (1 + tOri) % 3;

		tOri = eOri[br];
		eOri[br] = 1 - eOri[db];
		eOri[db] = 1 - eOri[bl];
		eOri[bl] = 1 - eOri[ub];
		eOri[ub] = 1 - tOri;

		edge tmp2 = ePos[br];
		ePos[br] = ePos[db];
		ePos[db] = ePos[bl];
		ePos[bl] = ePos[ub];
		ePos[ub] = tmp2;
	}
}

char	Cube::cornerFace(corner c, int offset)
{
	return (cornerNames[cPos[c]][(offset + cOri[c]) % 3]);
}

char	Cube::edgeFace(edge e, int offset)
{
	return (edgeNames[ePos[e]][(offset + eOri[e]) % 2]);
}

void	Cube::getColor()
{
	int pos = 0;
	//0-8
	color[pos++] = cornerFace(ulb, 0);
	color[pos++] = edgeFace(ub, 0);
	color[pos++] = cornerFace(ubr, 0);
	color[pos++] = edgeFace(ul, 0);
	color[pos++] = 'U';
	color[pos++] = edgeFace(ur, 0);
	color[pos++] = cornerFace(ufl, 0);
	color[pos++] = edgeFace(uf, 0);
	color[pos++] = cornerFace(urf, 0);
	//9-17
	color[pos++] = cornerFace(dlf, 2);
	color[pos++] = edgeFace(fl, 0);
	color[pos++] = cornerFace(ufl, 1);
	color[pos++] = edgeFace(df, 1);
	color[pos++] = 'F';
	color[pos++] = edgeFace(uf, 1);
	color[pos++] = cornerFace(dfr, 1);
	color[pos++] = edgeFace(fr, 0);
	color[pos++] = cornerFace(urf, 2);
	//18-26
	color[pos++] = cornerFace(drb, 1);
	color[pos++] = edgeFace(dr, 1);
	color[pos++] = cornerFace(dfr, 2);
	color[pos++] = edgeFace(br, 1);
	color[pos++] = 'R';	
	color[pos++] = edgeFace(fr, 1);
	color[pos++] = cornerFace(ubr, 2);
	color[pos++] = edgeFace(ur, 1);
	color[pos++] = cornerFace(urf, 1);
	//27-35
	color[pos++] = cornerFace(dbl, 0);
	color[pos++] = edgeFace(db, 0);
	color[pos++] = cornerFace(drb, 0);
	color[pos++] = edgeFace(dl, 0);
	color[pos++] = 'D';
	color[pos++] = edgeFace(dr, 0);
	color[pos++] = cornerFace(dlf, 0);
	color[pos++] = edgeFace(df, 0);
	color[pos++] = cornerFace(dfr, 0);
	//36-44
	color[pos++] = cornerFace(dbl, 1);
	color[pos++] = edgeFace(bl, 0);
	color[pos++] = cornerFace(ulb, 2);
	color[pos++] = edgeFace(db, 1);
	color[pos++] = 'B';
	color[pos++] = edgeFace(ub, 1);
	color[pos++] = cornerFace(drb, 2);
	color[pos++] = edgeFace(br, 0);
	color[pos++] = cornerFace(ubr, 1);
	//45-53
	color[pos++] = cornerFace(dbl, 2);
	color[pos++] = edgeFace(dl, 1);
	color[pos++] = cornerFace(dlf, 1);
	color[pos++] = edgeFace(bl, 1);
	color[pos++] = 'L';
	color[pos++] = edgeFace(fl, 1);
	color[pos++] = cornerFace(ulb, 1);
	color[pos++] = edgeFace(ul, 1);
	color[pos++] = cornerFace(ufl, 2);
}

void Cube::wallsToColor()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			color[i * 9 + j] = walls[i][j];
		}
	}
}
void Cube::colorToWalls()
{

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			walls[i][j] = color[9 * i + j];
		}
	}
}

void Cube::show()
{
	colorToWalls();
	std::cout << "    " << walls[U].substr(0, 3) << std::endl;
	std::cout << "    " << walls[U].substr(3, 3) << std::endl;
	std::cout << "    " << walls[U].substr(6, 3) << std::endl;
	std::cout << walls[L].substr(0, 3) << " " << walls[F].substr(0, 3) << " " << walls[R].substr(0, 3) << " " << walls[B].substr(0, 3) << std::endl;
	std::cout << walls[L].substr(3, 3) << " " << walls[F].substr(3, 3) << " " << walls[R].substr(3, 3) << " " << walls[B].substr(3, 3) << std::endl;
	std::cout << walls[L].substr(6, 3) << " " << walls[F].substr(6, 3) << " " << walls[R].substr(6, 3) << " " << walls[B].substr(6, 3) << std::endl;
	std::cout << "    " << walls[D].substr(0, 3) << std::endl;
	std::cout << "    " << walls[D].substr(3, 3) << std::endl;
	std::cout << "    " << walls[D].substr(6, 3) << std::endl
		<< std::endl;
}

void Cube::readFromFile(const std::string& path)
{
	std::string line;
	ifstream file(path);
	if (file.is_open())
	{
		int i = 0;
		while (std::getline(file, line))
		{
			std::istringstream linestream(line);
			if (i >= 0 && i <= 2)
			{
				while (linestream >> walls[U][i * 3] >> walls[U][i * 3 + 1] >> walls[U][i * 3 + 2]) {}
			}
			if (i >= 3 && i <= 5)
			{
				while (linestream >> walls[L][(i - 3) * 3] >> walls[L][(i - 3) * 3 + 1] >> walls[L][(i - 3) * 3 + 2]
					>> walls[F][(i - 3) * 3] >> walls[F][(i - 3) * 3 + 1] >> walls[F][(i - 3) * 3 + 2]
					>> walls[R][(i - 3) * 3] >> walls[R][(i - 3) * 3 + 1] >> walls[R][(i - 3) * 3 + 2]
					>> walls[B][(i - 3) * 3] >> walls[B][(i - 3) * 3 + 1] >> walls[B][(i - 3) * 3 + 2]) {
				}
			}
			if (i >= 6 && i <= 8)
			{
				while (linestream >> walls[D][(i - 6) * 3] >> walls[D][(i - 6) * 3 + 1] >> walls[D][(i - 6) * 3 + 2]) {}
			}
			i++;
		}
	}
	//FIXING
	rotateR(walls[F]);
	rotateR(walls[B]);
	rotateR(walls[R]);
	rotateR(walls[R]);
	rotateR(walls[L]);
	rotateR(walls[L]);
	//FIXING
	wallsToColor();
	file.close();
}

void Cube::convertColorsToNotation()
{
	char cF;
	char cB;
	char cR;
	char cL;
	char cU;
	char cD;

	cF = walls[F][4];
	cB = walls[B][4];
	cR = walls[R][4];
	cL = walls[L][4];
	cU = walls[U][4];
	cD = walls[D][4];

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (walls[i][j] == cF) walls[i][j] = 'F';
			else if (walls[i][j] == cB) walls[i][j] = 'B';
			else if (walls[i][j] == cR) walls[i][j] = 'R';
			else if (walls[i][j] == cL) walls[i][j] = 'L';
			else if (walls[i][j] == cU) walls[i][j] = 'U';
			else if (walls[i][j] == cD) walls[i][j] = 'D';
		}
	}
	wallsToColor();
}


void Cube::wallsToOrientation()
{
	
}

void Cube::rotateR(std::string& wall)
{
	char temp0 = wall[0];
	char temp1 = wall[1];
	char temp2 = wall[2];
	wall[2] = temp0;
	wall[1] = wall[3];
	wall[0] = wall[6];
	wall[3] = wall[7];
	wall[6] = wall[8];
	wall[7] = wall[5];
	wall[8] = temp2;
	wall[5] = temp1;
}

void Cube::rotateL(std::string& wall)
{
	char temp0 = wall[0];
	char temp1 = wall[1];
	char temp2 = wall[2];
	wall[0] = temp0;
	wall[1] = wall[5];
	wall[2] = wall[8];
	wall[5] = wall[7];
	wall[8] = wall[6];
	wall[7] = wall[3];
	wall[6] = temp2;
	wall[3] = temp1;
}