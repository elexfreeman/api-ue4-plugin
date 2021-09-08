// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FRmLocation.generated.h"

USTRUCT(BlueprintType)
struct RIKMORTYAPIPLG_API FRmLocation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    int32 id = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sName = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sType = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sDimension = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sUrl = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sImage = TEXT("");

};