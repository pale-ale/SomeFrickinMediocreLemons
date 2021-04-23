#pragma once

struct CardSelectionInfo{
    bool selfBattlefield = false;
    bool enemyBattlefield = true;
    bool selfHand = false;
    bool enemyHand = false;
    bool canAttackHero = true;
    bool canAttackHeroDirectly = false;
    int maxCompleteSelectionCount = 1;
    int minCompleteSelecitonCount = 1;
    int minRequiredTargetCount = 1;
};