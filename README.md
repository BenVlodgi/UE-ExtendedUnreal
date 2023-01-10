# [Extended Unreal](https://github.com/BenVlodgi/UE-ExtendedUnreal)
[Unreal Engine](https://www.unrealengine.com/en-US/) [Plugin](https://docs.unrealengine.com/5.1/en-US/plugins-in-unreal-engine/) Exposing functions to Blueprints and adding small utilities.

## Included

| Structures   | Description                                                                                          |
|--------------|------------------------------------------------------------------------------------------------------|
| Object Array | Array of Objects, useful as a value in a Map (Dictionary).                                           |

| Enums      | Description                                                                                          |
|------------|------------------------------------------------------------------------------------------------------|
| World Type | Specifies the goal/source of a World object (Blueprint Accessible version of the Engine EWorldType). |

| Blueprint Functions               | Domain  |
|-----------------------------------|---------|
| Get World Gravity                 | Runtime |
| Get World Type                    | Runtime |
| Make Brush from App Style         | Runtime |
| Get Soft Class Name               | Runtime |
| Get Soft Class Display Name Text  | Runtime |
| Get Soft Object Name              | Runtime |
| Get Class Display Name Text       | Runtime |
| Get Component Reference Component | Runtime |
| Get Component by Name             | Runtime |
| To String (GameplayTag)           | Runtime |
| To Name (GameplayTag)             | Runtime |
| To Display String                 | Runtime |
| Cast Array                        | Runtime |
| Focus Viewport to Selection       | Editor  |


| Macros                   | Description                                                                                                                                     |
|--------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------|
| Merge                    | Merges two execution lines together and returns which execution line was used. This is useful for feeding into a `Select`.                      |
| For Loop (Continue)      | Requires `Continue` pin to be executed for the loop to continue, this is useful when the loop is large and should happen in segments over time. |
| For Each Loop (Continue) | Requires `Continue` pin to be executed for the loop to continue, this is useful when the loop is large and should happen in segments over time. |


| Widgets     | Description                                                                                                                                     |
|-------------|-------------------------------------------------------------------------------------------------------------------------------------------------|
| Style Image | Displays the image associated the [AppStyle](https://docs.unrealengine.com/5.0/en-US/API/Runtime/SlateCore/Styling/FAppStyle/)'s Property Name. |