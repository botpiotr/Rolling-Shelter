#include "ExplorationScreen.h"

#include <QLabel>
#include <QVBoxLayout>

ExplorationScreen::ExplorationScreen(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    auto *title = new QLabel("Exploration - à venir");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
}
