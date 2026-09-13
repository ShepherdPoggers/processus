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

using namespace std;

void splitCommand(char command[], std::deque<std::string> &historique, const int &taille, int &instance)
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
            array<int, 2> param = stringInt(args);
            string commandes[3] = {"ls", "pwd", "man"};
            unordered_map<string, vector<string>> options;
            options["ls"] = {"-a", "-l", "-h", "-R"};
            options["pwd"] = {"-L", "-P"};
            options["man"] = {"-f", "-k", "-a"};
            int nbrCommande = param[0];
            int freqSave = param[1];
            instance ++;
            for (int i = 0; i < nbrCommande; i++)
            {
                randomExecute(commandes, options, historique, taille, instance);
                if ((i + 1) % freqSave == 0)
                {
                    string nom = "historique" + to_string(instance) + "_" + to_string(i + 1);
                    ecrireHistorique(historique, nom);
                }
            }
        }
        else
        {
            execute(historique, taille, prog, argv, args);
        }
    }
}
void execute(
    std::deque<std::string> &historique,
    int taille,
    const char *prog,
    char *const argv[],
    const std::vector<char *> &args)
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
        if (historique.size() > taille)
            historique.pop_front();

        if (waitpid(kidpid, 0, 0) < 0)
        {
            // Raise exception
            return;
        }
    }
}

void randomExecute(const string command[],
                   const unordered_map<string, vector<string>> &options,
                   std::deque<std::string> &historique,
                   const int &taille, int &instance)
{
    string commandeComplete;
    string choix = command[randomInt(command->size())];
    vector<string> choixOptions = options.at(choix);
    string option = choixOptions[randomInt(choixOptions.size())];

    commandeComplete += choix + " " + option;
    splitCommand(commandeComplete.data(), historique, taille, instance);
}