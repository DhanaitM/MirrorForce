// Copyright Mirror Force


#include "UI/WidgetController/OverlayWidgetController.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	if (const UMirrorAttributeSet* MirrorAttributeSet = Cast<UMirrorAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(MirrorAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(MirrorAttributeSet->GetMaxHealth());
	}
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UMirrorAttributeSet* MirrorAttributeSet = CastChecked<UMirrorAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MirrorAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MirrorAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
}
