// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePiece.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <iostream>
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
	if (bIsClicked) {
		UE_LOG(LogTemp, Warning, TEXT("Should be picked up now."));

	}


}



// Called when the game starts or when spawned
void APuzzlePiece::BeginPlay()
{
	Super::BeginPlay();
	/*EnableInput(GetWorld()->GetFirstPlayerController());
	if (InputComponent) {
		InputComponent->BindAction("Click", IE_Pressed, this, &APuzzlePiece::Grab);
	}*/
}

// Called every frame
void APuzzlePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

