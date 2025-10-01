#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaderboardWidget.generated.h"

// ✅ Forward declare Actor
class AFirebaseManager;

UCLASS()
class FIREBASE_REALTIME_API ULeaderboardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Leaderboard")
	void AddEntry(const FString& PlayerName, int32 Score);

	UFUNCTION(BlueprintCallable, Category="Leaderboard")
	void UpdateScore(int32 NewScore);
	

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;

	UFUNCTION(BlueprintCallable, Category="Leaderboard")
	void ClearEntries();

	// Manager reference (set when creating the widget)
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	AFirebaseManager* FirebaseManagerRef;

	

protected:
	// UI elements bound from UMG
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* LeaderboardList;
};
