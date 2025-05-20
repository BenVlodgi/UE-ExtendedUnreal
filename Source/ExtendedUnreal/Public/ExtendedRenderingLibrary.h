// Copyright 2025 Dream Seed LLC.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExtendedRenderingLibrary.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDUNREAL_API UExtendedRenderingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Rendering|Material")
	static UPARAM(DisplayName = "Data") TArray<float> GetCustomPrimitiveData(const UPrimitiveComponent* Target);

	UFUNCTION(BlueprintCallable, Category = "Rendering|Material")
	static UPARAM(DisplayName = "Data") float GetCustomPrimitiveDataFloat(const UPrimitiveComponent* Target, int32 DataIndex);

	/**
	 * Copy parameter values from another material instance. This will copy only parameters explicitly overridden in that material instance!!
	 * This will not clear away existing override parameters unless there is a new one to replace it.
	 *
	 * @param	Target				Parameter-overrides copied to this material instance.
	 * @param	MaterialInstance	Parameter-overrides copied from this material instance.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Over Parameter Overrides"), Category = "Rendering|Material")
	static void CopyOverParameterOverrides(UMaterialInstanceDynamic* Target, const UMaterialInstance* MaterialInstance);

	/**
	 * Creates a new render target cube and initializes it to the specified dimensions.
	 */
	UFUNCTION(BlueprintCallable, Category = "Rendering", meta = (WorldContext = "WorldContextObject"))
	static UTextureRenderTargetCube* CreateRenderTargetCube(UObject* WorldContextObject, int32 Width = 256, FLinearColor ClearColor = FLinearColor::Green, bool bAutoGenerateMipMaps = false, bool bSupportUAVs = false, bool bHDR = true, bool bForceLinearGamma = true);

	/**
	 * Clears the specified render target cube with the given ClearColor.
	 */
	UFUNCTION(BlueprintCallable, Category = "Rendering", meta = (Keywords = "ClearRenderTarget", WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static void ClearRenderTargetCube(UObject* WorldContextObject, UTextureRenderTargetCube* TextureRenderTargetCube, FLinearColor ClearColor);

	/**
	* Creates a new Static Texture from a Render Target 2D.
	* Path can target plugins: /Plugin/Folder/TextureName
	* Only works in the editor
	*/
	UFUNCTION(BlueprintCallable, Category = "Rendering", meta = (DisplayName = "Save (Render Target 2D)", Keywords = "Create Static Texture from Render Target", UnsafeDuringActorConstruction = "true", DevelopmentOnly, DeprecatedFunction, DeprecationMessage = "Doesn't seem to be working."))
	static UTexture2D* RenderTarget2D_ExportStatic(UTextureRenderTarget2D* RenderTarget, FString Path = "/Game/Texture", enum TextureCompressionSettings CompressionSettings = TC_Default, enum TextureMipGenSettings MipSettings = TMGS_FromTextureGroup);

};
