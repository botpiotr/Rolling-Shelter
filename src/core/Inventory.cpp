#include "Inventory.h"

#include <algorithm>

namespace core {

Inventory::Inventory(std::optional<int> capacity)
    : m_capacity(capacity)
{
}

std::optional<int> Inventory::capacity() const
{
    return m_capacity;
}

const std::vector<InventorySlot> &Inventory::InventorySlots() const
{
    return m_slots;
}

int Inventory::quantityOf(const std::string &itemId) const
{
    int total = 0;
    for (const auto &slot : m_slots) {
        if (slot.itemId == itemId) {
            total += slot.quantity;
        }
    }
    return total;
}

bool Inventory::isFull() const
{
    if (!m_capacity.has_value()) {
        return false; // illimité : jamais plein
    }
    return static_cast<int>(m_slots.size()) >= *m_capacity;
}

int Inventory::addItem(const Item &item, int quantity)
{
    int remaining = quantity;

    // 1. Remplir les slots existants du même item, jusqu'à leur stack max.
    for (auto &slot : m_slots) {
        if (remaining <= 0) {
            break;
        }
        if (slot.itemId != item.id) {
            continue;
        }
        const int spaceInSlot = item.maxStackSize - slot.quantity;
        const int toAdd = std::min(spaceInSlot, remaining);
        slot.quantity += toAdd;
        remaining -= toAdd;
    }

    // 2. Créer de nouveaux slots tant qu'il reste à placer et que la
    //    capacité le permet (ou qu'il n'y a pas de limite).
    while (remaining > 0) {
        if (m_capacity.has_value() && static_cast<int>(m_slots.size()) >= *m_capacity) {
            break; // inventaire plein : le reste ne peut pas être ajouté
        }
        const int toAdd = std::min(item.maxStackSize, remaining);
        m_slots.push_back(InventorySlot{ item.id, toAdd });
        remaining -= toAdd;
    }

    return remaining; // > 0 seulement si l'inventaire s'est retrouvé plein
}

int Inventory::removeItem(const std::string &itemId, int quantity)
{
    int remaining = quantity;
    int removed = 0;

    for (auto &slot : m_slots) {
        if (remaining <= 0) {
            break;
        }
        if (slot.itemId != itemId) {
            continue;
        }
        const int toRemove = std::min(slot.quantity, remaining);
        slot.quantity -= toRemove;
        remaining -= toRemove;
        removed += toRemove;
    }

    // Nettoyage : supprimer les slots vidés pour ne pas laisser de trous.
    m_slots.erase(
        std::remove_if(m_slots.begin(), m_slots.end(),
                        [](const InventorySlot &s) { return s.isEmpty(); }),
        m_slots.end());

    return removed;
}

} // namespace core
