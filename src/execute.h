#pragma once


#include <deque>
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <string>
#ifndef EXECUTE_H
#define EXECUTE_H

void execute(
    std::deque<std::string>& historique,
    int taille,
    const char* prog,
    char* const argv[],
    const std::vector<char*>& args,
    bool background,
    std::deque<std::string> *historique2
    
);

void choixFonction(char command[],
                    std::deque<std::string> &historique,
                    const int &taille, int &instance,
                    std::deque<std::string> *historique2);
char ** splitCommand(char command[], std::vector<char *> &args, char *&prog, bool &background);
void random(const std::vector<char *> &args, std::deque<std::string> &historique,
            const int &taille, int &instance);
void randomExecute(const std::array<std::string, 3>& command, const std::unordered_map<std::string, std::vector<std::string>> &options, 
                    std::deque<std::string> &historique, const int &taille, int &instance, std::deque<std::string> *historique2);

#endif
