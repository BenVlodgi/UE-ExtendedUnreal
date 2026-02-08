// Copyright 2025 Dream Seed LLC.

#include "K2Node_IsPinConnected.h"


#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintEditorSettings.h"
#include "EdGraphSchema_K2.h"
#include "Framework/Notifications/NotificationManager.h"
#include "SourceCodeNavigation.h"
#include "K2Node_CallFunction.h"
#include "K2Node_Knot.h"
#include "K2Node_Literal.h"
#include "KismetCompiler.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/CompilerResultsLog.h"



#define LOCTEXT_NAMESPACE "K2Node_IsPinConnected"

namespace K2Node_IsPinConnected
{
	const FName PinPinName = "Pin";
	const FName ResultPinName = "IsConnected";
}


bool UK2Node_IsPinConnected::IsConnected() const
{
	UEdGraphPin* PinPin = FindPin(K2Node_IsPinConnected::PinPinName);
	return PinPin && HasNonKnotConnection(PinPin);
}

bool UK2Node_IsPinConnected::HasNonKnotConnection(UEdGraphPin* Pin, TSet<UK2Node_Knot*> VisitedKnots) const
{
	if (!Pin)
	{
		return false;
	}

	for (UEdGraphPin* LinkedPin : Pin->LinkedTo)
	{
		if (!LinkedPin)
		{
			continue;
		}

		if (UK2Node_Knot* KnotNode = Cast<UK2Node_Knot>(LinkedPin->GetOwningNode()))
		{
			if (!VisitedKnots.Contains(KnotNode))
			{
				VisitedKnots.Add(KnotNode);
				if (HasNonKnotConnection(KnotNode->GetInputPin(), VisitedKnots))
				{
					return true;
				}
			}
		}
		else
		{
			return true; // found a non-knot connection
		}
	}

	return false;
}


//// UObject interface
void UK2Node_IsPinConnected::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
//// End of UObject interface


// UEdGraphNode interface
void UK2Node_IsPinConnected::AllocateDefaultPins()
{
	UEdGraphPin* PinPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, K2Node_IsPinConnected::PinPinName);
	UEdGraphPin* ResultPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Boolean, K2Node_IsPinConnected::ResultPinName);

	Super::AllocateDefaultPins();
}


void UK2Node_IsPinConnected::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	
	UEdGraphPin* ResultPin = FindPinChecked(K2Node_IsPinConnected::ResultPinName);



	// Make a literal bool
	UK2Node_CallFunction* MakeLiteralBool = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	MakeLiteralBool->SetFromFunction(UKismetSystemLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UKismetSystemLibrary, MakeLiteralBool)));
	MakeLiteralBool->AllocateDefaultPins();
	if (UEdGraphPin* ValuePin = MakeLiteralBool->FindPin(TEXT("Value")))
	{
		ValuePin->DefaultValue = IsConnected() ? FString("true") : FString("false");
	}
	CompilerContext.MovePinLinksToIntermediate(*ResultPin, *MakeLiteralBool->GetReturnValuePin());

	BreakAllNodeLinks();
}

void UK2Node_IsPinConnected::PinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::PinConnectionListChanged(Pin);

	if (Pin == FindPin(K2Node_IsPinConnected::PinPinName))
	{
		if (UEdGraph* Graph = GetGraph())
		{
			Modify();
			Graph->NotifyGraphChanged();
		}
	}
}

FText UK2Node_IsPinConnected::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	const FText BaseTitle = LOCTEXT("IsPinConnected_NodeTitle", "Is Pin Connected");

	bool bIsConnected = IsConnected();
	return FText::Format(
		FText::FromString(TEXT("{0} ({1})")),
		BaseTitle,
		FText::FromString(bIsConnected ? TEXT("True") : TEXT("False")));
}

// End of UEdGraphNode interface





// UK2Node interface

void UK2Node_IsPinConnected::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);

	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);
		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2Node_IsPinConnected::GetMenuCategory() const
{
	return LOCTEXT("IsConnected_MenuCategory", "Utilities");
}




#undef LOCTEXT_NAMESPACE
