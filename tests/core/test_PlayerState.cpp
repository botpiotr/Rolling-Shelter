#include <gtest/gtest.h>

#include "core/PlayerState.h"

using namespace core;

TEST(Gauge, ClampsToMaxOnConstruction)
{
    Gauge g(150, 100);
    EXPECT_EQ(g.value(), 100);
}

TEST(Gauge, ClampsToZero)
{
    Gauge g(10, 100);
    g.add(-50);
    EXPECT_EQ(g.value(), 0);
}

TEST(Gauge, PercentIsComputedFromMax)
{
    Gauge g(25, 100);
    EXPECT_EQ(g.percent(), 25);
}

TEST(PlayerState, StartsAtFullSurvivalGauges)
{
    PlayerState state;
    EXPECT_EQ(state.stamina().percent(), 100);
    EXPECT_EQ(state.thirst().percent(), 100);
    EXPECT_EQ(state.hunger().percent(), 100);
    EXPECT_EQ(state.fatigue().percent(), 0);
    EXPECT_EQ(state.pollution().percent(), 0);
}

TEST(PlayerState, DefaultStatesAreNeutral)
{
    PlayerState state;
    EXPECT_EQ(state.healthState(), HealthState::BienPortant);
    EXPECT_EQ(state.moralState(), MoralState::Neutre);
    EXPECT_TRUE(state.diseaseName().empty());
}

TEST(PlayerState, ThresholdRuleAppliesMalusWhenBelowThreshold)
{
    PlayerState state;
    state.thirst().set(10); // 10% < seuil de 20%

    state.applyThresholdRules(defaultThresholdRules());

    EXPECT_EQ(state.stamina().value(), 99); // -1 appliqué une fois pour la soif
}

TEST(PlayerState, ThresholdRuleDoesNotApplyWhenAboveThreshold)
{
    PlayerState state;
    state.thirst().set(50); // 50% > seuil de 20%

    state.applyThresholdRules(defaultThresholdRules());

    EXPECT_EQ(state.stamina().value(), 100); // rien n'a bougé
}

TEST(PlayerState, MultipleThresholdsStackTheirEffects)
{
    PlayerState state;
    state.thirst().set(5);   // sous le seuil
    state.hunger().set(5);   // sous le seuil aussi

    state.applyThresholdRules(defaultThresholdRules());

    EXPECT_EQ(state.stamina().value(), 98); // -1 soif, -1 faim
}

TEST(PlayerState, SettingDiseaseNameSwitchesHealthStateToMalade)
{
    PlayerState state;
    state.setDiseaseName("Grippe");

    EXPECT_EQ(state.healthState(), HealthState::Malade);
    EXPECT_EQ(state.diseaseName(), "Grippe");
}

TEST(PlayerState, ClearingHealthStateClearsDiseaseName)
{
    PlayerState state;
    state.setDiseaseName("Grippe");
    state.setHealthState(HealthState::BienPortant);

    EXPECT_TRUE(state.diseaseName().empty());
}

TEST(PlayerState, MotiveReducesStaminaCostAndIllnessChance)
{
    PlayerState state;
    state.setMoralState(MoralState::Motive);

    EXPECT_LT(state.staminaCostModifier(), 1.0);
    EXPECT_LT(state.illnessChanceModifier(), 1.0);
}

TEST(PlayerState, EpuiseBlocksExploreAction)
{
    PlayerState state;
    state.setMoralState(MoralState::Epuise);

    EXPECT_TRUE(state.isActionBlocked("explore"));
    EXPECT_FALSE(state.isActionBlocked("rest"));
}

TEST(PlayerState, NeutralMoralHasNoModifiers)
{
    PlayerState state;

    EXPECT_DOUBLE_EQ(state.staminaCostModifier(), 1.0);
    EXPECT_DOUBLE_EQ(state.illnessChanceModifier(), 1.0);
    EXPECT_DOUBLE_EQ(state.actionSuccessModifier(), 1.0);
}
