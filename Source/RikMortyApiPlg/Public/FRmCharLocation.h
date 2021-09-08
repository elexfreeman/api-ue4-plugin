// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FRmCharLocation.generated.h"

USTRUCT(BlueprintType)
struct RIKMORTYAPIPLG_API FRmCharLocation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sName = TEXT("");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA")
    FString sUrl = TEXT("");

};