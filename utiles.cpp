#include "utiles.h"
#include <iostream>
#include <cctype>
#include <array>
#include <sstream>

using namespace std;

void ecrireHistorique(const deque<string> &historique, string nom)
{
    nom += ".txt";
    string path = "historique/";

    ofstream fichierHistorique(path + nom);
    for (int i = 0; i < historique.size(); i++)
    {
        fichierHistorique << historique.size() - i << historique[i] << endl;
        cout << historique.size() - i << historique[i] << endl;
    }
    return;
    fichierHistorique.close();
}

// Reconstruction de la commande
string construireCommande(const std::vector<char *> &args)
{
    string arguments = "";
    for (int i = 0; i < args.size(); i++)
    {
        arguments += args[i];
        if (i < args.size() - 1)
            arguments += " ";
    }
    return arguments;
}
// Extraction des arguments de la commande automatique
array<int, 2> stringInt(const std::vector<char *> &args)
{
    vector<string> mots;
    string commande = construireCommande(args);
    istringstream flux(commande);
    string mot;
    array<int, 2> argument;
    while (flux >> mot)
    {
        mots.push_back(mot);
    }
    if (mots.size() != 3)
        throw invalid_argument("Utilisation : automatique <nombreCommandes> <frequenceSauvegarde>");

    try
    {
        argument[0] = stoi(mots[1]);
        argument[1] = stoi(mots[2]);
    }catch(const exception e)
    {
        throw invalid_argument("Utilisation : automatique <nombreCommandes> <frequenceSauvegarde>");
    }

    return argument;
}

int randomInt(int array)
{
    return rand() % array;
}
