#include "MainWindow.h"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "HudWidget.h"
#include "screens/BaseScreen.h"
#include "screens/CombatScreen.h"
#include "screens/ExplorationScreen.h"
#include "screens/InventoryScreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_hud(new HudWidget(this))
    , m_screens(new QStackedWidget(this))
    , m_explorationScreen(new ExplorationScreen(this))
    , m_combatScreen(new CombatScreen(this))
    , m_inventoryScreen(new InventoryScreen(this))
    , m_baseScreen(new BaseScreen(this))
{
    setWindowTitle("Rolling Shelter");
    resize(1024, 768);

    m_screens->addWidget(m_explorationScreen);
    m_screens->addWidget(m_combatScreen);
    m_screens->addWidget(m_inventoryScreen);
    m_screens->addWidget(m_baseScreen);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);
    layout->addWidget(m_hud);
    layout->addWidget(m_screens);
    setCentralWidget(central);

    showScreen(GameScreen::Exploration);
}

void MainWindow::showScreen(GameScreen screen)
{
    switch (screen) {
    case GameScreen::Exploration:
        m_screens->setCurrentWidget(m_explorationScreen);
        break;
    case GameScreen::Combat:
        m_screens->setCurrentWidget(m_combatScreen);
        break;
    case GameScreen::Inventory:
        m_screens->setCurrentWidget(m_inventoryScreen);
        break;
    case GameScreen::Base:
        m_screens->setCurrentWidget(m_baseScreen);
        break;
    }
}
