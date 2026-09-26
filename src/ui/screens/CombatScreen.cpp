#include "CombatScreen.h"

#include <QLabel>
#include <QVBoxLayout>

CombatScreen::CombatScreen(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    auto *title = new QLabel("Combat - à venir");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
}
