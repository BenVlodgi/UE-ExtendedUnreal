<br/>
<p align="center">
  <a href="https://github.com/BenVlodgi/UE-ExtendedUnreal">
    <img src="https://github.com/BenVlodgi/UE-ExtendedUnreal/assets/1462374/f65a86dd-56ab-41b4-a3be-bc9442fb3341" alt="Logo" width="640" height="320">
  </a>
</p>

# Extended Unreal
[Unreal Engine](https://www.unrealengine.com/en-US/) [Plugin](https://docs.unrealengine.com/5.1/en-US/plugins-in-unreal-engine/) Exposing functions to Blueprints and adding small utilities.

Currently Compatible with Unreal Engine 5.5.

## Includes

| Structures   | Description |
|--------------|-------------|
| Object Array | Array of Objects, useful as a value in a Map/Dictionary. |
| Vector Array | Array of Vectors, useful as a value in a Map/Dictionary. |
| Delegate Handle Wrapper | Delegate Handle holds ID of a delegate, used for unbinding. |


| Enums      | Description |
|------------|-------------|
| World Type | The type of world an object lives in. Describes the context in which it is being used (Editor, Game, Preview etc.) (Blueprint Accessible version of the Engine [EWorldType](https://docs.unrealengine.com/5.0/en-US/API/Runtime/Engine/Engine/EWorldType__Type/)). |
| Extended Blend Space Axis| Used as parameter  for `GetBlendSpaceAxisMinMax()` |


| Class                       | Blueprint Functions                   | Domain     |
|-----------------------------|---------------------------------------|------------|
| Extended **Unreal** Library | Make Brush from App Style             | Runtime    |
| Extended **Unreal** Library | Make Brush from Style Set             | Runtime    |
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
| Extended **Unreal** Library | Set Actor Display Name                | Developer  |
| Extended **Unreal** Library | Rename Object                         | Runtime    |
| Extended **Unreal** Library | Set Root Component                    | Runtime    |
| Extended **Unreal** Library | Spawn Actor from Class                | Runtime    |
| Extended **Unreal** Library | Get Hash                              | Runtime    |
| Extended **Unreal** Library | Hash Combine                          | Runtime    |
| Extended **Unreal** Library | Hash Combine Fast                     | Runtime    |
| Extended **Unreal** Library | Get Custom Primitive Data             | Runtime    |
| Extended **Unreal** Library | Get Custom Primitive Data Float       | Runtime    |
| Extended **Unreal** Library | Copy Over Parameter Overrides         | Runtime    |
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
| Extended **Unreal** Library | Is Valid (DelegateHandleWrapper)      | Runtime    |
| Extended **Unreal** Library | Reset (DelegateHandleWrapper)         | Runtime    |
| Extended **Unreal** Library | Equal Equal (DelegateHandleWrapper)   | Runtime    |
| Extended **Unreal** Library | Not Equal (DelegateHandleWrapper)     | Runtime    |
| Extended **Unreal** Library | SetAutoPossessAI                      | Runtime    |
| Extended **Unreal** Library | Set Preview Skeletal Mesh             | Developer  |
| Extended **Unreal** Library | Get Distance Along Spline at Time     | Runtime    |
| Extended **Unreal** Library | Get Time Along Spline at Time         | Runtime    |
| Extended **Unreal** Library | Get Time Along Spline at Spline Point | Runtime    |
| Extended **Unreal** Library | Is Point Inside Capsule               | Runtime    |
| Extended **Unreal** Library | Is Point Inside Sphere                | Runtime    |
| Extended **Unreal** Library | Is Point Inside Box                   | Runtime    |
| Extended **Unreal** Library | Is Point Inside Capsule               | Runtime    |
| Extended **Unreal** Library | Is Point Inside Sphere                | Runtime    |
| Extended **Unreal** Library | Is Point Inside Box                   | Runtime    |
| Extended **Unreal** Library | Get Owner Chain                       | Runtime    |
| Extended **Unreal** Library | Get Interface Implementor             | Runtime    |
| Extended **Unreal** Library | Get Interface Implementors            | Runtime    |
| Extended **Unreal** Library | Get Player Viewport Transform         | Runtime    |
| Extended **Unreal** Library | Set Timeline Duration                 | Runtime    |
| Extended **Unreal** Library | IsInWater (Movement Component)        | Runtime    |
| Extended **Unreal** Library | Get Level Editing Viewport Location   | Developer  |
| Extended **Unreal** Library | Set Level Editing Viewport Location   | Developer  |
| Extended **Unreal** Library | Get Level Editing Viewport Rotation   | Developer  |
| Extended **Unreal** Library | Set Level Editing Viewport Rotation   | Developer  |
| Extended **Unreal** Library | Set Absolute (Advanced)               | Runtime    |
| Extended **Unreal** Library | Browse to Assets                      | Developer  |
| Extended **Unreal** Library | Editor Request Play Session           | Developer  |
| Extended **Unreal** Library | Create RenderTargetCube               | Runtime    |
| Extended **Unreal** Library | Clear RenderTargetCube                | Runtime    |
| Extended **Unreal** Library | Mark RenderTransform Dirty            | Runtime    |
| Extended **Unreal** Library | Mark RenderState Dirty                | Runtime    |
| Extended **Unreal** Library | Get AllowCPUAccess                    | Runtime    |
| Extended **Unreal** Library | Set AllowCPUAccess                    | Developer  |
| Extended **Unreal** Library | Flip Vectors                          | Runtime    |
| Extended **Unreal** Library | Sphere Overlap Component Collision    | Runtime    |
| Extended **Unreal** Library | Get Closest Point on Collision        | Runtime    |
| Extended **Unreal** Library | Get Closest Point on BodySetup        | Runtime    |
| Extended **Unreal** Library | Get Segments overlaping Component     | Runtime    |
| Extended **Unreal** Library | IsLevelNameValid                      | Runtime    |
| Extended **Unreal** Library | GetCharacterArrow                     | Developer  |           
| Extended **World** Library | Get World Gravity | Runtime |
| Extended **World** Library | Get World Type    | Runtime |
| Extended **World** Library | Is Game World     | Runtime |
| Extended **World** Library | Is Editor World   | Runtime |
| Extended **World** Library | Is Preview World  | Runtime |
| Extended **World** Library | World Type Query  | Runtime |
| Extended **Animation** Library | Get Blend Space Axis Min Max    | Runtime  |
| Extended **Animation** Library | Get Linked Anim Layers          | Runtime  |
| Extended **Animation** Library | Get All Animations              | Runtime  |
| Extended **Animation** Library | Get All Animations for Skeleton | Runtime  |
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
| Extended **Math** Library | Make Relative Rotator                  | Runtime |
| Extended **Math** Library | Signed Distance from Plane (Plane)     | Runtime |
| Extended **Math** Library | Equal (Plane)                          | Runtime |
| Extended **Math** Library | Flip (Plane)                           | Runtime |
| Extended **Math** Library | Is Valid (Plane)                       | Runtime |
| Extended **Math** Library | Get Origin (Plane)                     | Runtime |
| Extended **Math** Library | Get Normal (Plane)                     | Runtime |
| Extended **Math** Library | Plane Dot (Plane)                      | Runtime |
| Extended **Math** Library | Dot (Plane)                            | Runtime |
| Extended **Math** Library | Get Points in Circle                   | Runtime |
| Extended **Math** Library | Filter Split Path to Overlap Component | Runtime |
| Extended **Math** Library | Get Points in Circle                   | Runtime |
| Extended **Math** Library | Closest Point in Box                   | Runtime |
| Extended **Math** Library | Closest Point in Capsule               | Runtime |
| Extended **Math** Library | Sphere Encloses Sphere                 | Runtime |
| Extended **Math** Library | Angle Distance Degrees                 | Runtime |
| Extended **Math** Library | Get Axis and Angle Between Rotators    | Runtime |
| Extended **Math** Library | Get Axis and Angle Between Vectors     | Runtime |
| Extended **Math** Library | Get Rotator Angle Relative to Axis     | Runtime |
| Extended **Math** Library | Nearest                                | Runtime |
| Extended **Math** Library | Nearest Angle                          | Runtime |
| Extended **Math** Library | Lerp Angle Degrees                     | Runtime |
| Extended **Math** Library | Calculate Triangle Normal              | Runtime |
| Extended **Math** Library | Calculate Edge Up Direction            | Runtime |
| Extended **Math** Library | Random Weighted Array Item             | Runtime |
| Extended **Math** Library | Random Weighted Array Item From Stream | Runtime |
| Extended **Gameplay Abilities** Library | Has Ability                               | Runtime |
| Extended **Gameplay Abilities** Library | Set Float Attribute Base (Ability System) | Runtime |
| Extended **Gameplay Abilities** Library | Set Float Attribute Base (Actor)          | Runtime |
| Extended **Gameplay Abilities** Library | Get SetByCaller Tag Magnitudes            | Runtime |
| Extended **Gameplay Abilities** Library | Get SetByCaller Name Magnitudes           | Runtime |
| Extended **Gameplay Abilities** Library | Get SetByCaller Tag Magnitudes            | Runtime |
| Extended **Gameplay Abilities** Library | Get SetByCaller Name Magnitudes           | Runtime |
| Extended **Gameplay Abilities** Library | Get GameplayEffect Class SetByCaller Tag  | Runtime |
| Extended **Gameplay Abilities** Library | Set Ability Actor Info                    | Runtime |
| Extended **Gameplay Abilities** Library | Try Cancel Abilities By Tag               | Runtime |
| Extended **Gameplay Tag** Library | Add GameplayTag Containers        | Runtime |
| Extended **Gameplay Tag** Library | To String (GameplayTag)           | Runtime |
| Extended **Gameplay Tag** Library | To Name (GameplayTag)             | Runtime |
| Extended **Gameplay Tag** Library | To GameplayTag (Name)             | Runtime |
| Extended **Gameplay Tag** Library | To GameplayTagContainer (String)  | Runtime |
| Extended **Gameplay Tag** Library | To GameplayTagContainer (Strings) | Runtime |
| Extended **Gameplay Tag** Library | To String (GameplayTagContainer)  | Runtime |
| Extended **Gameplay Tag** Library | To Strings (GameplayTagContainer) | Runtime |
| Extended **World Partition** Library | Is Collision Loaded                  | Runtime |
| Extended **World Partition** Library | Set Default Visualizer Loading Range | Runtime |
| Extended **World** Library | Get World Gravity                  | Runtime |
| Extended **World** Library | Get World Type                     | Runtime |
| Extended **World** Library | Is Game World                      | Runtime |
| Extended **World** Library | Is Editor World                    | Runtime |
| Extended **World** Library | Is Preview World                   | Runtime |
| Extended **World** Library | Is Playing or Simulating in Editor | Runtime |
| Extended **World** Library | Is Playing in Editor               | Runtime |
| Extended **World** Library | Is Running Construction Script     | Runtime |
| Extended **World** Library | Is Simulating in Editor            | Runtime |
| Extended **World** Library | World Type Query                   | Runtime |



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
