#pragma once

#include <string>
#include <vector>

namespace core {

// État de santé qualitatif (pas une jauge : un état affiché tel quel).
enum class HealthState {
    BienPortant,
    Malade,
    Epuise
};

// État de moral qualitatif : influence d'autres systèmes via des
// modificateurs cachés (voir PlayerState::staminaCostModifier, etc.)
enum class MoralState {
    Neutre,
    Motive,
    Nerveux,
    Triste,
    Epuise
};

// Une jauge simple, bornée entre 0 et maxValue.
class Gauge {
public:
    explicit Gauge(int initialValue = 100, int maxValue = 100);

    int value() const;
    int maxValue() const;
    int percent() const; // valeur en % du max, pratique pour les seuils

    void set(int value);
    void add(int delta); // delta peut être négatif

private:
    int m_value;
    int m_maxValue;
};

// Règle générique de malus par seuil : si `watchedGauge` passe sous
// `threshold` (en %), applique `effectDelta` sur `affectedGauge`.
// Représenté en donnée plutôt qu'en code pour rester facile à étendre
// (et, plus tard, chargeable depuis un JSON comme le tech tree).
struct ThresholdRule {
    std::string watchedGauge;
    int threshold;
    std::string affectedGauge;
    int effectDelta;
};

// Jeu de règles provisoire pour le prototype (à ajuster/déplacer en
// JSON une fois les vraies valeurs équilibrées via playtests).
std::vector<ThresholdRule> defaultThresholdRules();

class PlayerState {
public:
    PlayerState();

    // Jauges
    Gauge &stamina();
    Gauge &fatigue();
    Gauge &pollution();
    Gauge &thirst();
    Gauge &hunger();

    const Gauge &stamina() const;
    const Gauge &fatigue() const;
    const Gauge &pollution() const;
    const Gauge &thirst() const;
    const Gauge &hunger() const;

    // États qualitatifs
    HealthState healthState() const;
    void setHealthState(HealthState state);

    const std::string &diseaseName() const; // vide si pas malade
    void setDiseaseName(const std::string &name);

    MoralState moralState() const;
    void setMoralState(MoralState state);

    // Modificateurs cachés issus du moral, utilisés par d'autres systèmes
    // (craft, exploration, combat...) sans qu'ils aient à connaître l'état
    // de moral eux-mêmes.
    double staminaCostModifier() const;   // ex: 0.9 = -10% de coût en stamina
    double illnessChanceModifier() const; // ex: 0.8 = -20% de chance de tomber malade

    // Modificateur de réussite aux tests : combine le moral ET l'épuisement
    // (stamina à 0). Toute mécanique qui "teste" une réussite (combat,
    // craft risqué...) doit multiplier sa chance de base par cette valeur.
    double actionSuccessModifier() const; // ex: 0.9 = -10% de réussite aux tests
    bool isActionBlocked(const std::string &actionId) const;

    // Stamina à 0 : le personnage est épuisé, ne peut plus rien tenter
    // efficacement tant qu'il ne s'est pas reposé (uniquement possible au
    // hangar -- géré côté UI/MainWindow, pas ici).
    bool isStaminaDepleted() const;

    // Applique un ensemble de règles de seuil (typiquement en fin de période).
    void applyThresholdRules(const std::vector<ThresholdRule> &rules);

private:
    Gauge m_stamina;
    Gauge m_fatigue;
    Gauge m_pollution;
    Gauge m_thirst;
    Gauge m_hunger;

    HealthState m_healthState;
    std::string m_diseaseName;

    MoralState m_moralState;

    Gauge *gaugeByName(const std::string &name);
};

} // namespace core
