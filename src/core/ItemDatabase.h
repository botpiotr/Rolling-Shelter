#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#include "Item.h"

namespace core {

// Petit registre id -> Item. Provisoire : à terme, chargé depuis un JSON
// comme le tech tree. Pour l'instant, rempli à la main via
// defaultTestItems() pour tester le système d'inventaire.
class ItemDatabase {
public:
    void addItem(const Item &item);
    std::optional<Item> find(const std::string &itemId) const;

private:
    std::unordered_map<std::string, Item> m_items;
};

// Quelques objets de test pour valider l'inventaire avant que le tech tree
// ne fournisse une vraie liste d'objets.
ItemDatabase defaultTestItems();

} // namespace core
