#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include "nPuzzle.hpp"
#include "Board.hpp"
#include "Solver.hpp"

int	checkValid(const Board& b, int size){
	std::map<short, char> duplicates;
	int zero;

	for (int x = 0; x < size; x++){
		for (int y = 0; y < size; y++){
			if (duplicates[b.str[y * size + x]] == 1)
			{
				std::cout << RED << "The value " << static_cast<int>(b.str[y * size + x])
				<< " is present twice. Dummy.\n";
				exit(0);
			}
			if (b.str[y * size + x] >= static_cast<char>(size * size)
				|| b.str[y * size + x] < static_cast<char>(0))
			{
				std::cout << RED << "The value " << static_cast<int>(b.str[y * size + x])
				<< " is not in range. Dummy.\n";
				exit(0);
			}
			if (b.str[y * size + x] == 0)
				zero = y * size + x;
			duplicates[b.str[y * size + x]] = 1;
		}
	}
	return zero;
}

PTR		getStartingMap(std::fstream& file, int size){
	std::string line;
	PTR b = MPTR(Board(size));
	int pos;
	int y = 0;

	if (size <= 1){
		std::cout << ORANGE << "There is nothing to solve V_V. Dummy.\n";
		exit(0);
	}
    while (std::getline(file, line))
    {
    	if (line.find('#') != std::string::npos)
    		line = line.substr(0, line.find('#'));
    	if (line.size() == 0)
    		continue ;
    	for (int i = 0; i < size; i++){
    		b->str += static_cast<char>(stoi(line));
    		pos = 0;
    		while (line[pos] && line[pos] == ' ')
	    		pos++;
	    	while (line[pos] && line[pos] != ' ')
	    		pos++;
	    	while (line[pos] && line[pos] == ' ')
	    		pos++;
	    	if (!line[pos] && i < size - 1){
	    		std::cout << RED << "Line " << y + 1 << " of the puzzle is too short. Dummy.\n";
				exit(0);
    		}
    		line = line.substr(pos);
    	}
    	if (line.size() > 0){
    		std::cout << RED << "Line " << y + 1 << " of the puzzle is too long. Dummy.\n";
			exit(0);
    	}
    	y++;
    }
    b->zero = checkValid(*b, size);
    b->dSt = 0;
    b->dEnd = 0;
    b->cameFrom = PTR(nullptr);
    b->size = size;
    return b;
}

int main(int ac, char** av){
	PTR st;
	std::fstream file;
	std::string line;
	int size = 0;
	char flag = 0;
	char heur = 0;
	int fPos = 2;
	bool visual = false;

	if (ac < 2){
		std::cout << ORANGE << "Usage : nPuzzle [start file] [-v] [-m | -g | -u] [heurstic]\n";
		std::cout << "\tAvaliable heurstics :\tmanhattan | max | atomic | (default)linear conflict\n";
		return (0);
	}
	if (ac >= 3){
		if (strcmp(av[fPos], "-v") == 0){
			visual = true;
			fPos++;
		}
	}
	if (ac >= fPos + 1){
		if (strcmp(av[fPos], "-g") == 0){
			flag = 'g';
			fPos++;
		}
		else if (strcmp(av[fPos], "-u") == 0){
			flag = 'u';
			fPos++;
		}
		else if (strcmp(av[fPos], "-m") == 0){
			flag = 'm';
			fPos++;
		}
	}
	if (ac >= fPos + 1){
		if (strcmp(av[fPos], "manhathan") == 0){
			heur = 'h';
			fPos++;
		}
		else if (strcmp(av[fPos], "max") == 0){
			heur = 'm';
			fPos++;
		}
		else if (strcmp(av[fPos], "atomic") == 0){
			heur = 'a';
			fPos++;
		}
	}
 	file.open(av[1]);
    if (!file.good()){
        std::cout << RED << "nPuzzle: "<< av[1] << ": no such file or directory\n";
        return (0);
    }
    while (size == 0 && std::getline(file, line))
    {
    	if (line.find('#') != std::string::npos)
    		line = line.substr(0, line.find('#'));
    	if (line.size() > 0)
    		size = std::stoi(line);
    }
    st = getStartingMap(file, size);
    Solver slov(st, size, flag, heur, visual);
}
