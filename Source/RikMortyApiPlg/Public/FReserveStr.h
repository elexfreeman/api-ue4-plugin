// Fill out your copyright notice in the Description page of Project Settings.
// Полученные данные

#pragma once

#include "CoreMinimal.h"
#include "FReserveStr.generated.h"


USTRUCT(BlueprintType)
struct RIKMORTYAPIPLG_API FReserveStr
{
    GENERATED_BODY()

	// данные в виде строки
	UPROPERTY(BlueprintReadWrite, Category = "AA")
	FString sData = TEXT("");

	// урл
	UPROPERTY(BlueprintReadWrite, Category = "AA")
	FString sUrl = TEXT("");

	// номер запроса
	UPROPERTY(BlueprintReadWrite, Category = "AA")
	int32 idx = 0;

	// данные если картинка
	UPROPERTY(BlueprintReadWrite, Category = "AA")
	TArray<uint8> rawData;
};
