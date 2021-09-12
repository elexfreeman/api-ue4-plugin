// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/EngineBaseTypes.h"
#include "Engine/Texture2D.h"
#include "Math/UnrealMathUtility.h"
#include "Modules/ModuleManager.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"
#include "HAL/UnrealMemory.h"

#include "RmImgLoader.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RIKMORTYAPIPLG_API URmImgLoader : public UObject
{
	GENERATED_BODY()

public:
	UTexture2D *LoadTexture2DFromFile(const TArray<uint8>& RawFileData, bool &IsValid, int32 &Width, int32 &Height)
	{
		IsValid = false;
		UTexture2D *LoadedT2D = NULL;


		IImageWrapperModule &ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		//IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
		IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

		//Create T2D!
		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
		{
			const TArray<uint8> *UncompressedBGRA = NULL;
			if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
			{
				LoadedT2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

				//Valid?
				if (!LoadedT2D)
					return NULL;
				//~~~~~~~~~~~~~~

				//Out!
				Width = ImageWrapper->GetWidth();
				Height = ImageWrapper->GetHeight();

				//Copy!
				void *TextureData = LoadedT2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
				LoadedT2D->PlatformData->Mips[0].BulkData.Unlock();

				//Update!
				LoadedT2D->UpdateResource();
			}
		}

		// Success!
		IsValid = true;
		return LoadedT2D;
	}

protected:
public:
};
