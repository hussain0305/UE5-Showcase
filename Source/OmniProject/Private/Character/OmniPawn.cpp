#include "Character/OmniPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h" 
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


AOmniPawn::AOmniPawn()
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

void AOmniPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AOmniPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOmniPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AOmniPawn::Move(const FInputActionValue& Value)
{

}

void AOmniPawn::Look(const FInputActionValue& Value)
{

}