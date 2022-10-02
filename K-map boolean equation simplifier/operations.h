#pragma once
#include <vector>
#include <iostream>
#include "Operators.h"

void initialize();


extern OR* Or;
extern AND* And;
extern NOR* Nor;
extern NAND* Nand;
extern EXOR* Xor;
extern COMPLEMENT* complement;
extern std::vector<Operators*> ops;



