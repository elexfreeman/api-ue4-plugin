// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FRmCharLocation.h"
#include "Engine/Texture2D.h"

#include "RmCharInfo.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RIKMORTYAPIPLG_API URmCharInfo : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    int32 id = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sName = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sStatus = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sGender = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sSpecies = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sType = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sUrl = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sImage = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    UTexture2D* texImage = nullptr;
    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    TArray<FRmCharLocation> aLocationShort;
    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    TArray<FRmCharLocation> aLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    TArray<FString> aEpisode;

};