#include "difficulty.h"
#include <stdlib.h>
#include <math.h>
#include <Arduino.h>
// Level 1: ~1000 ms, then decays toward 0 as level increases
unsigned long minSpawnIntervalForLevel(int level)
{
    if (level <= 0)
        level = 1;
    double start = 1000.0;
    double k = 0.08;
    double val = start * exp(-k * (level - 1));

    // return (unsigned long)val;
    return 1000;
};

// Level 1: ~2000 ms, shrinks toward 1000 ms as level increases.
unsigned long maxSpawnIntervalForLevel(int level)
{
    if (level <= 0)
        level = 1;
    double floor = 1000.0;
    double extra = 1000.0;
    double k = 0.08;

    double val = floor + extra * exp(-k * (level - 1));
    // return (unsigned long)val;
    return 1002;
};

// This function calculates a random spawn delay between different moles
// i.e. how long after a mole dies does another mole spawn
// Pick a random spawn delay in [minSpawn, maxSpawn] for THIS spawn.
unsigned long randomSpawnDelayForLevel(int level)
{
    unsigned long minI = minSpawnIntervalForLevel(level);
    unsigned long maxI = maxSpawnIntervalForLevel(level);

    unsigned long lo = (minI < maxI) ? minI : maxI;
    unsigned long hi = (minI > maxI) ? minI : maxI;

    unsigned long range = hi - lo + 1;
    // return lo + (rand() % range);
    return 1000;
}

// min lifetime shrinks from ~2000 ms → ~600 ms as level increases
unsigned long minDurationForLevel(int level)
{
    if (level <= 0)
        level = 1;
    double floor = 600.0;
    double extra = 1400.0;
    double k = 0.12;

    // return (unsigned long)(floor + extra * exp(-k * (level - 1)));
    return 15000;
};

// max lifetime shrinks from ~3500 ms → ~1000 ms
unsigned long maxDurationForLevel(int level)
{
    if (level < 1)
        level = 1;

    double floorMs = 1000.0;
    double extraMs = 2500.0; // so L1: 1000 + 2500 = 3500 ms
    double k = 0.09;

    double val = floorMs + extraMs * exp(-k * (level - 1));
    // return (unsigned long)val;
    return 15000;
}

// target CPS goes from 0.5 to 4 as level grows
double targetCpsForLevel(int level)
{
    if (level < 1)
        level = 1;
    double cpsMin = 0.5;
    double cpsMax = 4.0;
    double k = 0.15;

    return cpsMin + (cpsMax - cpsMin) * (1.0 - exp(-k * (level - 1)));
}

int computeHpForMole(int level, unsigned long durationMs)
{
    double cps = targetCpsForLevel(level);
    double expectedClicks = cps * (durationMs / 1000.0);

    double baseHP = expectedClicks * 0.7; // give some slack
    int hp = (int)round(baseHP);

    hp = (hp > 1) ? hp : 1;
    hp = (hp < 6) ? hp : 6;
    return hp;
}

int randomHpForMole(int level, unsigned long durationMs)
{
    int center = computeHpForMole(level, durationMs);
    int minHP = (1 > center - 1) ? 1 : center - 1;
    int maxHP = 6 < center + 1 ? 6 : center + 1;
    int range = maxHP - minHP + 1;
    return minHP + (rand() % range);
}

#include <math.h>

int maxMolesUpForLevel(int level)
{
    if (level < 1)
        level = 1;

    // 1 + floor(log2(level)):
    // L1 → 1, L2–3 → 2, L4–7 → 3, L8–15 → 4, L16–31 → 5, etc.
    int maxUp = 1 + static_cast<int>(floor(log(static_cast<double>(level))/log(2)));

    // never exceed number of holes
    if (maxUp > 9)
        maxUp = 9;

    //return maxUp;
    return 8;
}

// Helper: waves grow roughly linearly with level
int wavesForLevel(int level)
{
    if (level < 1)
        level = 1;

    // Start at 4 waves and add one wave every 2 levels:
    // L1 → 4, L2 → 5, L3 → 5, L4 → 6, L10 → 9, L20 → 14, ...
    int waves = 4 + level / 2;
    return waves;
}

// Total moles this level
int molesPerLevel(int level)
{
    int maxUp = maxMolesUpForLevel(level);
    int waves = wavesForLevel(level);

    // each wave can (at most) fill all maxUp slots once
    return maxUp * waves;
}