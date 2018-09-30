#include "Solver.hpp"

Solver::Solver(PTR start, int s, char flg, char h, bool visual) : size(s),
st(start), end(findEnd()), flag(flg), heur(h){
	end = findEnd();
	Board::setHeur(heur);
	st->dEnd = st->heuristic(*st, *end);
	if (isSolvable(st) != isSolvable(end)){
		std::cout << RED << "The puzzle is not solvable =(\n";
		exit(0);
	}
	Board::flag = flag;
	int t, sz;
	std::chrono::milliseconds startTime = std::chrono::duration_cast<std::chrono::milliseconds>
	(std::chrono::system_clock::now().time_since_epoch());
	PTR answer = aStar(t, sz);
	std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>
	(std::chrono::system_clock::now().time_since_epoch()) - startTime;
	std::cout << YELLO << "Your puzzle has been solved :\n" << WHITE;
	if (visual){
		Display dis;
		recursivePrint(answer, &dis);
		printOutput(answer, t, sz, time);
		dis.refresh(answer, end, true);
	}
	else {
		recursivePrint(answer, NULL);
		printOutput(answer, t, sz, time);
	}
}

void	Solver::printOutput(PTR ans, int time, int size, std::chrono::milliseconds t){
	std::cout << YELLO << "Time complexity: " << time << "\n";
	std::cout << "Size complexity: " << size << "\n";
	std::cout << "Number of moves : " << ans->dSt << "\n";
	std::cout << "Time to find path : " << static_cast<float>(t.count()) / 1000 << " seconds\n";
}

void	Solver::recursivePrint(PTR ans, Display *dis){
	if (ans->cameFrom)
		recursivePrint(ans->cameFrom, dis);
	printBoard(ans);
	if (dis){
		dis->refresh(ans, end, false);
		usleep(1500000 / size / size);
	}
}

bool	Solver::isSolvable(PTR b){
	int inversions = 0;
	for (int i = 0; i < size * size; i++)
		for (int j = i + 1; j < size * size; j++)
			if (b->str[i] != 0 && b->str[j] != 0)
				if (b->str[i] > b->str[j])
					inversions++;
	if (size % 2 == 1)
		return (inversions % 2 == 0);
	if ((b->zero / size) % 2 == 0)
		return (inversions % 2 == 1);
	return (inversions % 2 == 0);
}

PTR Solver::findEnd(){
	int ts = size * size;
	PTR b = MPTR(Board(size));
	int cur = 1;
	int co = 0;
	int cix = 1;
	int ciy = 0;

	for (int i = 0; i < size * size; i++)
		b->str += -1;
	while (cur <= ts)
	{
		b->str[co] = cur;
		cur++;
		if (co % size + cix == size || co % size + cix < 0 ||
			(cix != 0 && b->str[co + cix] != -1))
		{
			ciy = cix;
			cix = 0;
		}
		else if (co / size + ciy == size || co / size + ciy < 0 ||
			(ciy != 0 && b->str[co + ciy * size] != -1))
		{
			cix = -ciy;
			ciy = 0;
		}
		co += cix + ciy * size;
	}
	co -= cix + ciy * size;
	b->zero = co;
	b->dEnd = 0;
	b->dSt = -1;
	b->cameFrom = PTR(nullptr);
	b->str[co] = 0;
	return b;
}

PTR		Solver::aStar(int& t, int& s){
	PTR cur;
	PTR tmp;
	int count = 0;

	closedList.clear();
	openList = std::priority_queue<PTR, std::vector<PTR>, Compare>();
	openList.push(st);
	openSet.insert(st->str);
	while (openList.size() > 0){
		cur = openList.top();
		openList.pop();
		if (--count <= 0){
			std::cout << YELLO << "Beep Boop ... I am working ... do not disturb...\n";
			count = 100000;
		}
		if (cur->dEnd == 0){
			t = closedList.size();
			s = closedList.size() + openList.size();
			return cur;
		}
		closedList.insert(cur->str);
		for (int i = up; i <= right; i++){
			if (!inBounds(cur->zero, i))
				continue;
			tmp = MPTR(Board(*cur, static_cast<direction>(i), size, end));
			if (closedList.find(tmp->str) != closedList.end())
				continue;
			if (openSet.find(tmp->str) == openSet.end()){
				openList.push(tmp);
				openSet.insert(tmp->str);
			}
		}
	}
	return PTR(nullptr);
}

bool	Solver::inBounds(int pos, int dir){
	switch(dir){
		case up:
			pos -= size;
			break;
		case down:
			pos += size;
			break;
		case left:
			if (pos % size == 0)
				return false;
			pos--;
			break;
		case right:
			if (pos % size == size - 1)
				return false;
			pos++;
			break;
		}
	if (pos < 0 || pos >= size * size)
		return false;
	return true;	
}

void	Solver::printBoard(PTR b){
	for (int y = 0; y < size; y++){
		for (int x = 0; x < size; x++)
			std::cout << std::setw(3) << static_cast<int>(b->str[y * size + x]) << " "; 
		std::cout << "\n";
	}
	std::cout << "\n";	
}
