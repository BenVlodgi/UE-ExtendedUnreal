// Copyright 2025 Dream Seed LLC.
#pragma once

#include "CoreMinimal.h"


#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphNodeUtils.h"
#include "K2Node.h"
#include "K2Node_AddPinInterface.h"


#include "K2Node_IsPinConnected.generated.h"


class FBlueprintActionDatabaseRegistrar;
class UEdGraph;
class UK2Node_Knot;

// IsPinConnected: Use in macros to determine if an input is connected to a pin. This allows for different behavior if a pin is left unconnected, such as using a default value instead of an input value.
UCLASS()
class UK2Node_IsPinConnected : public UK2Node
{
	GENERATED_BODY()


protected:
	/** Constructing FText strings can be costly, so we cache the node's title */
	FNodeTitleTextTable CachedNodeTitles;

	int CachedNodeTitleCachedConnectionState = -1;

protected:
	[[nodiscard]] virtual bool IsConnected() const;

	[[nodiscard]] virtual bool HasNonKnotConnection(UEdGraphPin* Pin, TSet<UK2Node_Knot*> VisitedKnots = TSet<UK2Node_Knot*>()) const;

public:
	//// UObject interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//// End of UObject interface

	// UEdGraphNode interface
	virtual bool ShouldShowNodeProperties() const override { return true; }
	//virtual bool ShouldDrawCompact() const override { return true; }

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	// End of UEdGraphNode interface

	
	// UK2Node interface
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	virtual bool IsNodePure() const override { return true; }
	// End of UK2Node interface

};
