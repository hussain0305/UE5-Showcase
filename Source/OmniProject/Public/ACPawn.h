#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ACPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class OMNIPROJECT_API AACPawn : public APawn
{
	GENERATED_BODY()

public:
	AACPawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Core Component")
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Core Component")
		UCapsuleComponent* BaseCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Core Component")
		USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Core Component")
		UCameraComponent* Camera;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
