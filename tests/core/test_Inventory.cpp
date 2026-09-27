#include <gtest/gtest.h>

#include "core/Inventory.h"
#include "core/Item.h"

using namespace core;

namespace {
const Item kWood{ "bois", "Bois", 99 };
const Item kMetal{ "metal", "Métal", 99 };
const Item kWater{ "eau", "Eau", 99 };
}

TEST(Inventory, StartsEmpty)
{
    Inventory inv(20);
    EXPECT_TRUE(inv.InventorySlots().empty());
    EXPECT_EQ(inv.quantityOf(kWood.id), 0);
}

TEST(Inventory, AddItemCreatesANewSlot)
{
    Inventory inv(20);
    const int leftover = inv.addItem(kWood, 5);

    EXPECT_EQ(leftover, 0);
    ASSERT_EQ(inv.InventorySlots().size(), 1u);
    EXPECT_EQ(inv.InventorySlots()[0].itemId, kWood.id);
    EXPECT_EQ(inv.InventorySlots()[0].quantity, 5);
}

TEST(Inventory, AddingSameItemFillsExistingSlotFirst)
{
    Inventory inv(20);
    inv.addItem(kWood, 5);
    inv.addItem(kWood, 3);

    ASSERT_EQ(inv.InventorySlots().size(), 1u); // toujours une seule case
    EXPECT_EQ(inv.quantityOf(kWood.id), 8);
}

TEST(Inventory, ExceedingStackSizeCreatesASecondSlot)
{
    Inventory inv(20);
    inv.addItem(kWood, 99); // remplit le premier stack (maxStackSize = 99)
    inv.addItem(kWood, 10); // doit créer un second slot

    ASSERT_EQ(inv.InventorySlots().size(), 2u);
    EXPECT_EQ(inv.quantityOf(kWood.id), 109);
}

TEST(Inventory, LimitedInventoryRejectsOverflowWhenFull)
{
    Inventory inv(1); // une seule case possible
    inv.addItem(kWood, 99); // remplit l'unique case

    const int leftover = inv.addItem(kMetal, 10); // item différent, plus de place

    EXPECT_EQ(leftover, 10); // rien n'a pu être ajouté
    EXPECT_EQ(inv.quantityOf(kMetal.id), 0);
    EXPECT_TRUE(inv.isFull());
}

TEST(Inventory, UnlimitedInventoryNeverRejectsItems)
{
    Inventory inv(std::nullopt); // véhicule : illimité
    int leftover = 0;
    for (int i = 0; i < 50; ++i) {
        leftover += inv.addItem(kMetal, 99);
    }

    EXPECT_EQ(leftover, 0);
    EXPECT_FALSE(inv.isFull());
    EXPECT_EQ(inv.quantityOf(kMetal.id), 50 * 99);
}

TEST(Inventory, RemoveItemReducesQuantity)
{
    Inventory inv(20);
    inv.addItem(kWater, 10);

    const int removed = inv.removeItem(kWater.id, 4);

    EXPECT_EQ(removed, 4);
    EXPECT_EQ(inv.quantityOf(kWater.id), 6);
}

TEST(Inventory, RemoveMoreThanOwnedRemovesOnlyWhatExists)
{
    Inventory inv(20);
    inv.addItem(kWater, 3);

    const int removed = inv.removeItem(kWater.id, 10);

    EXPECT_EQ(removed, 3);
    EXPECT_EQ(inv.quantityOf(kWater.id), 0);
}

TEST(Inventory, RemovingAllOfAnItemClearsItsSlot)
{
    Inventory inv(20);
    inv.addItem(kWater, 5);
    inv.removeItem(kWater.id, 5);

    EXPECT_TRUE(inv.InventorySlots().empty()); // le slot vidé est supprimé
}

TEST(Inventory, EachSlotHoldsOnlyOneItemType)
{
    Inventory inv(20);
    inv.addItem(kWood, 5);
    inv.addItem(kMetal, 5);

    ASSERT_EQ(inv.InventorySlots().size(), 2u);
    EXPECT_NE(inv.InventorySlots()[0].itemId, inv.InventorySlots()[1].itemId);
}
