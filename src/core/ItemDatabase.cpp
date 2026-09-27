#include "ItemDatabase.h"

namespace core {

void ItemDatabase::addItem(const Item &item)
{
    m_items[item.id] = item;
}

std::optional<Item> ItemDatabase::find(const std::string &itemId) const
{
    auto it = m_items.find(itemId);
    if (it == m_items.end()) {
        return std::nullopt;
    }
    return it->second;
}

ItemDatabase defaultTestItems()
{
    ItemDatabase db;

    Item bois;
    bois.id = "bois";
    bois.name = "Bois";
    bois.maxStackSize = 99;
    db.addItem(bois);

    Item metal;
    metal.id = "metal";
    metal.name = "Métal";
    metal.maxStackSize = 99;
    db.addItem(metal);

    Item ration;
    ration.id = "ration";
    ration.name = "Ration alimentaire";
    ration.maxStackSize = 10;
    ration.consumable = true;
    ration.hungerRestore = 30;
    db.addItem(ration);

    Item gourde;
    gourde.id = "gourde";
    gourde.name = "Gourde d'eau";
    gourde.maxStackSize = 10;
    gourde.consumable = true;
    gourde.thirstRestore = 30;
    db.addItem(gourde);

    Item outilCasse;
    outilCasse.id = "outil_casse";
    outilCasse.name = "Outil cassé";
    outilCasse.maxStackSize = 5;
    outilCasse.repairable = true;
    db.addItem(outilCasse);

    Item pieceDetachee;
    pieceDetachee.id = "piece_detachee";
    pieceDetachee.name = "Pièce détachée";
    pieceDetachee.maxStackSize = 20;
    pieceDetachee.assemblable = true;
    db.addItem(pieceDetachee);

    Item lampeTorche;
    lampeTorche.id = "lampe_torche";
    lampeTorche.name = "Lampe torche";
    lampeTorche.maxStackSize = 1;
    lampeTorche.usable = true;
    db.addItem(lampeTorche);

    return db;
}

} // namespace core
