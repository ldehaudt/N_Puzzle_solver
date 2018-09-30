# N_Puzzle

A solver for the puzzle everyone played as a kid. In the classic tile sliding game N_Puzzle, the goal is to recreate a picture by sliding around
tiles. 

This program uses A* pathfinding with different heuristics to find the fastest way to solve the puzzle. it features customizable options to
like a greedy mode, a uniform mode, and a multiplier mode.

This was done with Conan Wu (conanwu777) <------ *Go check out her stuff*  

## Comiling and Running

Make sure to check out the options bellow before running.

Run `make` to compile. An executable will be created.

Run with:
```
./nPuzzle boards/[board]
```

For randomly generated maps, run:
```
python puzzle_generator.py -s [size] > tmp; ./nPuzzle tmp
```

## Options

`-v` run visualizer
`-g` greedy mode
`-m` multiplier mode (recomended)
`-u` uniform mode

## Input (visualizer only)

Space : pause.

Right arrow : next.

1-4 : switch picture (egg is best ^^)

## Screenshots

![alt text](screenshots/1.png)

![alt text](screenshots/2.png)

![alt text](screenshots/3.png)
