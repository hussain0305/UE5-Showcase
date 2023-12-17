#include "Items/OmniItem.h"
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

	AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	AddActorWorldRotation(FRotator(0.f, TransformedCos(), 0.f));
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
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, OtherActor->GetName());
		}
	}
}

void AOmniItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, OtherActor->GetName());
		}
	}
}
