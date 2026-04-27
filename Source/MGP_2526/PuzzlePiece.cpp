// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePiece.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <iostream>
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include <MGP_2526Character.h>
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
	
}



// Called when the game starts or when spawned
void APuzzlePiece::BeginPlay()
{
	Super::BeginPlay();
	SpawnVector = GetActorLocation();
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
	if (bIsClicked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Clicked Activated"));
		AMGP_2526Character* plr = Cast<AMGP_2526Character>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		CurrentPos = plr->mousepos;
		CurrentPos.Y = plr->mousepos.Y + 30;
		
	}
	if (bIsClicked == false) {
		CurrentPos = SpawnVector;

	}
}

