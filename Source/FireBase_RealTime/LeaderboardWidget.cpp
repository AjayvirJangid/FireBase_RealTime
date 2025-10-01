// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderboardWidget.h"
#include "Components/VerticalBox.h"
#include "FirebaseManager.h"
#include "Components/TextBlock.h"

void ULeaderboardWidget::AddEntry(const FString& PlayerName, int32 Score)
{
	if (!LeaderboardList) return;

	UTextBlock* EntryText = NewObject<UTextBlock>(LeaderboardList);
	EntryText->SetText(FText::FromString(PlayerName + " : " + FString::FromInt(Score)));
	LeaderboardList->AddChild(EntryText);
}

void ULeaderboardWidget::UpdateScore(int32 NewScore)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), NewScore)));
	}
}

void ULeaderboardWidget::ClearEntries()
{
	if (LeaderboardList)
	{
		LeaderboardList->ClearChildren();
	}
}

