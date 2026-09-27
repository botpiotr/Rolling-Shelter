#include "Adventure.h"

namespace core {

std::vector<AdventureStep> defaultTestAdventure()
{
    return {
            {
                Location{ "champs", "Campagne - Champs abandonnés", "" },
                {
                 { "fouiller", "Fouiller les environs" },
                 { "avancer", "Continuer prudemment" },
                 }
            },
            {
                Location{ "ferme", "Campagne - Ferme isolée", "" },
                {
                 { "fouiller", "Fouiller la ferme" },
                 { "avancer", "Continuer prudemment" },
                 }
            },
            {
                Location{ "route", "Campagne - Route déserte", "" },
                {
                 { "fouiller", "Inspecter les véhicules abandonnés" },
                 { "avancer", "Continuer prudemment" },
                 }
            },
            };
}

} // namespace core
