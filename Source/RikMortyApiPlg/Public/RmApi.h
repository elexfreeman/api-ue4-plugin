// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
DECLARE_LOG_CATEGORY_EXTERN(RkLog, Log, All);

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Engine/EngineBaseTypes.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/Queue.h"

#include "FReserveStr.h"
#include "RmCharInfo.h"
#include "RmImgLoader.h"

#include "RmApi.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadCharDone);

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

	FHttpModule* Http = nullptr;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	

	// API-URL

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, meta = (DisplayName = "eventOnLoadCharDone", Category = "AA", MultiLine = "true"))
	FOnLoadCharDone eventOnLoadCharDone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AA")
	TArray<URmCharInfo *> aChar;


	UFUNCTION(BlueprintCallable, Category = "AA_Net")
	void fCharListCtrl(const FString &sSearchStr);

	UFUNCTION(BlueprintCallable, Category = "AA_Net")
	UTexture2D *LoadTexture2DFromFile(const TArray<uint8> &RawFileData, bool &IsValid, int32 &Width, int32 &Height);


	TSharedRef<IHttpRequest> fMakeRequest(FString sUrl);

};
