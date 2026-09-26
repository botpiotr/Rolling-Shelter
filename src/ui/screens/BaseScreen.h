#pragma once

#include <QWidget>

// Gestion des emplacements du camion (nourriture, recherche, craft,
// spécifiques). Pour l'instant : placeholder.
class BaseScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BaseScreen(QWidget *parent = nullptr);
};
