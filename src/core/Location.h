#pragma once

#include <string>

namespace core {

// Représentation minimale d'un lieu. Le vrai système de lieux (méta-lieux,
// bonus/malus, génération aléatoire...) viendra avec le tech tree. Pour
// l'instant, juste de quoi identifier "où est le joueur", l'afficher, et
// distinguer le hangar (où le véhicule est accessible) du reste.
struct Location {
    std::string id;
    std::string name;
    std::string imageResourcePath; // ex: ":/images/locations/decrepit_shed.png", vide = pas d'image
};

// Le hangar : lieu de base où l'on peut se reposer, faire du craft (à venir
// avec le tech tree), et partir en exploration. C'est le seul endroit où
// l'inventaire du véhicule est accessible.
inline const Location kHangarLocation{
    "hangar", "Le Hangar", ":/decrepit_shed_1"
};

} // namespace core
