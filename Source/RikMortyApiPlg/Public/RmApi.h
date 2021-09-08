// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Engine/EngineBaseTypes.h"
#include "Math/UnrealMathUtility.h"

#include "FReserveStr.h"

#include "RmApi.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHttpResponse, FReserveStr, vData);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RIKMORTYAPIPLG_API URmApi : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URmApi();

	const FString sServerUrl = TEXT("https://rickandmortyapi.com");

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FHttpModule *Http = nullptr;

	TQueue<FReserveStr> qReserve;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, meta = (DisplayName = "eventOnHttpResponse", Category = "AA", MultiLine = "true"))
	FOnHttpResponse eventOnHttpResponse;

	// API-URL

	UPROPERTY(BlueprintReadWrite, Category = "AA")
	FString sUrlCharList = TEXT("/api/character");

	UPROPERTY(BlueprintReadWrite, Category = "AA")
	FString sUrlLocationList = TEXT("/api/location");

	UFUNCTION(BlueprintCallable, Category = "AA", meta = (ToolTip = "Загрузить локации"))
	void fLoadLocation();

	UFUNCTION(BlueprintCallable, Category = "AA", meta = (ToolTip = "Загрузть персонажей"))
	void fLoadChar(const FString &sSearchStr);

	UFUNCTION(BlueprintCallable, Category = "AA", meta = (ToolTip = "Отправить запрос на сервер"))
	void fHttpCall(const FString &sUrl);

	UFUNCTION(BlueprintCallable, Category = "AA_Net")
	void fLocationListCtrl(FReserveStr vData);

	void fOnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};

