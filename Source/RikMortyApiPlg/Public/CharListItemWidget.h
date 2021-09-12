// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "RmCharInfo.h"

#include "CharListItemWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, editinlinenew, BlueprintType, Blueprintable, meta = (DontUseGenericSpawnObject = "True", DisableNativeTick))
class RIKMORTYAPIPLG_API UCharListItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, Category = "AA")
	URmCharInfo *vCharData;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "AA", meta = (ToolTip = "Обновить данные"))
	void fSetCharData(URmCharInfo *_vCharData);
};
