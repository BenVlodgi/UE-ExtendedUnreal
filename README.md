# [Extended Unreal](https://github.com/BenVlodgi/UE-ExtendedUnreal)
[Unreal Engine](https://www.unrealengine.com/en-US/) [Plugin](https://docs.unrealengine.com/5.1/en-US/plugins-in-unreal-engine/) Exposing functions to Blueprints and adding small utilities.
Currently Compatible with Unreal Engine 5.3.

## Included

| Structures   | Description |
|--------------|-------------|
| Object Array | Array of Objects, useful as a value in a Map (Dictionary). |
| Delegate Handle Wrapper | Delegate Handle holds ID of a delegate, used for unbinding. |


| Enums      | Description |
|------------|-------------|
| World Type | The type of world an object lives in. Describes the context in which it is being used (Editor, Game, Preview etc.) (Blueprint Accessible version of the Engine [EWorldType](https://docs.unrealengine.com/5.0/en-US/API/Runtime/Engine/Engine/EWorldType__Type/)). |
| Extended Blend Space Axis| Used as parameter  for `GetBlendSpaceAxisMinMax()` |


| Class                       | Blueprint Functions                   | Domain     |
|-----------------------------|---------------------------------------|------------|
| Extended **Unreal** Library | Make Brush from App Style             | Runtime    |
| Extended **Unreal** Library | Make Brus from Style Set              | Runtime    |
| Extended **Unreal** Library | Make Brush from Slate Icon            | Runtime    |
| Extended **Unreal** Library | Get Soft Class Name                   | Runtime    |
| Extended **Unreal** Library | Get Soft Class Display Name Text      | Developer  |
| Extended **Unreal** Library | Get Soft Object Name                  | Runtime    |
| Extended **Unreal** Library | Get Class Display Name Text           | Developer  |
| Extended **Unreal** Library | Get Component (Component Reference)   | Runtime    |
| Extended **Unreal** Library | Make Component Reference              | Runtime    |
| Extended **Unreal** Library | Get Component by Name                 | Runtime    |
| Extended **Unreal** Library | To Display String                     | Runtime    |
| Extended **Unreal** Library | Focus Viewport to Selection           | Developer  |
| Extended **Unreal** Library | Get Attached Actors of Class          | Runtime    |
| Extended **Unreal** Library | Get First Attached Actor of Class     | Runtime    |
| Extended **Unreal** Library | Set Active (Safe) (Component)         | Runtime    |
| Extended **Unreal** Library | Is Running Construction (Actor)       | Runtime    |
| Extended **Unreal** Library | Is Beginning Play (Actor)             | Runtime    |
| Extended **Unreal** Library | Has Begun Play (Actor)                | Runtime    |
| Extended **Unreal** Library | Is in Play (Actor)                    | Runtime    |
| Extended **Unreal** Library | Get Hash                              | Runtime    |
| Extended **Unreal** Library | Get Custom Primitive Data             | Runtime    |
| Extended **Unreal** Library | Get Custom Primitive Data Float       | Runtime    |
| Extended **Unreal** Library | Does Class Implement Interface        | Runtime    |
| Extended **Unreal** Library | Destroy Audio Component when Complete | Runtime    |
| Extended **Unreal** Library | Is Actor in Actor Owner Chain         | Runtime    |
| Extended **Unreal** Library | Is Actor in Component Owner Chain     | Runtime    |
| Extended **Unreal** Library | Get Owner Chain                       | Runtime    |
| Extended **Unreal** Library | Get Owner (Safe)                      | Runtime    |
| Extended **Unreal** Library | Is Net Startup Actor                  | Runtime    |
| Extended **Unreal** Library | As Actor or Owner                     | Runtime    |
| Extended **Unreal** Library | Bind Event to OnTransformUpdated      | Runtime    |
| Extended **Unreal** Library | Unbind Event from OnTransformUpdated  | Runtime    |
| Extended **Unreal** Library | Set Preview Skeletal Mesh             | Developer  |
| Extended **Unreal** Library | Get Distance Along Spline at Time     | Runtime    |
| Extended **Unreal** Library | Get Time Along Spline at Time         | Runtime    |
| Extended **Unreal** Library | Get Time Along Spline at Spline Point | Runtime    |
| Extended **Unreal** Library | Get Owner Chain                       | Runtime    |
| Extended **Unreal** Library | Get Interface Implementor             | Runtime    |
| Extended **Unreal** Library | Get Interface Implementors            | Runtime    |
| Extended **Unreal** Library | GetPlayerViewportTransform            | Runtime    |
| Extended **World** Library | Get World Gravity | Runtime |
| Extended **World** Library | Get World Type    | Runtime |
| Extended **World** Library | Is Game World     | Runtime |
| Extended **World** Library | Is Editor World   | Runtime |
| Extended **World** Library | Is Preview World  | Runtime |
| Extended **Animation** Library | Get Blend Space Axis Min Max | Runtime  |
| Extended **Array** Library | Cast Array                 | Runtime |
| Extended **Array** Library | Remove Items               | Runtime |
| Extended **Array** Library | To Set                     | Runtime |
| Extended **Array** Library | Filter Array for Interface | Runtime |
| Extended **Array** Library | Resolve                    | Runtime |
| Extended **Set** Library   | Add Set             | Runtime |
| Extended **Set** Library   | Cast Set            | Runtime |
| Extended **Map** Library   | Find Keys by Value  | Runtime |
| Extended **Curve** Library | Get Float Value (Runtime Float Curve) | Runtime |
| Extended **Curve** Library | Get Time Range (Runtime Float Curve)  | Runtime |
| Extended **Curve** Library | Get Value Range (Runtime Float Curve) | Runtime |
| Extended **Curve** Library | Is Constant (Runtime Float Curve)     | Runtime |
| Extended **Curve** Library | Is Empty (Runtime Float Curve)        | Runtime |
| Extended **Curve** Library | Get Curve (Runtime Curve)             | Runtime |
| Extended **Math** Library | Make Relative Rotator              | Runtime |
| Extended **Math** Library | Signed Distance from Plane (Plane) | Runtime |
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
| Extended **World Partition** Library | Is Collision Loaded | Runtime |
| Extended **World Partition** Library | Set Default Visualizer Loading Range | Runtime |
| Extended **World** Library | Get World Gravity | Runtime |
| Extended **World** Library | Get World Type    | Runtime |
| Extended **World** Library | Is Game World     | Runtime |
| Extended **World** Library | Is Editor World   | Runtime |
| Extended **World** Library | Is Preview World  | Runtime |



| Macros                   | Description |
|--------------------------|-------------|
| Merge                    | Merges two execution lines together and returns which execution line was used. This is useful for feeding into a `Select`.                      |
| For Loop (Continue)      | Requires `Continue` pin to be executed for the loop to continue, this is useful when the loop is large and should happen in segments over time. |
| For Each Loop (Continue) | Requires `Continue` pin to be executed for the loop to continue, this is useful when the loop is large and should happen in segments over time. |


| Widgets     | Description |
|-------------|-------------|
| Style Image | Displays the image associated the [AppStyle](https://docs.unrealengine.com/5.0/en-US/API/Runtime/SlateCore/Styling/FAppStyle/)'s Property Name. |

| Graph Nodes | Description |
|-------------|-------------|
| Sphere Trace by Profile (Control Rig) | Sweeps a sphere against the world and return the first blocking hit using a specific profile. (By default: Sphere traces exist in control rig, but not by profile) |
