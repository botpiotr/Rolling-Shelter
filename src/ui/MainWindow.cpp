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
    , m_playerState()
    , m_playerInventory(20)
    , m_vehicleInventory(std::nullopt)
    , m_itemDatabase(core::defaultTestItems())
    , m_atHangar(true)
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

    connect(m_explorationScreen, &ExplorationScreen::restRequested,
            this, &MainWindow::onRestRequested);
    connect(m_explorationScreen, &ExplorationScreen::endPeriodRequested,
            this, &MainWindow::onEndPeriodRequested);
    connect(m_explorationScreen, &ExplorationScreen::toggleLocationRequested,
            this, &MainWindow::onToggleLocationRequested);

    connect(m_hud, &HudWidget::playerInventoryRequested,
            this, &MainWindow::onPlayerInventoryRequested);
    connect(m_hud, &HudWidget::vehicleInventoryRequested,
            this, &MainWindow::onVehicleInventoryRequested);

    connect(m_inventoryScreen, &InventoryScreen::actionRequested,
            this, &MainWindow::onInventoryActionRequested);
    connect(m_inventoryScreen, &InventoryScreen::transferRequested,
            this, &MainWindow::onInventoryTransferRequested);

    // Quelques objets de départ pour tester le système (provisoire).
    if (const auto bois = m_itemDatabase.find("bois")) {
        m_playerInventory.addItem(*bois, 5);
    }
    if (const auto ration = m_itemDatabase.find("ration")) {
        m_playerInventory.addItem(*ration, 2);
    }
    if (const auto metal = m_itemDatabase.find("metal")) {
        m_vehicleInventory.addItem(*metal, 30);
    }

    m_explorationScreen->setAtHangar(m_atHangar);
    m_hud->setVehicleInventoryEnabled(m_atHangar);

    showScreen(GameScreen::Exploration);
    refreshHud();
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

void MainWindow::onRestRequested()
{
    // Valeurs provisoires (à équilibrer plus tard) : se reposer récupère
    // de la stamina et réduit la fatigue accumulée.
    m_playerState.stamina().add(20);
    m_playerState.fatigue().add(-10);
    refreshHud();
}

void MainWindow::onEndPeriodRequested()
{
    // Dégradation naturelle de la période (provisoire) : soif/faim baissent,
    // la pollution ambiante augmente légèrement (thématique choisie pour le
    // prototype), puis les règles de seuil s'appliquent.
    m_playerState.thirst().add(-15);
    m_playerState.hunger().add(-15);
    m_playerState.pollution().add(5);

    m_playerState.applyThresholdRules(core::defaultThresholdRules());

    refreshHud();
}

void MainWindow::onToggleLocationRequested()
{
    // Provisoire : bascule un simple booléen. Sera remplacé par un vrai
    // déplacement entre lieux une fois le système de lieux en place.
    m_atHangar = !m_atHangar;

    m_explorationScreen->setAtHangar(m_atHangar);
    m_hud->setVehicleInventoryEnabled(m_atHangar);

    // Si le joueur quitte le hangar pendant qu'il consultait l'inventaire
    // du véhicule, on revient à l'écran d'exploration pour éviter un état
    // incohérent (véhicule affiché alors qu'il n'est plus accessible).
    if (!m_atHangar && m_screens->currentWidget() == m_inventoryScreen) {
        showScreen(GameScreen::Exploration);
    }
}

void MainWindow::onPlayerInventoryRequested()
{
    m_inventoryScreen->configure(InventoryScreen::Mode::PlayerOnly,
                                 &m_playerInventory, nullptr, &m_itemDatabase);
    m_inventoryScreen->refresh();
    showScreen(GameScreen::Inventory);
}

void MainWindow::onVehicleInventoryRequested()
{
    if (!m_atHangar) {
        return; // le bouton HUD est désactivé dans ce cas, sécurité en plus
    }
    m_inventoryScreen->configure(InventoryScreen::Mode::Hangar,
                                 &m_playerInventory, &m_vehicleInventory, &m_itemDatabase);
    m_inventoryScreen->refresh();
    showScreen(GameScreen::Inventory);
}

void MainWindow::onInventoryActionRequested(InventoryOwner owner, QString itemId, QString action)
{
    core::Inventory &inventory =
        (owner == InventoryOwner::Player) ? m_playerInventory : m_vehicleInventory;
    const std::string id = itemId.toStdString();
    const auto itemDef = m_itemDatabase.find(id);

    if (action == "jeter") {
        inventory.removeItem(id, 1);
    } else if (action == "consommer" && itemDef && itemDef->consumable) {
        inventory.removeItem(id, 1);
        if (itemDef->hungerRestore > 0) {
            m_playerState.hunger().add(itemDef->hungerRestore);
        }
        if (itemDef->thirstRestore > 0) {
            m_playerState.thirst().add(itemDef->thirstRestore);
        }
    } else if (action == "utiliser" || action == "reparer" || action == "assembler") {
        // TODO : logique réelle à brancher plus tard (combat, tech tree...).
        // Pour l'instant, ces actions ne font rien côté données.
    }

    m_inventoryScreen->refresh();
    refreshHud();
}

void MainWindow::onInventoryTransferRequested(InventoryOwner from, QString itemId)
{
    if (!m_atHangar) {
        return; // le transfert n'a de sens qu'au hangar
    }

    core::Inventory &source =
        (from == InventoryOwner::Player) ? m_playerInventory : m_vehicleInventory;
    core::Inventory &destination =
        (from == InventoryOwner::Player) ? m_vehicleInventory : m_playerInventory;

    const std::string id = itemId.toStdString();
    const auto itemDef = m_itemDatabase.find(id);
    if (!itemDef) {
        return;
    }

    const int removed = source.removeItem(id, 1);
    if (removed <= 0) {
        return;
    }

    const int leftover = destination.addItem(*itemDef, removed);
    if (leftover > 0) {
        // La destination est pleine (cas possible seulement pour le sac
        // joueur, 20 cases) : on rend l'objet à la source.
        source.addItem(*itemDef, leftover);
    }

    m_inventoryScreen->refresh();
}

void MainWindow::refreshHud()
{
    m_hud->updateStamina(m_playerState.stamina().value());
    m_hud->updateFatigue(m_playerState.fatigue().value());
    m_hud->updatePollution(m_playerState.pollution().value());
    m_hud->updateThirst(m_playerState.thirst().value());
    m_hud->updateHunger(m_playerState.hunger().value());

    const QString healthText =
        m_playerState.healthState() == core::HealthState::Malade
            ? QString("Malade (%1)").arg(QString::fromStdString(m_playerState.diseaseName()))
            : (m_playerState.healthState() == core::HealthState::Epuise
                   ? "Épuisé"
                   : "Bien portant");
    m_hud->updateHealthState(healthText);

    const QString moralText = [this] {
        switch (m_playerState.moralState()) {
        case core::MoralState::Motive: return QString("Motivé");
        case core::MoralState::Nerveux: return QString("Nerveux");
        case core::MoralState::Triste: return QString("Triste");
        case core::MoralState::Epuise: return QString("Épuisé");
        case core::MoralState::Neutre:
        default: return QString("Neutre");
        }
    }();
    m_hud->updateMoralState(moralText);
}
