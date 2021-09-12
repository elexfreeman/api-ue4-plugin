// Fill out your copyright notice in the Description page of Project Settings.

#include "RmApi.h"
DEFINE_LOG_CATEGORY(RkLog);
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

	Http = &FHttpModule::Get();
	// ...
}

void URmApi::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

// Called every frame
void URmApi::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URmApi::fCharListCtrl(const FString &sSearchStr)
{
	TSharedRef<IHttpRequest> Request1 = this->fMakeRequest(this->sServerUrl + TEXT("/api/character/") + TEXT("?name=") + sSearchStr + TEXT("&status=alive"));
	UE_LOG(RkLog, Warning, TEXT("Make request"), 0);

	Request1->OnProcessRequestComplete().BindLambda(
		[this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			if (bSuccess)
			{
				UE_LOG(RkLog, Warning, TEXT("char api ok"), 0);
				this->aChar.Empty();

				FString sData = Response->GetContentAsString();
				TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(sData);
				TSharedPtr<FJsonObject> jsonData = MakeShareable(new FJsonObject);
				FJsonSerializer::Deserialize(JsonReader, jsonData);

				// чекаем ошибку
				const TSharedPtr<FJsonObject> *errorVal;
				if (jsonData->TryGetObjectField("error", errorVal))
				{
					UE_LOG(RkLog, Warning, TEXT("char api parse json error"), 0);
					return;
				}

				// перебираем массив результатов
				TArray<TSharedPtr<FJsonValue>> aCharJson = jsonData->GetArrayField("results");
				UE_LOG(RkLog, Warning, TEXT("char api start parse json "), 0);

				for (int32 k = 0; k < aCharJson.Num(); k++)
				{

					URmCharInfo *pChar = NewObject<URmCharInfo>();

					TSharedPtr<FJsonValue> value = aCharJson[k];
					TSharedPtr<FJsonObject> json = value->AsObject();

					pChar->id = json->GetNumberField("id");
					pChar->sName = json->GetStringField("name");
					pChar->sType = json->GetStringField("type");
					pChar->sGender = json->GetStringField("gender");
					pChar->sImage = json->GetStringField("image");

					this->aChar.Push(pChar);

					// -------------------------------

					TSharedRef<IHttpRequest> Request = this->fMakeRequest(pChar->sImage);

					Request->OnProcessRequestComplete().BindLambda(
						[this, pChar](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
						{
							if (bSuccess)
							{
								bool IsValid;
								int32 w;
								int32 h;
								pChar->texImage = this->LoadTexture2DFromFile(Response->GetContent(), IsValid, w, h);
							}
						});

					Request->ProcessRequest();
					// -------------------------------
				}
				this->eventOnLoadCharDone.Broadcast();
			}
		});

	Request1->ProcessRequest();
};

UTexture2D *URmApi::LoadTexture2DFromFile(const TArray<uint8> &RawFileData, bool &IsValid, int32 &Width, int32 &Height)
{
	URmImgLoader *vActorSpawnLib = NewObject<URmImgLoader>();
	return vActorSpawnLib->LoadTexture2DFromFile(RawFileData, IsValid, Width, Height);
}

TSharedRef<IHttpRequest> URmApi::fMakeRequest(FString sUrl)
{
	UE_LOG(RkLog, Warning, TEXT("MakeRequest"), 0);
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetURL(sUrl);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	UE_LOG(RkLog, Warning, TEXT("MakeRequestDone"), 0);
	return Request;
}
