#include "execute.h"

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <deque>
#include <array>
#include <exception>
#include <unordered_map>
#include "utiles.h"
#include "shellEnter.h"
using namespace std;
using namespace Utiles;

// Séparation des arguments de la commande.
void splitCommand(char command[],
                  std::deque<std::string> &historique,
                  const int &taille, int &instance,
                  std::deque<std::string> *historique2)
{
    if (strlen(command) != 0)
    {
        vector<char *> args;
        char *prog = strtok(command, " ");
        char *tmp = prog;

        while (tmp != NULL)
        {
            args.push_back(tmp);
            tmp = strtok(NULL, " ");
        }

        char **argv = new char *[args.size() + 1];

        for (int k = 0; k < args.size(); k++)
        {
            argv[k] = args[k];
        }

        argv[args.size()] = NULL;

        if (prog[0] == '.')
        {
            std::system(args[0]);
        }
        else if (strcmp(prog, "random") == 0)
        {
            random(args, historique, taille, instance);
        }
        else
        {
            execute(historique, taille, prog, argv, args, historique2);
        }
    }
    else
    {
        throw ShellEnter();
    }
}


// Permet d'executer une commande du shell avec un fork et execvp.
void execute(
    std::deque<std::string> &historique,
    int taille,
    const char *prog,
    char *const argv[],
    const std::vector<char *> &args,
    std::deque<std::string> *historique2 = nullptr)
{
    pid_t kidpid = fork();

    if (kidpid < 0)
    {
        perror("Could not fork");
        // Raise exception
        return;
    }

    else if (kidpid == 0)
    {
        execvp(prog, argv);
    }

    else
    {
        // Construction du string pour l'historique
        string arguments = construireCommande(args);
        string histoire = "\t" + arguments + "\t" + to_string(kidpid);
        historique.push_back(histoire);
        if (historique2 != nullptr)
            historique2->push_back(histoire);

        if (historique.size() > taille)
            historique.pop_front();

        if (waitpid(kidpid, 0, 0) < 0)
        {
            // Raise exception
            return;
        }
    }
}

// Traitement de la commande random
void random(
    const vector<char *> &args,
    deque<string> &historique,
    const int &taille,
    int &instance)
{
    array<int, 2> param = stringInt(args);
    array<string, 3> commandes = {"ls", "ps", "pwd"};
    unordered_map<string, vector<string>> options;
    options["ls"] = {"", "-a", "-l", "-h", "-R"};
    options["pwd"] = {"", "-L", "-P"};
    options["ps"] = {"", "-e", "-f", "-o"};
    int nbrCommande = param[0];
    int freqSave = param[1];
    instance++;
    deque<string> *historiqueComplet = new deque<string>();
    for (int i = 0; i < nbrCommande; i++)
    {
        randomExecute(commandes, options, historique, taille, instance, historiqueComplet);

        if ((i + 1) % freqSave == 0) // Vérification si on doit sauvegarder
        {
            string nom = "historique" + to_string(instance) + "_" + to_string(i + 1);
            ecrireHistorique(historique, nom);
        }
    }
    string nom = "historique" + to_string(instance) + "_Complet";
    ecrireHistorique(*historiqueComplet, nom);
}

// Choisi aléatoirement la commande à exécuter
void randomExecute(const array<string, 3> &command,
                   const unordered_map<string, vector<string>> &options,
                   std::deque<std::string> &historique,
                   const int &taille, int &instance, std::deque<std::string> *historique2)
{
    string commandeComplete;
    string choix = command[randomInt(command.size())];
    vector<string> choixOptions = options.at(choix);
    string option = choixOptions[randomInt(choixOptions.size())];
    commandeComplete += choix + " " + option;

    // Appelle de splitCommande  pour aller formater correctement la commande et rentrer dans execute
    splitCommand(commandeComplete.data(), historique, taille, instance, historique2);
}
