//This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Cube.hpp"
#include "Solver.hpp"
#include "rubik.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <stdlib.h>

template <typename Out>
void split(const std::string& s, char delim, Out result) {
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		*result++ = item;
	}
}

std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

Cube cube;

string translate(const string& path)
{
	string ret;

	/*for (size_t i = 0; path[i]; i++)
	{
		if (path[i] == '1')
			ret += " ";
		else if (path[i] == '3')
			ret += "' ";
		else if (path[i] == '2')
			ret += "2 ";
		else
			ret += path[i];
	}*/
	for (size_t i = 0; path[i]; i++)
	{
		if (path[i] == '1')
			ret += "1 ";
		else if (path[i] == '3')
			ret += "3 ";
		else if (path[i] == '2')
			ret += "2 ";
		else
			ret += path[i];
	}
	return ret;
}

void shuffle(int ac, char** av)
{
	if (ac == 1 || ac > 3)
	{
		cout << ORANGE << "Usage: Rubik \"shuffle string\" [-m | -r]\n";
		cout << "\tShuffle string: F B U D L R with variations F F' F2\n";
		cout << "\t-m: manually solve the cube with user input\n";
		cout << "\t-r: solve the cube without hashing\n";
		exit(1);
	}
	if (ac >= 2)
		for (size_t i = 0; av[1][i]; i++)
			if (av[1][i] == 'F' || av[1][i] == 'R' || av[1][i] == 'U' ||
				av[1][i] == 'B' || av[1][i] == 'L' || av[1][i] == 'D')
			{
				int num = 1;
				if (av[1][i + 1] == '\'')
					num = 3;
				else if (av[1][i + 1] == '2')
					num = 2;
				cube.rotCube(av[1][i], num);
			}
	cout << GREEN << "\nCube shuffle complete!\n";
}

