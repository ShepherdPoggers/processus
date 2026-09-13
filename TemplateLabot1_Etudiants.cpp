#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <sys/wait.h>
#include <deque>
#include "execute.h"
#include "utiles.h"
using namespace std;

// Parcours un deque<string> et écrit les résultats dans la console et dans un txt

int main()
{

   int taille = 5;           // Nombre d'élement dans l'historique
   deque<string> historique; // Utilisation du deque pour faciliter l'ajout et le retrait d'élement
   int  instance = 0;
   while (true)
   {
      string result;
      std::cout << "DesbiensShepherd< ";
      char command[128];
      cin.getline(command, 128);

      if (strcmp(command, "exit") == 0 || strcmp(command, "stop") == 0)
      {
         return 0;
      }
      else if (strcmp(command, "historique") == 0)
      {
         ecrireHistorique(historique);
      }
      else
      {
         splitCommand(command, historique, taille, instance);
      }
   }

   return 0;
}
