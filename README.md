# [Extended Unreal](https://github.com/BenVlodgi/UE-ExtendedUnreal)
[Unreal Engine](https://www.unrealengine.com/en-US/) [Plugin](https://docs.unrealengine.com/5.1/en-US/plugins-in-unreal-engine/) Exposing functions to Blueprints and adding small utilities.

## Included

| Structures   | Description |
|--------------|-------------|
| Object Array | Array of Objects, useful as a value in a Map (Dictionary). |

| Enums      | Description |
|------------|-------------|
| World Type | The type of world an object lives in. Describes the context in which it is being used (Editor, Game, Preview etc.) (Blueprint Accessible version of the Engine [EWorldType](https://docs.unrealengine.com/5.0/en-US/API/Runtime/Engine/Engine/EWorldType__Type/)). |
| Extended Blend Space Axis| Used as parameter  for `GetBlendSpaceAxisMinMax()` |


| Class                   | Blueprint Functions               | Domain     |
|-------------------------|-----------------------------------|------------|
| Extended **Unreal** Library | Get World Gravity                 | Runtime    |
| Extended **Unreal** Library | Get World Type                    | Runtime    |
| Extended **Unreal** Library | Make Brush from App Style         | Runtime    |
| Extended **Unreal** Library | Get Soft Class Name               | Runtime    |
| Extended **Unreal** Library | Get Soft Class Display Name Text  | Developer  |
| Extended **Unreal** Library | Get Soft Object Name              | Runtime    |
| Extended **Unreal** Library | Get Class Display Name Text       | Developer  |
| Extended **Unreal** Library | Get Component Reference Component | Runtime    |
| Extended **Unreal** Library | Get Component by Name             | Runtime    |
| Extended **Unreal** Library | To Display String                 | Runtime    |
| Extended **Unreal** Library | Focus Viewport to Selection       | Developer  |
| Extended **Unreal** Library | Get Attached Actors of Class      | Runtime    |
| Extended **Unreal** Library | Get First Attached Actor of Class | Runtime    |
| Extended **Animation** Library | Get Blend Space Axis Min Max | Runtime  |
| Extended **Array** Library | Cast Array          | Runtime |
| Extended **Array** Library | RemoveItems (Array) | Runtime |
| Extended **Array** Library | To Set (Array)      | Runtime |
| Extended **Map** Library   | Find Keys by Value  | Runtime |
| Extended **Curve** Library | Get Float Value (Runtime Float Curve) | Runtime |
| Extended **Curve** Library | Get Time Range (Runtime Float Curve)  | Runtime |
| Extended **Curve** Library | Get Value Range (Runtime Float Curve) | Runtime |
| Extended **Curve** Library | Is Constant (Runtime Float Curve)     | Runtime |
| Extended **Curve** Library | Is Empty (Runtime Float Curve)        | Runtime |
| Extended **Math** Library | Make Relative Rotator              | Runtime |
| Extended **Math** Library | Signed Distance From Plane (Plane) | Runtime |
| Extended **Math** Library | Equal (Plane)                      | Runtime |
| Extended **Math** Library | Flip (Plane)                       | Runtime |
| Extended **Math** Library | Is Valid (Plane)                   | Runtime |
| Extended **Math** Library | Get Origin (Plane)                 | Runtime |
| Extended **Math** Library | Get Normal (Plane)                 | Runtime |
| Extended **Math** Library | Plane Dot (Plane)                  | Runtime |
| Extended **Math** Library | Dot (Plane)                        | Runtime |
| Extended **Gameplay Abilities** Library | Has Ability                               | Runtime |
| Extended **Gameplay Abilities** Library | Set Float Attribute Base (Ability System) | Runtime |
| Extended **Gameplay Abilities** Library | Set Float Attribute Base (Actor)          | Runtime |
| Extended **Gameplay Abilities** Library | Get SetByCaller Tag Magnitudes            | Runtime |
| Extended **Gameplay Abilities** Library | Get SetByCaller Name Magnitudes           | Runtime |
| Extended **Gameplay Abilities** Library | Get SetByCaller Tag Magnitudes            | Runtime |
| Extended **Gameplay Abilities** Library | Get SetByCaller Name Magnitudes           | Runtime |
| Extended **Gameplay Abilities** Library | Get GameplayEffect Class SetByCaller Tag  | Runtime |
| Extended **Gameplay Tag** Library | Add GameplayTag Containers        | Runtime |
| Extended **Gameplay Tag** Library | To String (GameplayTag)           | Runtime |
| Extended **Gameplay Tag** Library | To Name (GameplayTag)             | Runtime |
| Extended **Gameplay Tag** Library | To GameplayTag (Name)             | Runtime |
| Extended **Gameplay Tag** Library | To GameplayTagContainer (String)  | Runtime |
| Extended **Gameplay Tag** Library | To GameplayTagContainer (Strings) | Runtime |
| Extended **Gameplay Tag** Library | To String (GameplayTagContainer)  | Runtime |
| Extended **Gameplay Tag** Library | To Strings (GameplayTagContainer) | Runtime |


| Macros                   | Description |
|--------------------------|-------------|
| Merge                    | Merges two execution lines together and returns which execution line was used. This is useful for feeding into a `Select`.                      |
| For Loop (Continue)      | Requires `Continue` pin to be executed for the loop to continue, this is useful when the loop is large and should happen in segments over time. |
| For Each Loop (Continue) | Requires `Continue` pin to be executed for the loop to continue, this is useful when the loop is large and should happen in segments over time. |


| Widgets     | Description |
|-------------|-------------|
| Style Image | Displays the image associated the [AppStyle](https://docs.unrealengine.com/5.0/en-US/API/Runtime/SlateCore/Styling/FAppStyle/)'s Property Name. |