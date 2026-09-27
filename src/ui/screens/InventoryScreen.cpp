#include "InventoryScreen.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLayoutItem>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

namespace {
// Vide un layout de tous ses widgets/enfants avant reconstruction.
void clearLayout(QLayout *layout)
{
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}
}

InventoryScreen::InventoryScreen(QWidget *parent)
    : QWidget(parent)
{
    auto *outerLayout = new QVBoxLayout(this);

    auto *backButton = new QPushButton("< Retour");
    connect(backButton, &QPushButton::clicked, this, &InventoryScreen::backRequested);
    outerLayout->addWidget(backButton);

    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    auto *content = new QWidget;
    m_rootLayout = new QVBoxLayout(content);
    m_rootLayout->addStretch();

    scrollArea->setWidget(content);
    outerLayout->addWidget(scrollArea);
}

void InventoryScreen::configure(Mode mode,
                                core::Inventory *playerInventory,
                                core::Inventory *vehicleInventory,
                                const core::ItemDatabase *itemDatabase)
{
    m_mode = mode;
    m_playerInventory = playerInventory;
    m_vehicleInventory = vehicleInventory;
    m_itemDatabase = itemDatabase;
}

void InventoryScreen::refresh()
{
    clearLayout(m_rootLayout);

    rebuildSection(m_rootLayout, "Sac (joueur)", core::InventoryOwner::Player,
                   m_playerInventory, m_mode == Mode::Hangar);

    if (m_mode == Mode::Hangar) {
        rebuildSection(m_rootLayout, "Véhicule", core::InventoryOwner::Vehicle,
                       m_vehicleInventory, true);
    }

    m_rootLayout->addStretch();
}

void InventoryScreen::rebuildSection(QVBoxLayout *parentLayout, const QString &title,
                                     core::InventoryOwner owner, core::Inventory *inventory,
                                     bool showTransferButton)
{
    auto *sectionTitle = new QLabel(title);
    sectionTitle->setStyleSheet("font-weight: bold;");
    parentLayout->addWidget(sectionTitle);

    if (!inventory || !m_itemDatabase) {
        parentLayout->addWidget(new QLabel("(non disponible)"));
        return;
    }

    if (inventory->InventorySlots().empty()) {
        parentLayout->addWidget(new QLabel("(vide)"));
    }

    for (const auto &slot : inventory->InventorySlots()) {
        const auto itemDef = m_itemDatabase->find(slot.itemId);
        const QString displayName = itemDef
                                        ? QString::fromStdString(itemDef->name)
                                        : QString::fromStdString(slot.itemId);

        auto *row = new QWidget;
        auto *rowLayout = new QHBoxLayout(row);
        rowLayout->setContentsMargins(0, 0, 0, 0);

        rowLayout->addWidget(new QLabel(QString("%1 x%2").arg(displayName).arg(slot.quantity)));

        const QString itemId = QString::fromStdString(slot.itemId);

        auto addActionButton = [&](const QString &label, const QString &action) {
            auto *btn = new QPushButton(label);
            connect(btn, &QPushButton::clicked, this, [this, owner, itemId, action] {
                emit actionRequested(owner, itemId, action);
            });
            rowLayout->addWidget(btn);
        };

        if (itemDef && itemDef->consumable) {
            addActionButton("Consommer", "consommer");
        }
        if (itemDef && itemDef->usable) {
            addActionButton("Utiliser", "utiliser");
        }
        if (itemDef && itemDef->repairable) {
            addActionButton("Réparer", "reparer");
        }
        if (itemDef && itemDef->assemblable) {
            addActionButton("Assembler", "assembler");
        }
        addActionButton("Jeter", "jeter");

        if (showTransferButton) {
            const QString transferLabel = owner == core::InventoryOwner::Player ? "Déposer" : "Prendre";
            auto *transferBtn = new QPushButton(transferLabel);
            connect(transferBtn, &QPushButton::clicked, this, [this, owner, itemId] {
                emit transferRequested(owner, itemId);
            });
            rowLayout->addWidget(transferBtn);
        }

        rowLayout->addStretch();
        parentLayout->addWidget(row);
    }
}
