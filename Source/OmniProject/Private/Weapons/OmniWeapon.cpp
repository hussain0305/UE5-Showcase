#include "Weapons/OmniWeapon.h"
#include "Character/OmniCharacter.h"

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
