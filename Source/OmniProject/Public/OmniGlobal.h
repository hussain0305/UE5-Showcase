#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OmniGlobal.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Unequipped			UMETA(DisplayName = "Unequipped"),
	OneHandedWeapon		UMETA(DisplayName = "One-Handed Weapon"),
	TwoHandedWeapon		UMETA(DisplayName = "Two-Handed Weapon")
};

UENUM(BlueprintType)
enum class EItemState : uint8
{
	Pickup				UMETA(DisplayName = "Pickup"),
	Equipped			UMETA(DisplayName = "Equipped")
};

