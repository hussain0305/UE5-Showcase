#include "Items/OmniItem.h"
#include "HeaderFiles/DebugMacros.h"
#include "Character/OmniCharacter.h"
#include "Components/SphereComponent.h"
#include "HeaderFiles/OmniGlobal.h"

AOmniItem::AOmniItem()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Object Mesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetGenerateOverlapEvents(false);
	StaticMesh->SetCollisionProfileName(WEAPON_PICKUP_PROFILE);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Collision Sphere"));
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetCollisionProfileName(WEAPON_PICKUP_PROFILE);
}

void AOmniItem::ItemEquipped()
{

}

void AOmniItem::SetItemState(const EItemState NewState)
{
	ItemState = NewState;
	switch(ItemState)
	{
	case EItemState::Equipped:
		SphereComponent->Deactivate();
		StaticMesh->SetCollisionProfileName(WEAPON_COLLISION_PROFILE);
		SphereComponent->SetCollisionProfileName(WEAPON_COLLISION_PROFILE);
		break;
	case EItemState::Sheathed:
		SphereComponent->Deactivate();
		StaticMesh->SetCollisionProfileName(WEAPON_COLLISION_PROFILE);
		SphereComponent->SetCollisionProfileName(WEAPON_COLLISION_PROFILE);
		break;
	case EItemState::Pickup:
		SetActorRotation(FRotator(0.f,0.f,0.f));
		SphereComponent->Activate();
		StaticMesh->SetCollisionProfileName(WEAPON_PICKUP_PROFILE);
		SphereComponent->SetCollisionProfileName(WEAPON_PICKUP_PROFILE);
		break;
	}
}

void AOmniItem::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AOmniItem::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AOmniItem::OnSphereEndOverlap);
}

void AOmniItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameTime += DeltaTime;

	RoutineAsAPickup();
}

float AOmniItem::TransformedSin()
{
	return Amplitude * FMath::Sin(GameTime * TimeConstant);
}


float AOmniItem::TransformedCos()
{
	return Amplitude * FMath::Cos(GameTime * TimeConstant);
}

void AOmniItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor)
		{
			AOmniCharacter* OmniCharacter = Cast<AOmniCharacter>(OtherActor);
			if (OmniCharacter)
			{
				OmniCharacter->SetOverlappingItemBegin(this);
			}
		}
	}
}

void AOmniItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		if (OtherActor)
		{
			AOmniCharacter* OmniCharacter = Cast<AOmniCharacter>(OtherActor);
			if (OmniCharacter)
			{
				OmniCharacter->SetOverlappingItemEnd(this);
			}
		}
	}
}

void AOmniItem::RoutineAsAPickup()
{
	if (!IsPickup())
	{
		return;
	}
	AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	AddActorWorldRotation(FRotator(0.f, TransformedCos(), 0.f));
}
