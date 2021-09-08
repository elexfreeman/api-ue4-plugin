// Fill out your copyright notice in the Description page of Project Settings.

#include "RmApi.h"

// Sets default values for this component's properties
URmApi::URmApi()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void URmApi::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Http = &FHttpModule::Get();

	this->eventOnHttpResponse.AddDynamic(this, &URmApi::fLocationListCtrl);
	// ...
}

void URmApi::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	this->qReserve.Empty();
}

// Called every frame
void URmApi::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FReserveStr vData;
	if (!this->qReserve.IsEmpty())
	{
		this->qReserve.Dequeue(vData);
		this->eventOnHttpResponse.Broadcast(vData);
	}
	// ...
}

void URmApi::fLoadLocation()
{
	this->fHttpCall(this->sUrlLocationList);
}

void URmApi::fLoadChar(const FString &sSearchStr)
{
	this->fHttpCall(this->sUrlCharList + TEXT("?name=sSearchStr") + TEXT("&status=alive"));
}

/*Http call*/
void URmApi::fHttpCall(const FString &sUrl)
{
	TSharedPtr<FHttpModule> bHttp = nullptr;

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	Request->SetURL(FURL::FURL(*(this->sServerUrl + sUrl)).ToString());
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));

	Request->OnProcessRequestComplete().BindLambda(
		[&](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			TSharedRef<FReserveStr> vData = MakeShared<FReserveStr>();
			vData->sData = Response->GetContentAsString();
			vData->sUrl = FURL::FURL(*(this->sServerUrl + sUrl)).ToString();
			vData->idx = FMath::RandRange(0, 10000);
			this->qReserve.Enqueue(vData.Get());
		});

	Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void URmApi::fOnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
}

void URmApi::fLocationListCtrl(FReserveStr vData)
{
	if (vData.sUrl != this->sUrlLocationList)
	{
		return;
	}
}