# Game Design Document — Game_1

*Jeu d'exploration/survie avec craft*

---

## 1. Pitch & Piliers

**Pitch**

Dans un monde qui s'effondre selon une menace choisie au lancement de la partie (toxicité, chaleur, froid ou submersion), le joueur explore les environs à bord d'un camion-base mobile qu'il doit améliorer et adapter pour survivre à une pression environnementale toujours croissante.

**Thématiques de dégradation (choisies au début d'une partie, interchangeables)**
- Le monde devient de plus en plus pollué/toxique
- Le monde devient de plus en plus chaud et aride
- Le monde devient de plus en plus froid
- Le monde devient de plus en plus humide/pluvieux, jusqu'à submersion des terres émergées

**Piliers**
1. **Dégradation progressive et irréversible** — la menace choisie en début de partie s'aggrave sans retour en arrière possible ; le temps est l'ennemi principal.
2. **Le camion comme refuge évolutif** — pas une base fixe à défendre, mais un véhicule qu'on améliore et qu'on adapte à la menace en cours.
3. **Rejouabilité par la menace** — changer de thématique de dégradation change fondamentalement les défis, le craft utile, et le rythme de la partie.

---

## 2. Boucle de gameplay

Le temps est découpé en **périodes**.

1. **Début de période** : le jeu annonce ce qui va se dégrader/arriver à la période suivante.
2. **Actions du joueur** : le joueur enchaîne plusieurs actions tant qu'il lui reste de la **stamina** :
   - Exploration
   - Repos
   - Craft
   - Recherche
   - Actions débloquées par certaines constructions/améliorations : cultiver (champignons), réparer véhicule/équipement/nettoyer, cuisiner, raffiner, etc.
3. **Déplacement** : changer de lieu fait changer de période et de lieu simultanément.
4. **Fin de période** : l'environnement empire, des malus sont appliqués.

**Exploration (détail)** : une action d'exploration se décompose en plusieurs sous-étapes/choix (déplacement/exploration visuelle d'une petite zone), pas une trouvaille unique directe.

---

## 3. Indicateurs du personnage

| Indicateur | Type | Rôle |
|---|---|---|
| **Stamina** | Jauge | Actions disponibles pendant la période en cours |
| **Fatigue** | Jauge | Accumulation sur plusieurs périodes (repos insuffisant) |
| **Pollution** | Jauge | Contamination liée à la dégradation environnementale |
| **Soif** | Jauge | Classique |
| **Faim** | Jauge | Classique |
| **État de santé** | Qualitatif | Bien portant / Malade (+ nom de la maladie) / Épuisé / etc. |
| **État de moral** | Qualitatif | Motivé / Nerveux / Triste / Épuisé / etc. — effets cachés sur les actions |

**Exemples d'effets cachés du moral** :
- Motivé : +X% de chance d'éviter une dépense d'énergie, -X% de chance de tomber malade
- Nerveux : -récupération pendant la nuit
- Triste : -énergie, -X% de réussite aux tests
- Épuisé : accès bloqué à certaines actions

Le passage sous un certain seuil d'une jauge applique des malus (ex : soif < 20 % → énergie -1). *Détail complet des seuils/malus restant à définir.*

---

## 4. Système de craft

- **Déblocage des recettes** : via un **arbre de progression (tech tree)**, alimenté par des **plans à trouver puis à étudier**.
- **Progression cumulative** : chaque plan débloque une amélioration d'un objet existant, formant une chaîne d'améliorations.
  - *Exemple — filtre à eau* : grille + tuyau → charbon actif → chlore → décantation.
- **Ressources** : mélange de matériaux génériques (bois, métal, tissu...) et de pièces spécifiques rares récupérées telles quelles.
- **Lieu de fabrication** : objet simple → fabricable n'importe où ; objet complexe → nécessite une station dédiée.
- **Structure de l'arbre** : un **tronc commun** (bases universelles) + des **branches spécifiques** selon la thématique de dégradation choisie.

---

## 5. La base mobile (camion)

Le camion est modulable, avec des emplacements dédiés à des constructions :

- 🍲 **Emplacement Nourriture**
- 🔬 **Emplacement Recherche**
- 🔧 **Emplacement Craft**
- ❓ **Emplacement spécifique 1** *(non défini)*
- ❓ **Emplacement spécifique 2** *(non défini)*

**Règles** :
- Certaines constructions sont **mutuellement exclusives** entre elles.
- Certaines constructions sont **nécessaires pour débloquer des crafts spécifiques** (ex : atelier, cuisine).
- Remplacer une construction déjà posée est possible mais entraîne une **forte pénalité** (ressources/temps).
- Nombre/taille exacts des emplacements : à définir plus précisément si besoin.

---

## 6. Exploration & monde

- **Structure spatiale** : carte en **nœuds/lieux discrets**, reliés entre eux (pas de carte ouverte continue).
- **Génération** : la carte de nœuds est **générée aléatoirement à chaque partie**.
- **Irréversibilité** : **pas de retour en arrière** possible sur un lieu déjà exploré.
- **Risque/récompense** : déterminé par le **type de zone** et le **niveau de dégradation globale** — pas par la distance au camion.

### Méta-lieux (régions)

Chaque nœud appartient à une région qui indique au joueur le type de zone à venir :
- 🌾 Campagne
- ⛰️ Montagne
- 🌊 Côtes
- 🌲 Vallée
- 🏙️ Urbain

### Lieux de base (accessibles dès le départ)

