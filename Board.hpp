#ifndef BOARD_HPP
# define BOARD_HPP

# include "nPuzzle.hpp"
# include <vector>

class Board
{
	public:
		static int		(*heuristic)(const Board& st, const Board& goal); 
		static char flag;
		int size;
		std::string str;
		int dSt;
		int dEnd;
		int zero;
		PTR cameFrom;
		Board(int);
		Board(const Board& parent, direction dir, int, PTR endNode);
		void	makeStr();
		int		findNumber(int num) const;
		bool operator<(const Board& rhs);
		bool operator==(const Board& rhs);
		static int		manhattanDist(const Board& st, const Board& goal);
		static int      linearConflictDist(const Board& st, const Board& goal);
		static int		atomicDist(const Board& st, const Board& goal);
		static int		maxDist(const Board& st, const Board& goal);
		static void		setHeur(char h);
};

#endif