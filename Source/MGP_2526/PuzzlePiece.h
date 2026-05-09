// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzlePiece.generated.h"

UCLASS()
class MGP_2526_API APuzzlePiece : public AActor
{
	GENERATED_BODY()
	
	

public:	
	// Sets default values for this actor's properties
	APuzzlePiece();

	UPROPERTY(VisibleAnywhere)
	FVector SpawnVector;
	FVector CurrentPos;
	FVector PickupPos;
	FVector LerpPos;
	FQuat CurrentRotation;
	FQuat LerpRot;
	FQuat TargetRot;
	void Grab();
	void Flip();
	void Rotate();
	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<APuzzlePiece> PieceClass;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

public:	
	// Called every frame
	float Timer;
	virtual void Tick(float DeltaTime) override;
	bool bIsFlipped;
	bool bIsRotated;
	bool bIsClicked;
};
