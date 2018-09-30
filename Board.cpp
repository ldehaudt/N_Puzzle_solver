#include "Board.hpp"

char Board::flag = 0;
int	(*Board::heuristic)(const Board& st, const Board& goal) = &Board::linearConflictDist; 

Board::Board(int s) : size(s){}

Board::Board(const Board& parent, direction dir, int s, PTR endNode) : size(s) {
	str = parent.str;
	zero = parent.zero;
	switch(dir){
		case up:
			zero -= size;
			break;
		case down:
			zero += size;
			break;
		case left:
			zero--;
			break;
		case right:
			zero++;
			break;
	}
	str[parent.zero] = str[zero];
	str[zero] = 0;
	cameFrom = MPTR(parent);
	dSt = parent.dSt + 1;
	dEnd = Board::heuristic(*this, *endNode);
	if (flag == 'm'){
		dEnd *= size;
	}
}

void	Board::setHeur(char h){
	switch(h){
		case 'h':
			heuristic = &Board::manhattanDist;
			break;
		case 'm':
			heuristic = &Board::maxDist;
			break;
		case 'a':
			heuristic = &Board::atomicDist;
			break;
	}
}

int		Board::manhattanDist(const Board& start, const Board& goal){
	int total = 0;
	int n;

	for (int i = 0; i < start.size * start.size; i++)
		if (i / start.size == 0 || i % start.size == 0)
		{
			n = start.findNumber(goal.str[i]);
			total += (abs(i % start.size - n % start.size) + abs(i / start.size - n / start.size));
		}
	return total;
}

int		Board::maxDist(const Board& start, const Board& goal){
	int total = 0;
	int n;

	for (int i = 0; i < start.size * start.size; i++){
		n = goal.findNumber(start.str[i]);
		total +=  fmax(abs(i % start.size - n % start.size) ,abs(i / start.size - n / start.size));
	}
	return total;
}

int		Board::atomicDist(const Board& start, const Board& goal){
	int total = 0;
	int n;

	for (int i = 0; i < start.size * start.size; i++){
		n = goal.findNumber(start.str[i]);
		total += !(n == i);
	}
	return total;
}

int        Board::linearConflictDist(const Board& st, const Board& goal){
    int total = 0;
    int n;
    int m;
    int n2;
    int m2;
    int size;

    size = st.size;
    for (int i = 0; i < size * size; i++){
        n = goal.findNumber(st.str[i]);
        total +=  (abs(i % size - n % size) + abs(i / size - n / size));
    }  

    for (int i = 0; i < size; i++)
    	for (int j = 0; j < size - 1; j++)
    	{
    		n = goal.findNumber(st.str[i * size + j]);
    		n2 = goal.findNumber(st.str[j * size + i]);
    		for (int k = j + 1; k < size; k++)
    		{
    			if (n / size == i)
    			{
    				m = goal.findNumber(st.str[i * size + k]);
					if (m / size == i && n % size > m % size)
						total += 2;
				}
				if (n2 % size == i)
				{
					m2 = goal.findNumber(st.str[k * size + i]);
					if (m2 % size == i && n2 / size > m2 / size)
						total += 2;
				}
    		}
    	}
    return total;
}

int		Board::findNumber(int num) const{
	size_t i = str.find(num);
	if (i != std::string::npos)
			return (i);
	return (-1);
}

bool Board::operator<(const Board& b){
	if (flag == 'u'){
		return (dSt < b.dSt);
	}
	if (Board::flag != 'g' && dSt + dEnd != b.dSt + b.dEnd)
		return (dSt + dEnd < b.dSt + b.dEnd);
	return (dEnd < b.dEnd);
}

bool Board::operator==(const Board& b){
	return (!str.compare(b.str));
}
