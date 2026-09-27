#pragma once

#include <QString>
#include <QWidget>

#include "core/InventoryOwner.h"
#include "core/Inventory.h"
#include "core/ItemDatabase.h"

class QVBoxLayout;

// Affiche un ou deux inventaires (joueur seul, ou joueur + véhicule côte à
// côte quand on est au hangar), avec les actions disponibles par objet.
class InventoryScreen : public QWidget
{
    Q_OBJECT

public:
    enum class Mode {
        PlayerOnly, // ailleurs qu'au hangar : seul le sac du joueur est visible
        Hangar      // au hangar : joueur + véhicule, avec transfert entre les deux
    };

    explicit InventoryScreen(QWidget *parent = nullptr);

    // À appeler avant refresh() (et à chaque fois que les pointeurs ou le
    // mode changent). Les pointeurs restent la propriété de l'appelant.
    void configure(Mode mode,
                   core::Inventory *playerInventory,
                   core::Inventory *vehicleInventory,
                   const core::ItemDatabase *itemDatabase);

    // Reconstruit l'affichage à partir de l'état actuel des inventaires.
    void refresh();

signals:
    // action ∈ {"jeter", "consommer", "utiliser", "reparer", "assembler"}
    void actionRequested(InventoryOwner owner, QString itemId, QString action);
    // Déplace 1 unité de l'objet depuis `from` vers l'autre inventaire.
    void transferRequested(InventoryOwner from, QString itemId);

private:
    void rebuildSection(QVBoxLayout *parentLayout, const QString &title,
                        InventoryOwner owner, core::Inventory *inventory,
                        bool showTransferButton);

    Mode m_mode = Mode::PlayerOnly;
    core::Inventory *m_playerInventory = nullptr;
    core::Inventory *m_vehicleInventory = nullptr;
    const core::ItemDatabase *m_itemDatabase = nullptr;

    QVBoxLayout *m_rootLayout;
};
