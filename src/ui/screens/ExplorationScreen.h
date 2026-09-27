#pragma once

#include <QWidget>

// Écran principal : représente le lieu où se trouve le joueur. Au hangar :
// repos, craft (à venir), départ en exploration. Actions d'exploration
// (sous-étapes, lieux...) à venir avec le système de lieux.
class ExplorationScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ExplorationScreen(QWidget *parent = nullptr);

public slots:
    // Met à jour le libellé du bouton de bascule et l'état affiché.
    void setAtHangar(bool atHangar);

signals:
    void restRequested();
    void endPeriodRequested();
    // Bascule hangar <-> exploration. Provisoire : en attendant un vrai
    // système de lieux/déplacement, sert juste à tester la logique de
    // visibilité de l'inventaire véhicule.
    void toggleLocationRequested();

private:
    class QLabel *m_locationLabel;
    class QPushButton *m_toggleLocationButton;
};
