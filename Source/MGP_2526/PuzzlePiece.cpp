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
	ConstructorHelpers::FObjectFinder<UStaticMesh> Piece(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'"));
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Piece"));
	//SetRootComponent(StaticMeshComponent);
	Cube->SetWorldScale3D(FVector(0.2, 0.1, 0.025));
	Cube->SetStaticMesh(Piece.Object);
	//Cube->OnClicked.AddDynamic(this, &APuzzlePiece::Grab);

}


void APuzzlePiece::Grab()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Click"));

}



// Called when the game starts or when spawned
void APuzzlePiece::BeginPlay()
{
	//if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComp))
	//EnhancedInputComponent->BindAction(Click, ETriggerEvent::Started, this, &APuzzlePiece::Grab);

	/*if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
	}*/
	Super::BeginPlay();
	//EnableInput(GetWorld()->GetFirstPlayerController());
	
	
	/*if (InputComponent) {
		InputComponent->BindAction("Click", IE_Pressed, this, &APuzzlePiece::Grab);
	}*/
}

void APuzzlePiece::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("BINDING INPUTS"));
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		
		EnhancedInputComponent->BindAction(Click, ETriggerEvent::Started, this, &APuzzlePiece::Grab);
		EnhancedInputComponent->BindAction(Click, ETriggerEvent::Completed, this, &APuzzlePiece::Grab);
	
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

// Called every frame
void APuzzlePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void APuzzlePiece::Grab()
//{
//
//}

