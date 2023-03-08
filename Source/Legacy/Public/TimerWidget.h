// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEGACY_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* WorldtimeMin;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* WorldtimeSec;
	UPROPERTY()
	class ALegacyGameMode* gm;

	void UpdateTimerWidget();
	FTimerHandle hdForTimerWidget;
};
