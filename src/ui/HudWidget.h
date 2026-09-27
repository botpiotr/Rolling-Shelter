#pragma once

#include <QWidget>

class QLabel;
class QPushButton;

// Barre d'indicateurs globaux, toujours visible en haut de la fenêtre.
// Contient aussi les accès rapides aux inventaires : le sac du joueur est
// toujours accessible, le véhicule seulement au hangar.
class HudWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HudWidget(QWidget *parent = nullptr);

public slots:
    void updateStamina(int value);
    void updateFatigue(int value);
    void updatePollution(int value);
    void updateThirst(int value);
    void updateHunger(int value);
    void updateHealthState(const QString &state);
    void updateMoralState(const QString &state);

    // Le bouton véhicule n'est activé que quand le joueur est au hangar.
    void setVehicleInventoryEnabled(bool enabled);

signals:
    void playerInventoryRequested();
    void vehicleInventoryRequested();

private:
    QLabel *m_staminaLabel;
    QLabel *m_fatigueLabel;
    QLabel *m_pollutionLabel;
    QLabel *m_thirstLabel;
    QLabel *m_hungerLabel;
    QLabel *m_healthLabel;
    QLabel *m_moralLabel;

    QPushButton *m_playerInventoryButton;
    QPushButton *m_vehicleInventoryButton;
};
