#pragma once

#include <optional>
#include <string>
#include <vector>

#include "Item.h"

namespace core {

// Une case d'inventaire : un seul type d'objet, empilé jusqu'à sa taille
// de stack. Une case vide a un itemId vide.
struct InventorySlot {
    std::string itemId;
    int quantity = 0;

    bool isEmpty() const { return itemId.empty() || quantity <= 0; }
};

// Inventaire générique à cases, réutilisable pour le joueur (capacité
// limitée) comme pour le véhicule (illimité).
//
// - capacity = std::nullopt  -> illimité : de nouvelles cases sont créées
//   à la volée quand nécessaire (utilisé pour l'inventaire du véhicule).
// - capacity = N             -> N cases fixes, jamais plus (utilisé pour
//   l'inventaire du joueur, N = 20).
class Inventory {
public:
    explicit Inventory(std::optional<int> capacity = std::nullopt);

    std::optional<int> capacity() const;
    const std::vector<InventorySlot> &InventorySlots() const;

    // Quantité totale possédée de cet item, tous slots confondus.
    int quantityOf(const std::string &itemId) const;

    // Ajoute `quantity` unités de `item` (la taille de stack vient de
    // item.maxStackSize). Remplit d'abord les slots existants du même item,
    // puis en crée de nouveaux si la capacité le permet. Retourne la
    // quantité qui n'a PAS pu être ajoutée (0 si tout a été placé ; > 0 si
    // l'inventaire est plein -- ne peut arriver que si capacity a une valeur).
    int addItem(const Item &item, int quantity);

    // Retire jusqu'à `quantity` unités de l'item `itemId`. Retourne la
    // quantité effectivement retirée (peut être < quantity si le joueur n'en
    // a pas assez). Les slots vidés sont supprimés pour ne pas laisser de
    // trous.
    int removeItem(const std::string &itemId, int quantity);

    bool isFull() const;

private:
    std::optional<int> m_capacity;
    std::vector<InventorySlot> m_slots;
};

} // namespace core
