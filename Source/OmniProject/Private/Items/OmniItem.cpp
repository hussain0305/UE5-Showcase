#include "Items/OmniItem.h"
#include "Character/OmniCharacter.h"
#include "Components/SphereComponent.h"

AOmniItem::AOmniItem()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Object Mesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetGenerateOverlapEvents(false);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Collision Sphere"));
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetGenerateOverlapEvents(true);
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
		break;
	case EItemState::Pickup:
		SetActorRotation(FRotator(0.f,0.f,0.f));
		SphereComponent->Activate();
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
