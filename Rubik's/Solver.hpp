#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "rubik.hpp"
#include "Cube.hpp"
#include <iomanip>
//# include <unistd.h>
#include <queue>
#include <unordered_set>
#include <chrono>

#define PTR std::shared_ptr<Cube>
#define MPTR(y) std::make_shared<Cube>(y)

class Solver
{
public:
	bool allowedMoves[18];
	unordered_set<int> middleSlice = {fr, fl, bl, br};
	int64_t phaseGoal[5];
	unordered_set<int64_t> ids;
	int64_t (Solver::*idPhase[4])(const Cube&) = {
		&Solver::idPhase1,
		&Solver::idPhase2,
		&Solver::idPhase3,
		&Solver::idPhase4};
	int64_t idPhase1(const Cube& c);
	int64_t idPhase2(const Cube& c);
	int64_t idPhase3(const Cube& c);
	int64_t idPhase4(const Cube& c);
	Cube BFS(int step, queue<Cube>);
	int64_t getPhaseId(const Cube& c, int phase);
	void nextPhase();
	Solver(const Cube& c);
};

#endif