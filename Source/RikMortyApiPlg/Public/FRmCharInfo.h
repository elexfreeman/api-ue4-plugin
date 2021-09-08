// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FRmCharLocation.h"

#include "FRmCharInfo.generated.h"

USTRUCT(BlueprintType)
struct RIKMORTYAPIPLG_API FRmCharInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    int32 id = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sName = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sStatus = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sGender = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sType = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sUrl = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sImage = TEXT("");
    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    TArray<FRmCharLocation> aLocationShort;
    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    TArray<FRmCharLocation> aLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    TArray<FString> aEpisode;

};