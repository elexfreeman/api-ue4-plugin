
    
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FReserveStr.generated.h"


USTRUCT(BlueprintType)
struct RIKMORTYAPIPLG_API FReserveStr
{
    GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "AA")
	FString sData = TEXT("");

	UPROPERTY(BlueprintReadWrite, Category = "AA")
	FString sUrl = TEXT("");

	UPROPERTY(BlueprintReadWrite, Category = "AA")
	int32 idx = 0;
};
