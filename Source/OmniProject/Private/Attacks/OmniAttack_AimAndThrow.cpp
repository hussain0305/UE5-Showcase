// Fill out your copyright notice in the Description page of Project Settings.


#include "Attacks/OmniAttack_AimAndThrow.h"
#include "AnimNotifies/OmniAimPrimedNotify.h"
#include "Character/OmniAnimInstance.h"
#include "Character/OmniCharacter.h"
#include "HeaderFiles/DebugMacros.h"

void UOmniAttack_AimAndThrow::InitializeAttack()
{
	Super::InitializeAttack();
	SubscribeToBroadcasts();
}

void UOmniAttack_AimAndThrow::ProcessPrimaryInput_Start(AOmniCharacter* Wielder, AOmniWeapon* Weapon)
{
	//Weapon Throw
	if (!Wielder->GetIsAiming())
	{
		return;
	}

	TObjectPtr<UOmniAnimInstance> WielderAnimInstance = Wielder->GetOmniAnimInstance();
	WielderAnimInstance->AnimatedBodyPart =  AttackDetails.BodyPart;
	UAnimMontage* SecondaryActionMontage = AttackDetails.AnimationMontage;

	if (WielderAnimInstance && SecondaryActionMontage)
	{
		SecondaryActionMontage->bLoop = false;
		WielderAnimInstance->Montage_Play(SecondaryActionMontage);
		WielderAnimInstance->Montage_JumpToSection(RangedAttackMontageSectionName_Attack, SecondaryActionMontage);
		WielderAnimInstance->Montage_SetPlayRate(SecondaryActionMontage, 5.f);
		Wielder->SetCharacterActionState(ECharacterActionState::Attacking);
	}
}

void UOmniAttack_AimAndThrow::ProcessPrimaryInput_Stop(AOmniCharacter* Wielder, AOmniWeapon* Weapon)
{

}

void UOmniAttack_AimAndThrow::ProcessSecondaryInput_Start(AOmniCharacter* Wielder, AOmniWeapon* Weapon)
{
	Wielder_Cached = Wielder;
	Weapon_Cached = Weapon;
	
	TObjectPtr<UOmniAnimInstance> WielderAnimInstance = Wielder->GetOmniAnimInstance();
	WielderAnimInstance->AnimatedBodyPart =  AttackDetails.BodyPart;

	UAnimMontage* SecondaryActionMontage = AttackDetails.AnimationMontage;
	
	if (WielderAnimInstance && SecondaryActionMontage)
	{
		Wielder->SetWantsAim(true);
		Wielder->SetCharacterActionState(ECharacterActionState::PreppingAttack);

		SecondaryActionMontage->bLoop = false;
		WielderAnimInstance->Montage_Play(SecondaryActionMontage);
		WielderAnimInstance->Montage_JumpToSection(RangedAttackMontageSectionName_PrepStart, SecondaryActionMontage);
		WielderAnimInstance->Montage_SetPlayRate(SecondaryActionMontage, 1.f);
		Weapon->SetInputConsumers(EWeaponAction::SecondaryAttack, EWeaponAction::SecondaryAttack);
	}
}

void UOmniAttack_AimAndThrow::ProcessSecondaryInput_Stop(AOmniCharacter* Wielder, AOmniWeapon* Weapon)
{
	if(IsAimAnimationPlaying())
	{
		StopAim();
	}
}

void UOmniAttack_AimAndThrow::SecondaryAttackPrepped()
{
	//TODO: Better way to do this? Flag variables are no bueno, think about better, more robust design
	if(!bRecallingWeapon && !Wielder_Cached->GetWantsAim())
	{
		if(IsAimAnimationPlaying())
		{
			StopAim();
		}
		return;
	}
	TObjectPtr<UOmniAnimInstance> WielderAnimInstance = Wielder_Cached->GetOmniAnimInstance();

	WielderAnimInstance->AnimatedBodyPart =  AttackDetails.BodyPart;
	UAnimMontage* SecondaryActionMontage = AttackDetails.AnimationMontage;
	
	if (WielderAnimInstance && SecondaryActionMontage)
	{
		SecondaryActionMontage->bLoop = true;
		WielderAnimInstance->Montage_Play(SecondaryActionMontage);
		WielderAnimInstance->Montage_JumpToSection(RangedAttackMontageSectionName_Prepped, SecondaryActionMontage);
		WielderAnimInstance->Montage_SetPlayRate(SecondaryActionMontage, 1.f);
		Wielder_Cached->SetCharacterActionState(bRecallingWeapon ? ECharacterActionState::OtherAction : ECharacterActionState::AttackPrepped);
	}
}

