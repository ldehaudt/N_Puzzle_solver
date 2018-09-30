#ifndef SOLVER_HPP
# define SOLVER_HPP

# include "Display.hpp"
# include "nPuzzle.hpp"
# include "Board.hpp"
# include <iomanip>
# include <unistd.h>
# include <queue>
# include <vector>
# include <unordered_set>
# include <chrono>

class Compare
{
public:
    bool operator() (PTR a, PTR b)
    {
        return !(*a < *b);
    }
};

class Solver
{
	PTR findEnd();
	public:
		std::unordered_set<std::string> closedList;
		std::priority_queue<PTR, std::vector<PTR>, Compare> openList;
		std::unordered_set<std::string> openSet;
		int size;
		PTR st;
		PTR end;
		char flag;
		char heur;
		Solver(PTR start, int s, char, char, bool);
		void	printBoard(PTR b);
		void	addOpenList(PTR p);
		void	printOutput(PTR ans, int time, int size, std::chrono::milliseconds);
		void	recursivePrint(PTR ans, Display *dis);
		bool	inOpenSet(PTR newPtr);
		bool	inBounds(int pos, int dir);
		bool	isSolvable(PTR board);
		PTR	aStar(int& time, int& size);
};

#endif