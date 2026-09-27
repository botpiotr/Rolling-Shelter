#pragma once

#include <string>
#include <vector>

#include "Location.h"

namespace core {

// Une option disponible à un lieu de l'aventure (ex: "Fouiller les
// environs"). Pour l'instant, juste un libellé -- pas encore d'effet
// mécanique réel (viendra avec le système de lieux complet/tech tree).
struct AdventureOption {
    std::string id;
    std::string label;
};

// Un arrêt de l'aventure : un lieu + les options qu'on peut y faire.
// "Rentrer au hangar" n'est PAS une option ici : c'est une action toujours
// disponible, gérée séparément par l'UI/MainWindow.
struct AdventureStep {
    Location location;
    std::vector<AdventureOption> options;
};

// Aventure de test (provisoire) pour valider la boucle lieu par lieu, en
// attendant la génération de carte en nœuds définie dans le GDD.
std::vector<AdventureStep> defaultTestAdventure();

} // namespace core
