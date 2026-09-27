#pragma once

#include <string>

namespace core {

// Définition statique d'un type d'objet. Ne représente pas une instance
// possédée par le joueur (ça, c'est le rôle d'InventorySlot) : juste ses
// caractéristiques, destinées à terme à être chargées depuis un JSON comme
// le tech tree.
//
// Les booléens indiquent quelles actions ont du sens pour cet objet dans
// l'UI (utiliser/jeter/consommer/prendre-déposer sont génériques ; réparer
// et assembler ne s'appliquent qu'à certains objets).
struct Item {
    std::string id;
    std::string name;
    int maxStackSize = 99;

    bool consumable = false;
    bool usable = false;
    bool repairable = false;
    bool assemblable = false;

    // Effets d'une consommation (valeurs provisoires, appliquées à
    // PlayerState si consumable == true).
    int hungerRestore = 0;
    int thirstRestore = 0;
};

} // namespace core
