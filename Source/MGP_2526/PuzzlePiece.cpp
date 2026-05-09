// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePiece.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <iostream>
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include <MGP_2526Character.h>
#include "Math/UnrealMathUtility.h"
#include <Kismet/KismetMathLibrary.h>
using namespace std;
// Sets default values
APuzzlePiece::APuzzlePiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*ConstructorHelpers::FObjectFinder<UStaticMesh> Piece(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Piece"));
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetWorldScale3D(FVector(0.2, 0.1, 0.025));
	StaticMeshComponent->SetStaticMesh(Piece.Object);*/

}


void APuzzlePiece::Grab()
{

	CurrentPos = GetActorLocation();
	LerpPos = FMath::VInterpTo(CurrentPos, PickupPos, Timer, 0.75);
	SetActorLocation(LerpPos);


	UE_LOG(LogTemp, Warning, TEXT("CurrentPos: %s"), *CurrentPos.ToString());
	UE_LOG(LogTemp, Warning, TEXT("SpawnVector: %s"), *SpawnVector.ToString());
	UE_LOG(LogTemp, Warning, TEXT("PickupPos: %s"), *PickupPos.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Lerppos: %s"), *LerpPos.ToString());
	UE_LOG(LogTemp, Warning, TEXT("CurrentRotation: %s"), *CurrentRotation.ToString());
}

void APuzzlePiece::Rotate()
{
	CurrentRotation = GetActorQuat();
	int Multiplier;
	//if (fmod(CurrentRotation.Z, 90)==0) {
	//	Multiplier = CurrentRotation.Z / 90;
	//}
	//else {
		Multiplier = floor(CurrentRotation.Z / 90);
	//}
		TargetRot = CurrentRotation;
		TargetRot.Z = 90 * Multiplier;
	LerpRot = FQuat::Slerp(CurrentRotation,TargetRot, 0.75);
	SetActorRotation(LerpRot);
}

void APuzzlePiece::Flip()
{
	CurrentRotation = GetActorQuat();
	int Multiplier;
	Multiplier = floor(CurrentRotation.X / 90);
	TargetRot = CurrentRotation;
	TargetRot.X = 90 * Multiplier;
	LerpRot = FQuat::Slerp(CurrentRotation, TargetRot, 0.75);
	SetActorRotation(LerpRot);
}

// Called when the game starts or when spawned
void APuzzlePiece::BeginPlay()
{
	Super::BeginPlay();
	SpawnVector = GetActorLocation();
	PickupPos = SpawnVector; PickupPos.Z = SpawnVector.Z + 10;
	CurrentPos = SpawnVector;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *SpawnVector.ToString());
	/*EnableInput(GetWorld()->GetFirstPlayerController());
	if (InputComponent) {
		InputComponent->BindAction("Click", IE_Pressed, this, &APuzzlePiece::Grab);
	}*/
}

// Called every frame
void APuzzlePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer = DeltaTime;
	if (bIsClicked)
	{
		Grab();
		
	}
	if (bIsClicked == false) {
		CurrentPos = GetActorLocation();
		LerpPos = FMath::VInterpTo(CurrentPos, SpawnVector, Timer, 0.75);
		SetActorLocation(LerpPos);
	}
	

	if (bIsFlipped) {
		Flip();
	}
	else if (bIsRotated) {
		Rotate();
	}
	else {
		CurrentRotation = GetActorQuat();
	}


}

