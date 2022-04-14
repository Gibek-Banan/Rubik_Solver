#include "Cube.hpp"
#include "Solver.hpp"
#include "Rubik.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

Cube cube;

string translate(string path)
{
	string ret;

	for (int i = 0; path[i]; i++)
	{
		if (path[i] == '1')
			ret += " ";
		else if (path[i] == '3')
			ret += "\' ";
		else if (path[i] == '2')
			ret += "2 ";
		else
			ret += path[i];
	}
	return ret;
}

void shuffle(int ac, char **av)
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
		for (int i = 0; av[1][i]; i++)
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

void hashSolve(Cube *solverCube, Solver *s, string *output)
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
			if (path == "")
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
			solverCube->show();
			return;
		}
		s->nextPhase();
	}
}

int main(int ac, char **av)
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