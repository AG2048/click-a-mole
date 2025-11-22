#ifndef DIFFICULTY_H
#define DIFFICULTY_H

// how long after a mole is dead can another mole reappear at the same spot
const unsigned long MOLE_RESPAWN_COOLDOWN_MS = 2000; // or 700, or whatever fits the animation

int maxMolesUpForLevel(int level); // calculates the max number of moles that can be up simultaneously for a given level
int wavesForLevel(int level);      // calculates the number of waves for a given level
int molesPerLevel(int level);      // calculates the total number of moles for a given level (wave * maxMolesUp)

unsigned long minSpawnIntervalForLevel(int level); // calculates the minimum spawn interval for a given level
unsigned long maxSpawnIntervalForLevel(int level); // calculates the maximum spawn interval for a given level

// randomized spawn delay between death of a mole and spawn of next mole
// calculated using the interval [minSpawnInterval, maxSpawnInterval]
unsigned long randomSpawnDelayForLevel(int level);

unsigned long minDurationForLevel(int level); // calculates the minimum duration a mole stays up for a given level
unsigned long maxDurationForLevel(int level); // calculates the maximum duration a mole stays up for a given level

double targetCPSForLevel(int level);                       // calculates the target clicks-per-second for a given level
int computeHpForMole(int level, unsigned long durationMs); // computes the HP for a mole based on level and duration
int randomHpForMole(int level, unsigned long durationMs);  // computes a randomized HP for a mole based on level and duration

#endif // DIFFICULTY_H
