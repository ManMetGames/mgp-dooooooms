// Copyright Epic Games, Inc. All Rights Reserved.

#include "MGP_2526Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"

#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PuzzlePiece.h"
#include "MGP_2526PlayerController.h"


AMGP_2526Character::AMGP_2526Character()
{
	// Set size for collision capsule
	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//	
	//// Don't rotate when the controller rotates. Let that just affect the camera.
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	//// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	//// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	//// instead of recompiling to adjust them
	//GetCharacterMovement()->JumpZVelocity = 500.f;
	//GetCharacterMovement()->AirControl = 0.35f;
	//GetCharacterMovement()->MaxWalkSpeed = 500.f;
	//GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	//GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	//GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	//// Create a camera boom (pulls in towards the player if there is a collision)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 400.0f;
	//CameraBoom->bUsePawnControlRotation = true;

	//// Create a follow camera
	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


}

void AMGP_2526Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &AMGP_2526Character::OnClicked);
		UE_LOG(LogTemp, Warning, TEXT("Inputs are bound"));
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
void AMGP_2526Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AMGP_2526PlayerController* Ctl = Cast<AMGP_2526PlayerController>(GetController());
	Ctl->DeprojectMousePositionToWorld(mousepos, mousedir);

}



void AMGP_2526Character::BeginPlay()
{
	

}

void AMGP_2526Character::OnClicked() {
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;

	AMGP_2526PlayerController* Ctl = Cast<AMGP_2526PlayerController>(GetController());
	bHitSuccessful = Ctl->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (Hit.GetActor()->ActorHasTag("Piece"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Clicked on a piece."));
		APuzzlePiece* HitPiece = Cast<APuzzlePiece>(Hit.GetActor());
		if (HitPiece) {
			if (HitPiece->bIsClicked==false) {

				HitPiece->bIsClicked = true;
				UE_LOG(LogTemp, Warning, TEXT("Clicked is now true."));
			}
			else
			{
				HitPiece->bIsClicked = false;
				UE_LOG(LogTemp, Warning, TEXT("Clicked is now false."));
			}
		}
		else if (HitPiece->bIsClicked == true) {
			HitPiece->bIsClicked = false;
		}

	}

}


void AMGP_2526Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AMGP_2526Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AMGP_2526Character::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AMGP_2526Character::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AMGP_2526Character::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AMGP_2526Character::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}
