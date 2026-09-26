#include "HudWidget.h"

#include <QHBoxLayout>
#include <QLabel>

namespace {
QLabel *makeIndicatorLabel(const QString &initialText)
{
    auto *label = new QLabel(initialText);
    label->setMinimumWidth(90);
    return label;
}
}

HudWidget::HudWidget(QWidget *parent)
    : QWidget(parent)
    , m_staminaLabel(makeIndicatorLabel("Stamina: -"))
    , m_fatigueLabel(makeIndicatorLabel("Fatigue: -"))
    , m_pollutionLabel(makeIndicatorLabel("Pollution: -"))
    , m_thirstLabel(makeIndicatorLabel("Soif: -"))
    , m_hungerLabel(makeIndicatorLabel("Faim: -"))
    , m_healthLabel(makeIndicatorLabel("Santé: -"))
    , m_moralLabel(makeIndicatorLabel("Moral: -"))
{
    auto *layout = new QHBoxLayout(this);
    layout->addWidget(m_staminaLabel);
    layout->addWidget(m_fatigueLabel);
    layout->addWidget(m_pollutionLabel);
    layout->addWidget(m_thirstLabel);
    layout->addWidget(m_hungerLabel);
    layout->addWidget(m_healthLabel);
    layout->addWidget(m_moralLabel);
    layout->addStretch();
}

void HudWidget::updateStamina(int value)
{
    m_staminaLabel->setText(QString("Stamina: %1").arg(value));
}

void HudWidget::updateFatigue(int value)
{
    m_fatigueLabel->setText(QString("Fatigue: %1").arg(value));
}

void HudWidget::updatePollution(int value)
{
    m_pollutionLabel->setText(QString("Pollution: %1").arg(value));
}

void HudWidget::updateThirst(int value)
{
    m_thirstLabel->setText(QString("Soif: %1").arg(value));
}

void HudWidget::updateHunger(int value)
{
    m_hungerLabel->setText(QString("Faim: %1").arg(value));
}

void HudWidget::updateHealthState(const QString &state)
{
    m_healthLabel->setText(QString("Santé: %1").arg(state));
}

void HudWidget::updateMoralState(const QString &state)
{
    m_moralLabel->setText(QString("Moral: %1").arg(state));
}
