// Copyright Epic Games, Inc. All Rights Reserved.


#include "MGP_2526PlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "MGP_2526.h"
#include "PuzzlePiece.h"
#include "PuzzlePiece.cpp"

#include "Widgets/Input/SVirtualJoystick.h"
class UInputAction;
void AMGP_2526PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		}
		else {

			UE_LOG(LogMGP_2526, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AMGP_2526PlayerController::OnClicked()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;


	UE_LOG(LogTemp, Warning, TEXT("Clicked!"));
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (Hit.GetActor()->ActorHasTag("Piece"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Clicked on a piece."));
		APuzzlePiece* HitPiece = Cast<APuzzlePiece>(Hit.GetActor());
		if (HitPiece) {
			if (HitPiece->bIsClicked) {

				HitPiece->bIsClicked = true;
			}
			else
			{
				HitPiece->bIsClicked = false;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Clicked is now true."));
	}

}



void AMGP_2526PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &AMGP_2526PlayerController::OnClicked);


		// only add IMCs for local player controllers
		if (IsLocalPlayerController())
		{
			// Add Input Mapping Contexts
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
			{
				for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}

				// only add these IMCs if we're not using mobile touch input
				if (!SVirtualJoystick::ShouldDisplayTouchInterface())
				{
					for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
					{
						Subsystem->AddMappingContext(CurrentContext, 0);
					}
				}

			}
		}
	}
}

