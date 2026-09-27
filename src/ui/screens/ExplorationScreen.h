#pragma once

#include <QString>
#include <QWidget>

#include "core/Adventure.h"

class QLabel;
class QPushButton;
class QVBoxLayout;

// Écran principal : représente le lieu où se trouve le joueur.
//
// - Mode Hangar : repos, craft (à venir), départ en exploration. Le repos
//   n'est disponible que dans ce mode -- impossible de se reposer en
//   pleine aventure.
// - Mode Adventure : affiche le lieu courant de l'aventure et ses options,
//   plus l'action "Rentrer au hangar" toujours disponible.
class ExplorationScreen : public QWidget
{
    Q_OBJECT

public:
    enum class Mode { Hangar, Adventure };

    explicit ExplorationScreen(QWidget *parent = nullptr);

public slots:
    void showHangar();
    void showAdventureStep(const core::AdventureStep &step);

signals:
    void restRequested();
    void endPeriodRequested();
    void leaveHangarRequested();
    void returnToHangarRequested();
    // Émis quand le joueur choisit une option à un lieu de l'aventure.
    void adventureOptionSelected(QString optionId);

private:
    void rebuildOptionButtons(const std::vector<core::AdventureOption> &options);
    void clearOptionButtons();

    Mode m_mode = Mode::Hangar;

    QLabel *m_locationLabel;
    QLabel *m_locationImage;
    QVBoxLayout *m_optionsLayout;

    QPushButton *m_restButton;
    QPushButton *m_craftButton;
    QPushButton *m_leaveHangarButton;
    QPushButton *m_endPeriodButton;
    QPushButton *m_returnToHangarButton;
};
