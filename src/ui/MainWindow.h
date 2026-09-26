#pragma once

#include <QMainWindow>

#include "screens/GameScreen.h"

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

private:
    HudWidget *m_hud;
    QStackedWidget *m_screens;

    ExplorationScreen *m_explorationScreen;
    CombatScreen *m_combatScreen;
    InventoryScreen *m_inventoryScreen;
    BaseScreen *m_baseScreen;
};
