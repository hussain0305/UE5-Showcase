#include "Weapons/OmniWeapon.h"

#include "OmniAttackFactory.h"
#include "Attacks/OmniAttack.h"
#include "Character/OmniAnimInstance.h"
#include "HeaderFiles/DebugMacros.h"
#include "Character/OmniCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "HeaderFiles/OmniGlobal.h"
#include "Game/OmniGameModeBase.h"

AOmniWeapon::AOmniWeapon()
{
	ScabbardMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Scabbard"));
	ScabbardMesh->SetupAttachment(StaticMesh);

	WeaponTraceTransforms = CreateDefaultSubobject<USceneComponent>(FName("Weapon Trace Transforms"));
	WeaponTraceTransforms->SetupAttachment(RootComponent);
	WeaponTraceStart = CreateDefaultSubobject<USceneComponent>(FName("Weapon Trace Start"));
	WeaponTraceStart->SetupAttachment(WeaponTraceTransforms);
	WeaponTraceEnd = CreateDefaultSubobject<USceneComponent>(FName("Weapon Trace End"));
	WeaponTraceEnd->SetupAttachment(WeaponTraceTransforms);
	
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(FName("Weapon Box"));
	WeaponBox->SetupAttachment(StaticMesh);
	WeaponBox->SetCollisionProfileName(WEAPON_PICKUP_PROFILE);
}

void AOmniWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AOmniWeapon::OnBoxBeginOverlap);

	InitializeAttacks();
}

void AOmniWeapon::InitializeAttacks()
{
	UOmniAttackFactory* AttackFactory = NewObject<UOmniAttackFactory>(this);
	if (PrimaryAttack.AttackClass)
	{
		PrimaryAttack.Attack = AttackFactory->CreateAttackInstance(PrimaryAttack.AttackClass, this);
		PrimaryAttack.Attack->InitializeAttack();
	}
	if (SecondaryAttack.AttackClass)
	{
		SecondaryAttack.Attack = AttackFactory->CreateAttackInstance(SecondaryAttack.AttackClass, this);
		SecondaryAttack.Attack->InitializeAttack();
	}

	SetInputConsumers(EWeaponAction::PrimaryAttack, EWeaponAction::SecondaryAttack);
}

void AOmniWeapon::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor)
	{
		if (OtherActor)
		{
			AOmniCharacter* OmniCharacter = Cast<AOmniCharacter>(OtherActor);
			if (OmniCharacter)
			{
				OmniCharacter->SetOverlappingWeaponBegin(this);
			}
		}
	}
}

void AOmniWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	if (OtherActor)
	{
		if (OtherActor)
		{
			AOmniCharacter* OmniCharacter = Cast<AOmniCharacter>(OtherActor);
			if (OmniCharacter)
			{
				OmniCharacter->SetOverlappingWeaponEnd(this);
			}
		}
	}
}

void AOmniWeapon::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetItemState() != EItemState::Equipped)
	{
		return;
	}
	PRINT_DEBUG_MESSAGE_WITH_PARAMETER(5.f, FColor::Green, FString("Hit "), OtherActor->GetName());
	
	FHitResult BoxTraceResult;
	TArray<AActor*> ActorsToIgnore;
	if (GetWielder() != nullptr)
	{
		ActorsToIgnore.Add(GetWielder());
	}

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		WeaponTraceStart->GetComponentLocation(),
		WeaponTraceEnd->GetComponentLocation(),
		WeaponHitTraceSize,
		WeaponTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		BoxTraceResult,
		true);
}

void AOmniWeapon::SetItemState(const EItemState NewState)
{
	Super::SetItemState(NewState);
	switch(GetItemState())
	{
	case EItemState::Equipped:
		WeaponBox->SetCollisionProfileName(WEAPON_COLLISION_PROFILE);
		break;
	case EItemState::Sheathed:
		WeaponBox->SetCollisionProfileName(WEAPON_COLLISION_PROFILE);
		break;
	case EItemState::Pickup:
		WeaponBox->SetCollisionProfileName(WEAPON_PICKUP_PROFILE);
		break;
	case EItemState::Thrown:
		break;
	}
}

int32 AOmniWeapon::GetMontageSectionToPlay(ECharacterLocomotionState LocomotionState)
{
	return 1;
	// if(WeaponConfig.PrimaryAttackType == EAttackSelection::StateBased)
	// {
	// 	switch (LocomotionState)
	// 	{
	// 	case ECharacterLocomotionState::Stationary:
	// 		return WeaponConfig.RunningAttackSectionNumber;
	//
	// 	case ECharacterLocomotionState::Falling:
	// 		return WeaponConfig.FallingAttackSectionNumber;
	// 		
	// 	case ECharacterLocomotionState::Running:
	// 		return WeaponConfig.RunningAttackSectionNumber;
	//
	// 	default:
	// 		return FMath::RandRange(1,WeaponConfig.NumSections);
	// 	}
	// }
	// return FMath::RandRange(1,WeaponConfig.NumSections);
}

void AOmniWeapon::ProcessPrimaryInput_Start()
{
	if (!PrimaryInputConsumer)
	{
		return;
	}
	PrimaryInputConsumer->ProcessPrimaryInput_Start(GetWielder(), this);
}

void AOmniWeapon::ProcessPrimaryInput_Stop()
{
	if (!PrimaryInputConsumer)
	{
		return;
	}
	PrimaryInputConsumer->ProcessPrimaryInput_Stop(GetWielder(), this);
}

void AOmniWeapon::ProcessSecondaryInput_Start()
{
	if (!SecondaryInputConsumer)
	{
		return;
	}
	SecondaryInputConsumer->ProcessSecondaryInput_Start(GetWielder(), this);
}

void AOmniWeapon::ProcessSecondaryInput_Stop()
{
	if (!SecondaryInputConsumer)
	{
		return;
	}
	SecondaryInputConsumer->ProcessSecondaryInput_Stop(GetWielder(), this);
}

FOmniWeaponTable AOmniWeapon::GetWeaponConfig()
{
	AssertWeaponConfig();
	return WeaponConfig;
}

void AOmniWeapon::SetInputConsumers(EWeaponAction Primary, EWeaponAction Secondary)
{
	switch(Primary)
	{
		case EWeaponAction::PrimaryAttack:
			PrimaryInputConsumer = PrimaryAttack.Attack;
			break;
		case EWeaponAction::SecondaryAttack:
			PrimaryInputConsumer = SecondaryAttack.Attack;
			break;
		case EWeaponAction::CallThrownWeapon:
			break;
	}
	switch(Secondary)
	{
		case EWeaponAction::PrimaryAttack:
			SecondaryInputConsumer = PrimaryAttack.Attack;
			break;
		case EWeaponAction::SecondaryAttack:
			SecondaryInputConsumer = SecondaryAttack.Attack;
			break;
		case EWeaponAction::CallThrownWeapon:
			break;
	}

}

void AOmniWeapon::AssertWeaponConfig()
{
	if (WeaponConfigFetched)
	{
		return;
	}
	if (AOmniGameModeBase* GameMode = Cast<AOmniGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		if (GameMode->GetWeaponConfiguration(WeaponID, WeaponType, WeaponConfig))
		{
			WeaponConfigFetched = true;
		}
	}
}