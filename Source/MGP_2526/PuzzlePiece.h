// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PuzzlePiece.generated.h"

class UInputAction;

UCLASS()
class MGP_2526_API APuzzlePiece : public ACharacter
{
	GENERATED_BODY()
	
	

public:	
	// Sets default values for this actor's properties
	APuzzlePiece();

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* Click;
	


protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* Cube;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	/*UFUNCTION()*/
	void Grab();

};
