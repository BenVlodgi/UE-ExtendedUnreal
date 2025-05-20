// Copyright 2025 Dream Seed LLC.


#include "ExtendedRenderingLibrary.h"


#include "Engine/TextureRenderTargetCube.h"
#include "Engine/TextureRenderTarget2D.h"
#include "TextureResource.h"
#include "Misc/RuntimeErrors.h"

#if WITH_EDITOR
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "PackageTools.h"
#endif


#define LOCTEXT_NAMESPACE "ExtendedRenderingLibrary"



TArray<float> UExtendedRenderingLibrary::GetCustomPrimitiveData(const UPrimitiveComponent* Target)
{
	if (IsValid(Target))
	{
		const FCustomPrimitiveData& PrimitiveData = Target->GetCustomPrimitiveData();
		return PrimitiveData.Data;
	}

	return TArray<float>();
}

float UExtendedRenderingLibrary::GetCustomPrimitiveDataFloat(const UPrimitiveComponent* Target, int32 DataIndex)
{
	if (IsValid(Target))
	{
		const FCustomPrimitiveData& PrimitiveData = Target->GetCustomPrimitiveData();
		if (PrimitiveData.Data.IsValidIndex(DataIndex))
		{
			return PrimitiveData.Data[DataIndex];
		}
	}

	return 0.0;
}

void UExtendedRenderingLibrary::CopyOverParameterOverrides(UMaterialInstanceDynamic* Target, const UMaterialInstance* MaterialInstance)
{
	LLM_SCOPE(ELLMTag::MaterialInstance);

	if (!ensureAsRuntimeWarning(Target != nullptr && MaterialInstance != nullptr))
	{
		return;
	}

	for (const auto& Parameter : MaterialInstance->VectorParameterValues) Target->SetVectorParameterValueByInfo(Parameter.ParameterInfo, Parameter.ParameterValue);
	for (const auto& Parameter : MaterialInstance->DoubleVectorParameterValues) Target->SetDoubleVectorParameterValue(Parameter.ParameterInfo.Name, Parameter.ParameterValue);
	for (const auto& Parameter : MaterialInstance->ScalarParameterValues) Target->SetScalarParameterValueByInfo(Parameter.ParameterInfo, Parameter.ParameterValue);
	for (const auto& Parameter : MaterialInstance->TextureParameterValues) Target->SetTextureParameterValueByInfo(Parameter.ParameterInfo, Parameter.ParameterValue);
	for (const auto& Parameter : MaterialInstance->FontParameterValues) Target->SetFontParameterValue(Parameter.ParameterInfo.Name, Parameter.FontValue, Parameter.FontPage);

#if WITH_EDITOR
	FObjectCacheEventSink::NotifyReferencedTextureChanged_Concurrent(Target);
#endif

	////Target->InitResources();
}

UTextureRenderTargetCube* UExtendedRenderingLibrary::CreateRenderTargetCube(UObject* WorldContextObject, int32 Width, FLinearColor ClearColor, bool bAutoGenerateMipMaps, bool bSupportUAVs, bool bHDR, bool bForceLinearGamma)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	if (Width > 0 && World)
	{
		UTextureRenderTargetCube* NewRenderTargetCube = NewObject<UTextureRenderTargetCube>(WorldContextObject);
		check(NewRenderTargetCube);
		//NewRenderTargetCube->RenderTargetFormat = Format;
		NewRenderTargetCube->ClearColor = ClearColor;
		//NewRenderTargetCube->bAutoGenerateMips = bAutoGenerateMipMaps;
		NewRenderTargetCube->bCanCreateUAV = bSupportUAVs;
		NewRenderTargetCube->InitAutoFormat(Width);
		NewRenderTargetCube->UpdateResourceImmediate(true);
		NewRenderTargetCube->bHDR = true;
		////NewRenderTargetCube->OverrideFormat = PF_Unknown;
		NewRenderTargetCube->bForceLinearGamma = true;

		return NewRenderTargetCube;
	}

	return nullptr;
}

void UExtendedRenderingLibrary::ClearRenderTargetCube(UObject* WorldContextObject, UTextureRenderTargetCube* TextureRenderTargetCube, FLinearColor ClearColor)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	if (TextureRenderTargetCube
		&& TextureRenderTargetCube->GetResource()
		&& World)
	{
		////FTextureRenderTargetResource* RenderTargetResource = TextureRenderTargetCube->GameThread_GetRenderTargetResource();
		////ENQUEUE_RENDER_COMMAND(ClearRTCommand)(
		////	[RenderTargetResource, ClearColor](FRHICommandList& RHICmdList)
		////	{
		////		FRHIRenderPassInfo RPInfo(RenderTargetResource->GetRenderTargetTexture(), ERenderTargetActions::DontLoad_Store);
		////		RHICmdList.Transition(FRHITransitionInfo(RenderTargetResource->GetRenderTargetTexture(), ERHIAccess::Unknown, ERHIAccess::RTV));
		////		RHICmdList.BeginRenderPass(RPInfo, TEXT("ClearRT"));
		////		DrawClearQuad(RHICmdList, ClearColor);
		////		RHICmdList.EndRenderPass();
		////		
		////		RHICmdList.Transition(FRHITransitionInfo(RenderTargetResource->GetRenderTargetTexture(), ERHIAccess::RTV, ERHIAccess::SRVMask));
		////	});
	}
}

