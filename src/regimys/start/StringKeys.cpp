#include "StringKeys.hpp"
#include "main.hpp"
#include <cstdio>
UNS

namespace StringKeys {
vector<string> keys = vector<string>();
vector<sf::String> strings = vector<sf::String>();

sf::String readLine(ifstream &input) {
    string toReturn;
    for(unsigned int i = 0; i < 1024; i++) {
        int got = input.get();
        // char traded = got;
        if(got == '\n' || got < 31) {
            break;
        } else {
            char truc = got;
            toReturn+=truc;
        }
    }
    sf::String toReelReturn;
    toReelReturn = sf::String::fromUtf8(toReturn.begin(), toReturn.end());
    return toReelReturn;
}

std::string sfStringtoStdString(sf::String const &str) {
    string toReelReturn;
    basic_string<unsigned int> bs = str.toUtf32();
    for(unsigned int i = 0; i < bs.size(); i++) {
        toReelReturn+=bs.at(i);
    }
    return toReelReturn;
}

void initialize(string keysFileS) {
    //Ouverture du fichier de cl�es, initialisation des vectors
    keysFileS = getPath(keysFileS);
    ifstream keysFile(keysFileS.c_str());
    keys = vector<string>();
    strings = vector<sf::String>();
    oplog("Keys initialization");
    if (!keysFile) {//Si ouverture du fichier �chou�e.
        handleError("Keys initialization error", true);
    }
    //R�cup�ration des cl�es
    while (true) {
        sf::String read;
        read = readLine(keysFile);
        if ((sfStringtoStdString(read) == "end")) {//V�rifie si la ligne lue est correcte
            break;//Sinon arr�te de lire
        }
        //Splittage de la ligne en deux parties
        if(read[0] != '#' || read[0] != ' ' || !read.isEmpty()) { //Checks if the string is valid
            std::vector<sf::String> strSplit = split(read, '=');
            if(!strSplit.size() == 0 && strSplit[0] != "") {
                keys.push_back(strSplit[0]);
                if(strSplit.size() < 2) {
                    strings.push_back(" ");
                } else {
                    strings.push_back(sfStringtoStdString(strSplit[1]));
                }
            }

        }

    }
}
sf::String voi;
sf::String &get(string key) {
    key = string("key.") + key;//Ajout du pr�fixe key.
    for (unsigned int i = 0; i < keys.size(); i++) {//Scanne les cl�es
        if (keys[i] == key) {
            return strings[i];
        }
    }
    return voi;//Si rien trouv�, retourne une chaine vide.
}

int getIndex(string key) {
    key = string("key.") + key;//Ajout du pr�fixe key.
    for (unsigned int i = 0; i < keys.size(); i++) {//Scanne les cl�es
        if (keys[i] == key) {
            return i;
        }
    }
    return -1;//Si rien trouv�, retourne -1
}

sf::String split(sf::String const& str, char const& splitter, int const& part) {
    int instances = 0;//Compte le nombre d'instances du splitter
    for (unsigned int i = 0; i < str.toUtf32().size(); i++) {//Scanne la chaine pour r�cuperer le nombre d'instances du splitter
        if ((char) str.toUtf32()[i] == splitter) {
            instances++;
        }
    }
    sf::String toReturn[instances + 1];//Cr�e un tableau contenant tous les splits
    for (unsigned int i = 0, enCours = 0; i < str.toUtf32().size(); i++) {//Parcours la chaine pour la s�parer
        if ((char) str.toUtf32()[i] == splitter) {
            enCours++;
        } else {
            toReturn[enCours] += str.toUtf32()[i];
        }
    }
    return toReturn[part];
}

std::vector<sf::String> split(sf::String const& str, char const& splitter) {
    int instances = 0;//Compte le nombre d'instances du splitter
    for (unsigned int i = 0; i < str.toUtf32().size(); i++) {//Scanne la chaine pour r�cuperer le nombre d'instances du splitter
        if ((char) str.toUtf32()[i] == splitter) {
            instances++;
        }
    }
    std::vector<sf::String> toReturn(instances + 1);//Cr�e un tableau contenant tous les splits
    for (unsigned int i = 0, enCours = 0; i < str.toUtf32().size(); i++) {//Parcours la chaine pour la s�parer
        if ((char) str.toUtf32()[i] == splitter) {
            enCours++;
        } else {
            toReturn[enCours] += str.toUtf32()[i];
        }
    }
    return toReturn;
}

int countInstances(sf::String const& str, char const& toSearch) {
    int instances = 0;
    for (unsigned int i = 0; i < str.toUtf32().size(); i++) {
        if ((char) str.toUtf32()[i] == toSearch) {
            instances++;
        }
    }
    return instances;
}

}