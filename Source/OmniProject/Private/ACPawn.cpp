#include "ACPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h" 
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AACPawn::AACPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	//Setup Base Mesh
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Base Mesh"));
	SetRootComponent(SkeletalMesh);

	//Setup Capsule Component
	BaseCapsule = CreateDefaultSubobject<UCapsuleComponent>(FName("Base Collision"));
	BaseCapsule->SetCapsuleHalfHeight(44.0f);
	BaseCapsule->SetCapsuleRadius(22.0f);
	BaseCapsule->SetupAttachment(GetRootComponent());

	//Setup Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Boom"));
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->SetupAttachment(GetRootComponent());

	//Setup Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(CameraBoom);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AACPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AACPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AACPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AACPawn::Move(const FInputActionValue& Value)
{

}

void AACPawn::Look(const FInputActionValue& Value)
{

}