UTexture2D* UExtendedRenderingLibrary::RenderTarget2D_ExportStatic(UTextureRenderTarget2D* RenderTarget, FString Path, TextureCompressionSettings CompressionSettings, TextureMipGenSettings MipSettings)
{

#if WITH_EDITOR
	if (!RenderTarget)
	{
		FMessageLog("Blueprint").Warning(LOCTEXT("RenderTargetCreateStaticTexture2D_InvalidRenderTarget", "RenderTargetCreateStaticTexture2DEditorOnly: RenderTarget must be non-null."));
		return nullptr;
	}
	else if (!RenderTarget->GetResource())
	{
		FMessageLog("Blueprint").Warning(LOCTEXT("RenderTargetCreateStaticTexture2D_ReleasedRenderTarget", "RenderTargetCreateStaticTexture2DEditorOnly: RenderTarget has been released."));
		return nullptr;
	}
	else
	{
		FString Name;
		FString PackageName;
		IAssetTools& AssetTools = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

		//Use asset name only if directories are specified, otherwise full path
		if (!Path.Contains(TEXT("/")))
		{
			FString AssetName = RenderTarget->GetOutermost()->GetName();
			const FString SanitizedBasePackageName = UPackageTools::SanitizePackageName(AssetName);
			const FString PackagePath = FPackageName::GetLongPackagePath(SanitizedBasePackageName) + TEXT("/");
			AssetTools.CreateUniqueAssetName(PackagePath, Path, PackageName, Name);
		}
		else
		{
			if (Path.StartsWith(TEXT("/Content/")))
			{
				Path.RemoveFromStart(TEXT("/Content/"));
				Path.InsertAt(0, TEXT("/Game/"));
			}
			else if (Path.StartsWith(TEXT("Content/")))
			{
				Path.RemoveFromStart(TEXT("Content/"));
				Path.InsertAt(0, TEXT("/Game/"));
			}
			else if (Path.StartsWith(TEXT("Game/")))
			{
				Path.RemoveFromStart(TEXT("Game/"));
				Path.InsertAt(0, TEXT("/Game/"));
			}
			else if (!Path.StartsWith(TEXT("/")))
			{
				Path.InsertAt(0, TEXT("/Game/"));
			}

			AssetTools.CreateUniqueAssetName(Path, TEXT(""), PackageName, Name);

			FText NamesMessage = FText::Format(LOCTEXT("RenderTarget2D_ExportStatic_Names", "RenderTarget2D_ExportStatic: PackageName='{0}'. Name='{1}'."), FText::FromString(PackageName), FText::FromString(Name));
			FMessageLog("Blueprint").Warning(NamesMessage);
		}

		UObject* NewObj = nullptr;

		// create a static 2d texture
		NewObj = RenderTarget->ConstructTexture2D(CreatePackage(*PackageName), Name, RenderTarget->GetMaskedFlags() | RF_Public | RF_Standalone, CTF_Default | CTF_AllowMips | CTF_SkipPostEdit, nullptr);
		UTexture2D* NewTex = Cast<UTexture2D>(NewObj);

		if (NewTex != nullptr)
		{
			// package needs saving
			NewObj->MarkPackageDirty();

			// Update Compression and Mip settings
			NewTex->CompressionSettings = CompressionSettings;
			NewTex->MipGenSettings = MipSettings;
			NewTex->PostEditChange();

			// Notify the asset registry
			FAssetRegistryModule::AssetCreated(NewObj);

			return NewTex;
		}
		FMessageLog("Blueprint").Warning(LOCTEXT("RenderTargetCreateStaticTexture2D_FailedToCreateTexture", "RenderTargetCreateStaticTexture2DEditorOnly: Failed to create a new texture."));
	}
#else
	FMessageLog("Blueprint").Error(LOCTEXT("Texture2D's cannot be created at runtime.", "RenderTargetCreateStaticTexture2DEditorOnly: Can't create Texture2D at run time. "));
#endif
	return nullptr;
}

#undef LOCTEXT_NAMESPACE
