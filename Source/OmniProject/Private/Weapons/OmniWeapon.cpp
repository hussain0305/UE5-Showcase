#include "Weapons/OmniWeapon.h"
#include "HeaderFiles/DebugMacros.h"
#include "Character/OmniCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HeaderFiles/OmniGlobal.h"

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
	}
}

int32 AOmniWeapon::GetMontageSectionToPlay(ECharacterLocomotionState LocomotionState)
{
	switch (LocomotionState)
	{
		case ECharacterLocomotionState::Stationary:
			return StationaryAttackSectionNumber;

		case ECharacterLocomotionState::Falling:
			return FalingAttackSectionNumber;
			
		case ECharacterLocomotionState::Running:
			return RunningAttackSectionNumber;

		default:
			return FMath::RandRange(1,NumAttackOptions);;
	}
}
