#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

#include <iostream>
#include <memory>
#include <math.h>

# define PTR std::shared_ptr<Board>
# define MPTR(y) std::make_shared<Board>(y)

# define RED "\e[1;38;2;225;20;20m"
# define WHITE "\e[1;38;2;255;251;214m"
# define YELLO "\e[1;38;2;255;200;0m"
# define ORANGE "\e[1;38;2;255;120;10m"
# define GREEN "\e[1;38;2;0;175;117m"

enum direction {up, down, left, right};

#endif