#pragma once

#include <QWidget>

// Liste des objets possédés (permanents/consommables). Pour l'instant : placeholder.
class InventoryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InventoryScreen(QWidget *parent = nullptr);
};
