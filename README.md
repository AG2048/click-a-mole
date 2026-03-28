# tclick-a-mole

Click A Mole :> Actuatator Team

## Directory Structure
```
/README.md
/click_a_mole
  /click_a_mole.ino
  /game_logic
    /game_logic.h
    /game_logic.cpp
    /tests
      /<test_name>
        /<test_name>.ino
  /motor_interface
    /motor_interface.h
    /motor_interface.cpp
    /tests
      /<test_name>
        /<test_name>.ino
  /led_interface
    /led_interface.h
    /led_interface.cpp
    /tests
      /<test_name>
        /<test_name>.ino
/leaderboard
  ...
```

## NOTE ABOUT FUNCTIONALITY
As of March 28, Gamelogic is sucessfully integrated with LEDs. Actuators not yet.


## Editing Convention

Whenever you wish to add a new feature:

1. Create a branch.
   - Naming: \<YYYY-MM-DD\>\_\<SUBTEAM\>\_\<FEATURE NAME\>
2. Edit the LOG in README.md specific to your branch!
   - Explain what this branch is meant to implement
3. Edit everything on the branch.
4. Test on the branch.
5. When you are sure the feature is correct, merge the branches.
   - The later-merged log should appear BELOW every previously merged branch.

## LOG
### \<Branch Merge NAME\> - Start: \<Date\> - Merged: \<Date\>
\<What this merge is supposed to do\>

### 25-10-04_actuator_stepperMotor - Start: 2025 Oct 4 - Merged: 2025 Oct 11
Working test case with motor with the magnetic encoder to measure the angle