bool UOmniAttack_AimAndThrow::IsAimAnimationPlaying() const
{
	if (!Wielder_Cached) { return false; }
	
	TObjectPtr<UOmniAnimInstance> WielderAnimInstance = Wielder_Cached->GetOmniAnimInstance();
	if (UAnimMontage* CurrentMontage = WielderAnimInstance->GetCurrentActiveMontage())
	{
		FName CurrentSectionName = WielderAnimInstance->Montage_GetCurrentSection(CurrentMontage);
		return CurrentSectionName == RangedAttackMontageSectionName_PrepStart || CurrentSectionName == RangedAttackMontageSectionName_Prepped;
	}
	return false;
}

void UOmniAttack_AimAndThrow::StopAim()
{
	if (Weapon_Cached)
	{
		Weapon_Cached->SetInputConsumers(EWeaponAction::PrimaryAttack, EWeaponAction::SecondaryAttack);
	}
	if (!Wielder_Cached) { return; }

	Wielder_Cached->SetWantsAim(false);
	TObjectPtr<UOmniAnimInstance> WielderAnimInstance = Wielder_Cached->GetOmniAnimInstance();
	WielderAnimInstance->AnimatedBodyPart =  AttackDetails.BodyPart;
	UAnimMontage* SecondaryActionMontage = AttackDetails.AnimationMontage;
	if (WielderAnimInstance && SecondaryActionMontage)
	{
		WielderAnimInstance->Montage_Play(SecondaryActionMontage);
		WielderAnimInstance->Montage_JumpToSection(RangedAttackMontageSectionName_PrepStart, SecondaryActionMontage);
		WielderAnimInstance->Montage_SetPlayRate(SecondaryActionMontage, -1);
		Wielder_Cached->SetCharacterActionState(ECharacterActionState::Idle);
	}
}

void UOmniAttack_AimAndThrow::RecallThrownWeaponAnimation()
{
	if (!Weapon_Cached || !Wielder_Cached || bRecallingWeapon)
	{
		return;
	}
	bRecallingWeapon = true;
	TObjectPtr<UOmniAnimInstance> WielderAnimInstance = Wielder_Cached->GetOmniAnimInstance();
	WielderAnimInstance->AnimatedBodyPart =  AttackDetails.BodyPart;
	UAnimMontage* SecondaryActionMontage = AttackDetails.AnimationMontage;
	
	if (WielderAnimInstance && SecondaryActionMontage)
	{
		Wielder_Cached->SetCharacterActionState(ECharacterActionState::OtherAction);
		SecondaryActionMontage->bLoop = false;
		WielderAnimInstance->Montage_Play(SecondaryActionMontage);
		WielderAnimInstance->Montage_JumpToSection(RangedAttackMontageSectionName_PrepStart, SecondaryActionMontage);
		WielderAnimInstance->Montage_SetPlayRate(SecondaryActionMontage, 1.f);
	}
}

void UOmniAttack_AimAndThrow::ThrownWeaponReceivedAnimation() const
{
	if (!Weapon_Cached || !Wielder_Cached)
	{
		return;
	}
	TObjectPtr<UOmniAnimInstance> WielderAnimInstance = Wielder_Cached->GetOmniAnimInstance();
	WielderAnimInstance->AnimatedBodyPart =  AttackDetails.BodyPart;
	UAnimMontage* SecondaryActionMontage = AttackDetails.AnimationMontage;
	
	if (WielderAnimInstance && SecondaryActionMontage)
	{
		SecondaryActionMontage->bLoop = false;
		WielderAnimInstance->Montage_Play(SecondaryActionMontage);
		WielderAnimInstance->Montage_JumpToSection(RangedAttackMontageSectionName_PrepStart, SecondaryActionMontage);
		WielderAnimInstance->Montage_SetPlayRate(SecondaryActionMontage, -1.f);
		Wielder_Cached->SetCharacterActionState(ECharacterActionState::Idle);
	}
}

void UOmniAttack_AimAndThrow::SubscribeToBroadcasts()
{
	if (AttackDetails.AnimationMontage)
	{
		UAnimMontage* AnimMontage = AttackDetails.AnimationMontage;

		for (const TArray<FAnimNotifyEvent>& NotifyEvents = AnimMontage->Notifies; const FAnimNotifyEvent& Event : NotifyEvents)
		{
			if (UOmniAimPrimedNotify* NotifyInstance = Cast<UOmniAimPrimedNotify>(Event.Notify))
			{
				NotifyInstance->OnAimPrimedNotify.AddDynamic(this, &UOmniAttack_AimAndThrow::SecondaryAttackPrepped);
				break;
			}
		}
	}
}



