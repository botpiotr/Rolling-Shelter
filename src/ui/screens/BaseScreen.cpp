#include "BaseScreen.h"

#include <QLabel>
#include <QVBoxLayout>

BaseScreen::BaseScreen(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    auto *title = new QLabel("Base (camion) - à venir");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
}
