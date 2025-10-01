// Fill out your copyright notice in the Description page of Project Settings.


#include "FirebaseManager.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Blueprint/UserWidget.h"
#include "LeaderboardWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LeaderboardWidget.h"
#include "Components/VerticalBox.h"

// Sets default values
AFirebaseManager::AFirebaseManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Score= 0;
	
	// Randomize each time game runs
	PlayerName = GenerateRandomPlayerName();
	FirebaseURL = "https://realtime-database-a19df-default-rtdb.firebaseio.com/";

}

// Called when the game starts or when spawned
void AFirebaseManager::BeginPlay()
{
	Super::BeginPlay();
	if(LeaderboardWidgetClass)
	{
		 LeaderboardUI = CreateWidget<ULeaderboardWidget>(GetWorld(), LeaderboardWidgetClass);
		if (LeaderboardUI)
		{
			LeaderboardUI->FirebaseManagerRef = this;
			LeaderboardUI->AddToViewport();

			if (LeaderboardUI && LeaderboardUI->IsValidLowLevel())
			{
				LeaderboardUI->UpdateScore(Score);
			}

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				PC->bShowMouseCursor = true;
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}

	LoadLeaderboard();
	
}

// Called every frame
void AFirebaseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Simple Key Handling for testing

	// if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::SpaceBar))
	// {
	// 	IncreaseScore();
	// }
	//
	// if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::Enter))
	// {
	// 	SaveScore();
	// 	
	// }

}

void AFirebaseManager::IncreaseScore()
{
	Score += 10;

	UE_LOG(LogTemp, Log, TEXT("Score: %d"), Score);

	// Update in UI
	if (LeaderboardUI && LeaderboardUI->IsValidLowLevel())
	{
		LeaderboardUI->UpdateScore(Score);
	}
	
}
void AFirebaseManager::SaveScore()
{
	FString Url = FirebaseURL + PlayerName + ".json";

	//JSON body
	 TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	 JsonObject->SetNumberField("score",Score);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(),Writer);

	// create HTTP request

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb("PUT");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->OnProcessRequestComplete().BindUObject(this, &AFirebaseManager::OnSaveResponse);
	Request->ProcessRequest();


	
}

FString AFirebaseManager::GenerateRandomPlayerName()
{
	const FString Prefix = "Player_";
	FString RandomString;

	// Create random 6-char alphanumeric
	const FString Charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	for (int32 i = 0; i < 6; i++)
	{
		int32 Index = FMath::RandRange(0, Charset.Len() - 1);
		RandomString.AppendChar(Charset[Index]);
	}

	return Prefix + RandomString;
}

void AFirebaseManager::OnSaveResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Save Response: %s"), *Response->GetContentAsString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save score!"));
	}
}

void AFirebaseManager::LoadLeaderboard()
{
	FString Url = FirebaseURL + ".json";

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb("GET");
	Request->OnProcessRequestComplete().BindUObject(this, &AFirebaseManager::OnLoadResponse);
	Request->ProcessRequest();
}

void AFirebaseManager::OnLoadResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FString JsonString = Response->GetContentAsString();
		UE_LOG(LogTemp, Log, TEXT("Leaderboard JSON: %s"), *JsonString);
		

		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			if (LeaderboardUI)
			{
				LeaderboardUI->ClearEntries();
			}

			for (auto& Elem : JsonObject->Values)
			{
				TSharedPtr<FJsonObject> PlayerData = Elem.Value->AsObject();
				if (PlayerData.IsValid())
				{
					int32 PlayerScore = PlayerData-> GetIntegerField("score");

					if (LeaderboardUI)
					{
						LeaderboardUI->AddEntry(Elem.Key,PlayerScore);
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to load leaderboard!"));
				}
			}
		}
	}
}