void hashSolve(Cube* solverCube, Solver* s, string* output)
{
	char face;
	int num;
	int i = 0;
	Cube c;
	for (int phase = 1; phase <= 4; phase++)
	{
		cout << "Phase " << phase << " moves: " << endl;
		while (s->getPhaseId(*solverCube, phase) != s->phaseGoal[phase])
		{
			string path = phaseHash[phase - 1][s->getPhaseId(*solverCube, phase)];
			if (path.empty())
			{
				cout << "Solution not found" << endl;
				exit(1);
			}
			cout << '\t' << translate(path) << endl;
			if (path[0] != 'E')
			{
				output->append(path);
				while (!path.empty())
				{
					face = path[0];
					num = path[1] - '0';
					solverCube->rotCube(face, num);
					path = path.substr(2);
				}
			}
		}
		if (*solverCube == c)
		{
			return;
		}
		s->nextPhase();
	}
}
using namespace std::chrono_literals;
int main(int ac, char** av)
{
	cube.readFromFile("colors.txt");
	cube.convertColorsToNotation();
	cube.getPosOri();
	cube.show();
	string output;
	string outputTranslated;
	Cube solverCube;
	solverCube = cube;
	Solver s(solverCube);
	hashSolve(&solverCube, &s, &output);
	cout << "Final output:" << endl;
	outputTranslated = translate(output);
	cout << outputTranslated << endl;
	cout << "Total steps: " << output.size() / 2 << endl;

	std::cout << "Write to a file" << std::endl;
	std::ofstream file("moves.txt");
	if (file.is_open())
	{
		file << outputTranslated;
		file.close();
	}
	else
	{
		std::cout << "Can't open a file!" << std::endl;
	}

	//display.txt
	std::ofstream file_d("display.txt");
	if (file_d.is_open())
	{
		cube.readFromFile("colors.txt");
		cube.convertColorsToNotation();
		cube.getPosOri();

		enum class Moves
		{
			R, R2, Ri,
			L, L2, Li,
			U, U2, Ui,
			D, D2, Di,
			F, F2, Fi,
			B, B2, Bi,
		};
		auto moves = split(outputTranslated, ' ');
		std::unordered_map<std::string, Moves> m_moves =
		{
			{"R1",Moves::R},
			{"R2",Moves::R2},
			{"R3",Moves::Ri},
			{"L1",Moves::L},
			{"L2",Moves::L2},
			{"L3",Moves::Li},
			{"U1",Moves::U},
			{"U2",Moves::U2},
			{"U3",Moves::Ui},
			{"D1",Moves::D},
			{"D2",Moves::D2},
			{"D3",Moves::Di},
			{"B1",Moves::B},
			{"B2",Moves::B2},
			{"B3",Moves::Bi},
			{"F1",Moves::F},
			{"F2",Moves::F2},
			{"F3",Moves::Fi}
		};

		for (const auto& m : moves)
		{
			switch (m_moves[m])
			{
			case Moves::R:
				cube.rotCube('R', 1);
				break;
			case Moves::R2:
				cube.rotCube('R', 2);
				break;
			case Moves::Ri:
				cube.rotCube('R', -1);
				break;
			case Moves::L:
				cube.rotCube('L', 1);
				break;
			case Moves::L2:
				cube.rotCube('L', 2);
				break;
			case Moves::Li:
				cube.rotCube('L', -1);
				break;
			case Moves::B:
				cube.rotCube('B', 1);
				break;
			case Moves::B2:
				cube.rotCube('B', 2);
				break;
			case Moves::Bi:
				cube.rotCube('B', -1);
				break;
			case Moves::F:
				cube.rotCube('F', 1);
				break;
			case Moves::F2:
				cube.rotCube('F', 2);
				break;
			case Moves::Fi:
				cube.rotCube('F', -1);
				break;
			case Moves::U:
				cube.rotCube('U', 1);
				break;
			case Moves::U2:
				cube.rotCube('U', 2);
				break;
			case Moves::Ui:
				cube.rotCube('U', -1);
				break;
			case Moves::D:
				cube.rotCube('D', 1);
				break;
			case Moves::D2:
				cube.rotCube('D', 2);
				break;
			case Moves::Di:
				cube.rotCube('D', -1);
				break;
			}
			cube.colorToWalls();
			cube.fixWalls();
			file_d << " " << cube.walls[U].substr(0, 3) << "    " << cube.walls[L].substr(3, 3) << "    " << cube.walls[F].substr(3, 3) << std::endl;
			file_d << " " << cube.walls[U].substr(3, 3) << "    " << cube.walls[L].substr(0, 3) << "    " << cube.walls[F].substr(0, 3) << std::endl;
			file_d << " " << cube.walls[U].substr(6, 3) << "    " << cube.walls[L].substr(6, 3) << "    " << cube.walls[F].substr(6, 3) << std::endl;
			file_d << " " << cube.walls[R].substr(3, 3) << "    " << cube.walls[B].substr(3, 3) << "    " << cube.walls[D].substr(0, 3) << std::endl;
			file_d << " " << cube.walls[R].substr(0, 3) << "    " << cube.walls[B].substr(0, 3) << "    " << cube.walls[D].substr(3, 3) << std::endl;
			file_d << " " << cube.walls[R].substr(6, 3) << "    " << cube.walls[B].substr(6, 3) << "    " << cube.walls[D].substr(6, 3) << std::endl;
		}
	}

	////ANIMATION:
	//std::cout << "\n-------------------------------------------------\n";
	//std::cout << "CLICK ENTER TO START ANIMATION\n";
	//std::cout << "\-------------------------------------------------\n";
	//std::cin.get();
	//cube.readFromFile("colors.txt");
	//cube.convertColorsToNotation();
	//cube.getPosOri();
	//cube.show();
	//enum class Moves
	//{
	//	R, R2, Ri,
	//	L, L2, Li,
	//	U, U2, Ui,
	//	D, D2, Di,
	//	F, F2, Fi,
	//	B, B2, Bi,
	//};
	//auto moves = split(outputTranslated, ' ');
	//std::unordered_map<std::string, Moves> m_moves =
	//{
	//	{"R",Moves::R},
	//	{"R2",Moves::R2},
	//	{"R'",Moves::Ri},
	//	{"L",Moves::L},
	//	{"L2",Moves::L2},
	//	{"L'",Moves::Li},
	//	{"U",Moves::U},
	//	{"U2",Moves::U2},
	//	{"U'",Moves::Ui},
	//	{"D",Moves::D},
	//	{"D2",Moves::D2},
	//	{"D'",Moves::Di},
	//	{"B",Moves::B},
	//	{"B2",Moves::B2},
	//	{"B'",Moves::Bi},
	//	{"F",Moves::F},
	//	{"F2",Moves::F2},
	//	{"F'",Moves::Fi}
	//};

	//for (const auto& m : moves)
	//{
	//	switch (m_moves[m])
	//	{
	//	case Moves::R:
	//		cube.rotCube('R', 1);
	//		break;
	//	case Moves::R2:
	//		cube.rotCube('R', 2);
	//		break;
	//	case Moves::Ri:
	//		cube.rotCube('R', -1);
	//		break;
	//	case Moves::L:
	//		cube.rotCube('L', 1);
	//		break;
	//	case Moves::L2:
	//		cube.rotCube('L', 2);
	//		break;
	//	case Moves::Li:
	//		cube.rotCube('L', -1);
	//		break;
	//	case Moves::B:
	//		cube.rotCube('B', 1);
	//		break;
	//	case Moves::B2:
	//		cube.rotCube('B', 2);
	//		break;
	//	case Moves::Bi:
	//		cube.rotCube('B', -1);
	//		break;
	//	case Moves::F:
	//		cube.rotCube('F', 1);
	//		break;
	//	case Moves::F2:
	//		cube.rotCube('F', 2);
	//		break;
	//	case Moves::Fi:
	//		cube.rotCube('F', -1);
	//		break;
	//	case Moves::U:
	//		cube.rotCube('U', 1);
	//		break;
	//	case Moves::U2:
	//		cube.rotCube('U', 2);
	//		break;
	//	case Moves::Ui:
	//		cube.rotCube('U', -1);
	//		break;
	//	case Moves::D:
	//		cube.rotCube('D', 1);
	//		break;
	//	case Moves::D2:
	//		cube.rotCube('D', 2);
	//		break;
	//	case Moves::Di:
	//		cube.rotCube('D', -1);
	//		break;
	//	}
	//	system("CLS");
	//	cube.show();
	//	std::this_thread::sleep_for(100ms);
	//}

	//NUMERATION
	/* cube.show();
	 stringstream ss;
	 for (int i = 0; i < 6; i++)
		for (int j = 0; j < 9; j++)
		{
			ss << j;
			cube.walls[i][j] = const_cast<char *>(ss.str().c_str())[j];
			cube.wallsToColor();
		}
	 cube.show(false);*/
	 //NUMERATION

	 //ROTATE
	 /* cube.rotCube('R',1);
	  cube.show();
	  cube.rotCube('D', 1);
	  cube.show();*/
	  //ROTATE

	  //TEST
	  /*std::ofstream file("moves1000.txt");
	  for (int i = 1; i <= 10000;i++)
	  {
		  cube.readFromFile("Files/colors" + std::to_string(i) + ".txt");
		  cube.convertColorsToNotation();
		  cube.getPosOri();

		  string outputTranslated;
		  string output;
		  Cube solverCube;
		  solverCube = cube;
		  Solver s(solverCube);
		  hashSolve(&solverCube, &s, &output);
		  if (file.is_open())
		  {
			  file << output.size() / 2<<std::endl;
		  }
		  else
		  {
			  std::cout << "Can't open a file!" << std::endl;
		  }
		  std::cout << "Next"<<std::endl;
	  }
	  file.close();*/
	  //TEST
	return 0;
}