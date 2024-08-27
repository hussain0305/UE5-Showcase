// Fill out your copyright notice in the Description page of Project Settings.


#include "Attacks/OmniAttack_Melee.h"
#include "Character/OmniAnimInstance.h"
#include "Character/OmniCharacter.h"
#include "HeaderFiles/DebugMacros.h"

void UOmniAttack_Melee::ProcessPrimaryInput_Start(AOmniCharacter* Wielder, AOmniWeapon* Weapon)
{
	TObjectPtr<UOmniAnimInstance> WielderAnimInstance = Wielder->GetOmniAnimInstance();
	WielderAnimInstance->AnimatedBodyPart =  AttackDetails.BodyPart;

	if (WielderAnimInstance && AttackDetails.AnimationMontage)
	{
		const int8 SectionToPlay = Weapon->GetMontageSectionToPlay(Wielder->GetLocomotionState());
		std::string SectionName = "Attack";
		SectionName += std::to_string(SectionToPlay);
		WielderAnimInstance->Montage_Play(AttackDetails.AnimationMontage);
		WielderAnimInstance->Montage_JumpToSection(FName(SectionName.c_str()), AttackDetails.AnimationMontage);
		Wielder->SetCharacterActionState(ECharacterActionState::Attacking);
	}
}

void UOmniAttack_Melee::ProcessPrimaryInput_Stop(AOmniCharacter* Wielder, AOmniWeapon* Weapon)
{

}

void UOmniAttack_Melee::ProcessSecondaryInput_Start(AOmniCharacter* Wielder, AOmniWeapon* Weapon)
{

}

void UOmniAttack_Melee::ProcessSecondaryInput_Stop(AOmniCharacter* Wielder, AOmniWeapon* Weapon)
{

}
