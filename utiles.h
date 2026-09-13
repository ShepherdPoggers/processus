#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <array>


#ifndef UTILES_H
#define UTILES_H


void ecrireHistorique(const std::deque<std::string> &historique, std::string nom = "historique");
std::string construireCommande(const std::vector<char *> &args);
bool estEntienr(const char* texte);
std::array<int, 2> stringInt(const std::vector<char *> &args);
int randomInt(int array);
#endif