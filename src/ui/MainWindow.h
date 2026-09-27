#pragma once

#include <QMainWindow>

#include "screens/GameScreen.h"
#include "core/InventoryOwner.h"
#include "core/Inventory.h"
#include "core/ItemDatabase.h"
#include "core/PlayerState.h"

class QStackedWidget;
class HudWidget;
class ExplorationScreen;
class CombatScreen;
class InventoryScreen;
class BaseScreen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    // Change l'écran affiché dans la zone centrale. Le HUD reste visible
    // en permanence, peu importe l'écran actif.
    void showScreen(GameScreen screen);

private slots:
    void onRestRequested();
    void onEndPeriodRequested();
    void onToggleLocationRequested();

    void onPlayerInventoryRequested();
    void onVehicleInventoryRequested();

    void onInventoryActionRequested(InventoryOwner owner, QString itemId, QString action);
    void onInventoryTransferRequested(InventoryOwner from, QString itemId);

private:
    // Pousse l'état actuel de m_playerState vers le HUD. À appeler après
    // toute action qui modifie l'état du joueur.
    void refreshHud();

    core::PlayerState m_playerState;
    core::Inventory m_playerInventory;  // capacité limitée (20)
    core::Inventory m_vehicleInventory; // illimité
    core::ItemDatabase m_itemDatabase;

    bool m_atHangar = true; // seul endroit où le véhicule est accessible

    HudWidget *m_hud;
    QStackedWidget *m_screens;

    ExplorationScreen *m_explorationScreen;
    CombatScreen *m_combatScreen;
    InventoryScreen *m_inventoryScreen;
    BaseScreen *m_baseScreen;
};
