#include "InventoryScreen.h"

#include <QLabel>
#include <QVBoxLayout>

InventoryScreen::InventoryScreen(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    auto *title = new QLabel("Inventaire - à venir");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
}
