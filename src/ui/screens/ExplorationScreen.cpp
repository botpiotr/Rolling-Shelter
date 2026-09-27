#include "ExplorationScreen.h"

#include <QLabel>
#include <QLayoutItem>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

#include "core/Location.h"

namespace {
void clearLayout(QLayout *layout)
{
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}
}

ExplorationScreen::ExplorationScreen(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);

    m_locationLabel = new QLabel();
    m_locationLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_locationLabel);

    m_locationImage = new QLabel();
    m_locationImage->setAlignment(Qt::AlignCenter);
    m_locationImage->setMinimumHeight(200);
    layout->addWidget(m_locationImage);

    // -- Actions du mode Hangar --
    m_restButton = new QPushButton("Se reposer");
    connect(m_restButton, &QPushButton::clicked,
            this, &ExplorationScreen::restRequested);
    layout->addWidget(m_restButton);

    m_craftButton = new QPushButton("Craft");
    m_craftButton->setEnabled(false);
    m_craftButton->setToolTip("Nécessite le tech tree (à venir)");
    layout->addWidget(m_craftButton);

    m_leaveHangarButton = new QPushButton("Partir en exploration");
    connect(m_leaveHangarButton, &QPushButton::clicked,
            this, &ExplorationScreen::leaveHangarRequested);
    layout->addWidget(m_leaveHangarButton);

    m_endPeriodButton = new QPushButton("Terminer la période");
    connect(m_endPeriodButton, &QPushButton::clicked,
            this, &ExplorationScreen::endPeriodRequested);
    layout->addWidget(m_endPeriodButton);

    // -- Actions du mode Adventure --
    auto *optionsContainer = new QWidget();
    m_optionsLayout = new QVBoxLayout(optionsContainer);
    m_optionsLayout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(optionsContainer);

    m_returnToHangarButton = new QPushButton("Rentrer au hangar");
    connect(m_returnToHangarButton, &QPushButton::clicked,
            this, &ExplorationScreen::returnToHangarRequested);
    layout->addWidget(m_returnToHangarButton);

    layout->addStretch();

    showHangar();
}

void ExplorationScreen::showHangar()
{
    m_mode = Mode::Hangar;

    m_locationLabel->setText(QString::fromStdString(core::kHangarLocation.name));
    const QString imagePath = QString::fromStdString(core::kHangarLocation.imageResourcePath);
    m_locationImage->setPixmap(imagePath.isEmpty()
                                   ? QPixmap()
                                   : QPixmap(imagePath).scaledToHeight(200, Qt::SmoothTransformation));

    m_restButton->setVisible(true);
    m_craftButton->setVisible(true);
    m_leaveHangarButton->setVisible(true);
    m_endPeriodButton->setVisible(true);

    clearOptionButtons();
    m_optionsLayout->parentWidget()->setVisible(false);
    m_returnToHangarButton->setVisible(false);
}

void ExplorationScreen::showAdventureStep(const core::AdventureStep &step)
{
    m_mode = Mode::Adventure;

    m_locationLabel->setText(QString::fromStdString(step.location.name));
    const QString imagePath = QString::fromStdString(step.location.imageResourcePath);
    m_locationImage->setPixmap(imagePath.isEmpty()
                                   ? QPixmap()
                                   : QPixmap(imagePath).scaledToHeight(200, Qt::SmoothTransformation));

    // Pas de repos, de craft, ni de départ "hangar->hangar" en pleine
    // aventure -- ces boutons n'appartiennent qu'au mode Hangar.
    m_restButton->setVisible(false);
    m_craftButton->setVisible(false);
    m_leaveHangarButton->setVisible(false);
    m_endPeriodButton->setVisible(false);

    rebuildOptionButtons(step.options);
    m_optionsLayout->parentWidget()->setVisible(true);
    m_returnToHangarButton->setVisible(true);
}

void ExplorationScreen::clearOptionButtons()
{
    clearLayout(m_optionsLayout);
}

void ExplorationScreen::rebuildOptionButtons(const std::vector<core::AdventureOption> &options)
{
    clearOptionButtons();
    for (const auto &option : options) {
        const QString optionId = QString::fromStdString(option.id);
        auto *btn = new QPushButton(QString::fromStdString(option.label));
        connect(btn, &QPushButton::clicked, this, [this, optionId] {
            emit adventureOptionSelected(optionId);
        });
        m_optionsLayout->addWidget(btn);
    }
}
