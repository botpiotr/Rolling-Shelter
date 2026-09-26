#pragma once

#include <QWidget>

// Écran de combat tour par tour : attaquer / fuir / intimider,
// utilisation d'objets permanents/consommables. Pour l'instant : placeholder.
class CombatScreen : public QWidget
{
    Q_OBJECT

public:
    explicit CombatScreen(QWidget *parent = nullptr);
};
