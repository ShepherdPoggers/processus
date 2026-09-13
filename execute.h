#pragma once


#include <deque>
#include <string>
#include <vector>
#include <unordered_map>
#ifndef EXECUTE_H
#define EXECUTE_H

void execute(
    std::deque<std::string>& historique,
    int taille,
    const char* prog,
    char* const argv[],
    const std::vector<char*>& args
);

void splitCommand(char command[], std::deque<std::string> &historique, const int &taille, int &instance);
void randomExecute(const std::string command[], const std::unordered_map<std::string, std::vector<std::string>> &options, 
                    std::deque<std::string> &historique, const int &taille, int &instance);

#endif