| Lieu | Méta-lieu | Bonus | Malus | Marchand |
|---|---|---|---|---|
| Campagne / champs | Campagne | Nourriture ++, calme | Peu de ressources techniques | — |
| Quartier résidentiel / banlieue | Campagne | Ressources variées, équilibré | Rien de spécialisé | Coloc |
| Ville côtière | Côtes | Nourriture/eau ++ | Exposition (submersion précoce) | — |
| Port / entrepôts maritimes | Côtes | Matériaux + pièces mécaniques ++ | Submersion précoce, rouille | Pêcheur |
| Forêt dense | Vallée / Montagne | Bois ++, gibier | Visibilité réduite, risque créatures | — |
| Bunker abandonné | Vallée | Provisions conservées ++ | Piégé, accès difficile, obscurité | — |
| Station-service | Urbain | Carburant/pièces véhicule ++ | Explosif si dégradé | — |
| Centre commercial | Urbain | Nourriture/vêtements/outils ++ | Peu de matériaux bruts, risque pillards ++ | Dealer |
| Casse auto / junkyard | Urbain | Pièces véhicule/métal ++ | Rouille, coupures, peu de nourriture | — |
| Carrière | Montagne | Pierre/matériaux de construction ++ | Terrain accidenté, peu de nourriture | — |
| Camping / refuge de montagne | Montagne | Équipement de survie/abri ++ | Isolé, accès difficile | — |
| Village de montagne | Montagne | Nourriture/eau ++, isolation thermique ++ | Peu de matériaux techniques, habitants hostiles possibles | — |

### Lieux débloquables (prérequis d'équipement/plan)

| Lieu | Méta-lieu | Prérequis | Marchand |
|---|---|---|---|
| Mine | Montagne | Masque à gaz / bouteille O2 | — |
| Station de métro / souterrains | Urbain | Source de lumière fiable | — |
| Hôpital abandonné | Urbain | Protection anti-contamination | — |
| Base militaire | Urbain | Outil de crochetage/effraction | Intendant militaire |
| Centrale électrique | Vallée | Combinaison anti-radiation | — |
| Laboratoire de recherche | Vallée | Accès sécurisé | — |
| Usine de soda | Vallée | — | — |
| École / université | Campagne | — | — |
| Bibliothèque | Urbain | — | — |
| Zoo / réserve naturelle | Campagne | Répulsif/arme contre faune | — |
| Permaculture | Campagne | — | Fermier |

*Bonus/malus des lieux débloquables : à définir (reporté à plus tard).*

*Détail des ressources recherchées/proposées par les marchands : à définir (reporté à plus tard).*

---

## 7. Progression & objectifs

**Objectif de fin de partie** : le jeu a un objectif final clair à atteindre. Plusieurs types possibles, variables selon la partie :
- Atteindre une **zone safe** (survie pure)
- Atteindre une **zone très polluante** pour y livrer un remède (bombe/virus/bactérie)
- Atteindre une **zone de transition** (ex : océan) avec le véhicule préparé en conséquence (plongée, réserve d'air, etc.)

**Structure en sous-étapes** : un objectif peut se décomposer en plusieurs paliers narratifs successifs.
- *Exemple* : Étape 1 — labo → Étape 2 — usine avec machine spécifique → Étape 3 — lieu d'origine de la pollution.

**Méta-progression inter-parties** : certaines rencontres spéciales liées à des lieux précis débloquent du contenu permanent pour les parties suivantes.
- *Exemple* : village côtier + rencontre spéciale → nouveau personnage jouable avec son propre véhicule dès la partie suivante.

**Échec** : en cas de stats critiques trop longtemps, le joueur meurt — game over classique, la partie s'arrête.

---

## 8. Menaces & combat

**Sources de menace** (en plus de la dégradation globale) :
- Environnementale (météo, effets directs de la dégradation)
- Créatures/ennemis hostiles
- Autres survivants / factions humaines

**Système de combat** — simplifié, tour par tour, résolu via **objets/équipement + probabilités** (pas de stats de personnage) :
- **3 actions possibles** : Attaquer / Fuir / Intimider
- **Sans équipement** : ces actions restent possibles mais avec une efficacité faible
- **Objets permanents** (ex : veste de camouflage) : ajoutent un bonus de probabilité de succès sur une ou plusieurs actions
- **Objets consommables** (ex : fumigène) : garantissent la réussite d'une action (100%)
- **But du système** : punir les mauvais choix (mauvais équipement pour la situation) plutôt qu'éliminer systématiquement la menace ; viser de la variété dans les objets et les rencontres

**Évolution de la difficulté** :
- Paliers de dégradation globale (subis, annoncés à l'avance)
- Risques pris par le joueur lui-même (ex : explorer une zone dangereuse pour plus de loot)

---

## 9. Scope du premier prototype

Pour un premier build jouable, scope volontairement réduit :
- **Une seule thématique de dégradation** : pollution
- **Chiffres provisoires** pour coûts d'action et seuils de malus (à équilibrer plus tard via playtests)
- **Craft très simplifié** : 2-3 recettes de test (pas le tech tree complet)
- Lieux de base (12) avec bonus/malus déjà définis, utilisables tels quels
- Pas de combat multi-menaces complexe, pas de méta-progression, pas de multi-objectifs pour cette première version — l'objectif est de valider la boucle de survie de base

---

## Points encore ouverts

- Réaction précise pour chaque type de menace (certaines évitables uniquement, d'autres combattables ?)
- Détail des malus par seuil pour chaque indicateur (au-delà de l'exemple soif < 20 %)
- Liste complète des maladies possibles et leurs effets
- Bonus/malus des lieux débloquables
- Détail des marchands (ressources recherchées/proposées par chacun)
- Fonctionnement précis des emplacements du camion (nombre fixe/extensible, tailles) et définition des 2 emplacements spécifiques
- Contenu complet du tech tree (tronc commun + branches par thématique de dégradation)
- Personnages jouables débloquables (au-delà du principe déjà posé)
