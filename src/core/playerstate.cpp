#include "PlayerState.h"

#include <algorithm>

namespace core {

// --- Gauge ---

Gauge::Gauge(int initialValue, int maxValue)
    : m_value(std::clamp(initialValue, 0, maxValue))
    , m_maxValue(maxValue)
{
}

int Gauge::value() const
{
    return m_value;
}

int Gauge::maxValue() const
{
    return m_maxValue;
}

int Gauge::percent() const
{
    if (m_maxValue <= 0) {
        return 0;
    }
    return (m_value * 100) / m_maxValue;
}

void Gauge::set(int value)
{
    m_value = std::clamp(value, 0, m_maxValue);
}

void Gauge::add(int delta)
{
    set(m_value + delta);
}

// --- Règles de seuil par défaut (provisoire, à équilibrer) ---

std::vector<ThresholdRule> defaultThresholdRules()
{
    return {
            { "soif", 20, "stamina", -1 },
            { "faim", 20, "stamina", -1 },
            { "fatigue", 80, "stamina", -1 }, // fatigue haute = moins de stamina
            { "pollution", 70, "stamina", -1 },
            };
}

// --- PlayerState ---

PlayerState::PlayerState()
    : m_stamina(100, 100)
    , m_fatigue(0, 100)
    , m_pollution(0, 100)
    , m_thirst(100, 100)
    , m_hunger(100, 100)
    , m_healthState(HealthState::BienPortant)
    , m_diseaseName()
    , m_moralState(MoralState::Neutre)
{
}

Gauge &PlayerState::stamina() { return m_stamina; }
Gauge &PlayerState::fatigue() { return m_fatigue; }
Gauge &PlayerState::pollution() { return m_pollution; }
Gauge &PlayerState::thirst() { return m_thirst; }
Gauge &PlayerState::hunger() { return m_hunger; }

const Gauge &PlayerState::stamina() const { return m_stamina; }
const Gauge &PlayerState::fatigue() const { return m_fatigue; }
const Gauge &PlayerState::pollution() const { return m_pollution; }
const Gauge &PlayerState::thirst() const { return m_thirst; }
const Gauge &PlayerState::hunger() const { return m_hunger; }

HealthState PlayerState::healthState() const
{
    return m_healthState;
}

void PlayerState::setHealthState(HealthState state)
{
    m_healthState = state;
    if (state != HealthState::Malade) {
        m_diseaseName.clear();
    }
}

const std::string &PlayerState::diseaseName() const
{
    return m_diseaseName;
}

void PlayerState::setDiseaseName(const std::string &name)
{
    m_diseaseName = name;
    if (!name.empty()) {
        m_healthState = HealthState::Malade;
    }
}

MoralState PlayerState::moralState() const
{
    return m_moralState;
}

void PlayerState::setMoralState(MoralState state)
{
    m_moralState = state;
}

double PlayerState::staminaCostModifier() const
{
    switch (m_moralState) {
    case MoralState::Motive:
        return 0.9; // -10% de coût en stamina
    case MoralState::Triste:
        return 1.1; // +10% de coût en stamina
    default:
        return 1.0;
    }
}

double PlayerState::illnessChanceModifier() const
{
    switch (m_moralState) {
    case MoralState::Motive:
        return 0.8; // -20% de chance de tomber malade
    default:
        return 1.0;
    }
}

double PlayerState::actionSuccessModifier() const
{
    switch (m_moralState) {
    case MoralState::Triste:
        return 0.9; // -10% de réussite aux tests
    default:
        return 1.0;
    }
}

bool PlayerState::isActionBlocked(const std::string &actionId) const
{
    // Épuisé bloque l'exploration (trop risqué sans énergie).
    if (m_moralState == MoralState::Epuise && actionId == "explore") {
        return true;
    }
    return false;
}

void PlayerState::applyThresholdRules(const std::vector<ThresholdRule> &rules)
{
    for (const auto &rule : rules) {
        Gauge *watched = gaugeByName(rule.watchedGauge);
        Gauge *affected = gaugeByName(rule.affectedGauge);
        if (!watched || !affected) {
            continue; // nom de jauge inconnu : on ignore silencieusement
        }
        if (watched->percent() < rule.threshold) {
            affected->add(rule.effectDelta);
        }
    }
}

Gauge *PlayerState::gaugeByName(const std::string &name)
{
    if (name == "stamina") return &m_stamina;
    if (name == "fatigue") return &m_fatigue;
    if (name == "pollution") return &m_pollution;
    if (name == "soif") return &m_thirst;
    if (name == "faim") return &m_hunger;
    return nullptr;
}

} // namespace core
