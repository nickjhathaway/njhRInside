
// Created on 2015/05/20
// main.cpp

#include "njhRInside.h"
int main(int argc, char* argv[]){
    std::cout << "Hello njhRInside!" << std::endl;
    njhRInside::OwnRInside rSes;
    auto & R = rSes.get();
    R.parseEvalQ("print (\"Hello from inside of R\")");
    return 0;
}
