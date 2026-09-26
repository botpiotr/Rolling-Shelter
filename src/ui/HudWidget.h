#pragma once

#include <QWidget>

class QLabel;

// Barre d'indicateurs globaux, toujours visible en haut de la fenêtre.
// Pour l'instant : placeholders statiques. Sera connecté à PlayerState (core)
// une fois cette classe écrite, via des slots publics (updateStamina, etc.)
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

private:
    QLabel *m_staminaLabel;
    QLabel *m_fatigueLabel;
    QLabel *m_pollutionLabel;
    QLabel *m_thirstLabel;
    QLabel *m_hungerLabel;
    QLabel *m_healthLabel;
    QLabel *m_moralLabel;
};
