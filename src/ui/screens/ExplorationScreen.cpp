#include "ExplorationScreen.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "core/Location.h"

ExplorationScreen::ExplorationScreen(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);

    m_locationLabel = new QLabel();
    m_locationLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_locationLabel);

    auto *restButton = new QPushButton("Se reposer");
    connect(restButton, &QPushButton::clicked,
            this, &ExplorationScreen::restRequested);
    layout->addWidget(restButton);

    auto *craftButton = new QPushButton("Craft");
    craftButton->setEnabled(false);
    craftButton->setToolTip("Nécessite le tech tree (à venir)");
    layout->addWidget(craftButton);

    m_toggleLocationButton = new QPushButton();
    connect(m_toggleLocationButton, &QPushButton::clicked,
            this, &ExplorationScreen::toggleLocationRequested);
    layout->addWidget(m_toggleLocationButton);

    auto *endPeriodButton = new QPushButton("Terminer la période");
    connect(endPeriodButton, &QPushButton::clicked,
            this, &ExplorationScreen::endPeriodRequested);
    layout->addWidget(endPeriodButton);

    layout->addStretch();

    setAtHangar(true);
}

void ExplorationScreen::setAtHangar(bool atHangar)
{
    const QString hangarName = QString::fromStdString(core::kHangarLocation.name);
    m_locationLabel->setText(atHangar
                                 ? QString("Vous êtes à : %1").arg(hangarName)
                                 : "Vous êtes en exploration");
    m_toggleLocationButton->setText(atHangar ? "Partir en exploration" : "Revenir au hangar");
}
