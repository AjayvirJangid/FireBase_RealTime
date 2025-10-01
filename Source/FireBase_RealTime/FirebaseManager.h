#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "FirebaseManager.generated.h"

// ✅ Forward declare widget, don’t include it here
class ULeaderboardWidget;

UCLASS()
class FIREBASE_REALTIME_API AFirebaseManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AFirebaseManager();

protected:
	virtual void BeginPlay() override;

	FString GenerateRandomPlayerName();

	void OnSaveResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);
	void OnLoadResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Firebase")
	void IncreaseScore(const FString& PlayerID, int32 Amount);
	
	UFUNCTION(BlueprintCallable, Category="Firebase")
	void SaveScore(const FString& PlayerID, int32 NewScore);

	UFUNCTION(BlueprintCallable, Category="Firebase")
	void LoadLeaderboard();

private:
	int32 Score;
	FString PlayerName;
	FString FirebaseURL;

	// Reference to created widget
	UPROPERTY()
	ULeaderboardWidget* LeaderboardUI;

	// Widget class set in editor
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<ULeaderboardWidget> LeaderboardWidgetClass;
};
