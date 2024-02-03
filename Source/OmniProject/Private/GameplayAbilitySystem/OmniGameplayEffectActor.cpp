// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/OmniGameplayEffectActor.h"

#include "Character/OmniCharacter.h"
#include "Components/SphereComponent.h"
#include "GameplayAbilitySystem/OmniAbilitySystemComponent.h"

// Sets default values
AOmniGameplayEffectActor::AOmniGameplayEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere Collision Component"));
	SphereComponent->SetupAttachment(GetRootComponent());
}

void AOmniGameplayEffectActor::ApplyGameplayEffectTo(AOmniCharacter* TargetCharacter)
{
	if(UOmniAbilitySystemComponent* OmniASC = Cast<UOmniAbilitySystemComponent>(TargetCharacter->GetAbilitySystemComponent()))
	{
		FGameplayEffectContextHandle EffectContextHandle = OmniASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = OmniASC->MakeOutgoingSpec(GameplayEffect, 1.f, EffectContextHandle);
		OmniASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void AOmniGameplayEffectActor::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ApplyGameplayEffectTo(Cast<AOmniCharacter>(OtherActor));
}

void AOmniGameplayEffectActor::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// Called when the game starts or when spawned
void AOmniGameplayEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AOmniGameplayEffectActor::OnSphereOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AOmniGameplayEffectActor::OnSphereOverlapEnd);
}
