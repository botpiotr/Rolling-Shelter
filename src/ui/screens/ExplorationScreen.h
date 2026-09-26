#pragma once

#include <QWidget>

// Écran principal : lieu actuel, actions disponibles (explorer, repos, craft,
// recherche), sous-étapes d'exploration. Pour l'instant : placeholder.
class ExplorationScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ExplorationScreen(QWidget *parent = nullptr);
};
