#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OmniGlobal.generated.h"

class AOmniCharacter;
class AOmniWeapon;

static FName WEAPON_COLLISION_PROFILE = "OmniWeaponCollision";
static FName WEAPON_PICKUP_PROFILE = "OmniPickups";
static FName CHARACTER_COLLISION_PROFILE = "OmniCharacterCollision";

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	OneHandedWeapon		UMETA(DisplayName = "One-Handed Weapon"),
	TwoHandedWeapon		UMETA(DisplayName = "Two-Handed Weapon")
};

UENUM(BlueprintType)
enum class ECharacterWieldState : uint8
{
	Unequipped			UMETA(DisplayName = "Unequipped"),
	OneHandedWeapon		UMETA(DisplayName = "One-Handed Weapon"),
	TwoHandedWeapon		UMETA(DisplayName = "Two-Handed Weapon")
};

USTRUCT(BlueprintType)
struct FInventoryState
{
	GENERATED_USTRUCT_BODY()
	
public:
	TObjectPtr<AOmniWeapon> OneHandedWeapon;
	TObjectPtr<AOmniWeapon> TwoHandedWeapon;
};

UENUM(BlueprintType)
enum class ECharacterActionState : uint8
{
	Idle						UMETA(DisplayName = "Idle"),
	Attacking_PrimaryAction		UMETA(DisplayName = "Attacking - Primary Action"),
	Aiming_SecondaryAction		UMETA(DisplayName = "Aiming - Secondary Action"),
	Attacking_SecondaryAction	UMETA(DisplayName = "Attacking - Secondary Action"),
	OtherAction					UMETA(DisplayName = "OtherAction")
};

UENUM(BlueprintType)
enum class EItemState : uint8
{
	Pickup				UMETA(DisplayName = "Pickup"),
	Equipped			UMETA(DisplayName = "Equipped"),
	Sheathed			UMETA(DisplayName = "Sheathed")
};

UENUM(BlueprintType)
enum class EOmniCharacterClass
{
	None		UMETA(DisplayName = "None"),
	Modern		UMETA(DisplayName = "Modern"),
	Medieval	UMETA(DisplayName = "Medieval")
};

USTRUCT(BlueprintType)
struct FPlayableCharactersTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EOmniCharacterClass CharacterClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AOmniCharacter> CharacterBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UTexture2D> DisplayImage;
};

UENUM(BlueprintType)
enum class ECharacterLocomotionState
{
	Undetermined		UMETA(DisplayName = "Undetermined"),
	Stationary			UMETA(DisplayName = "Stationary"),
	Walking				UMETA(DisplayName = "Walking"),
	Running				UMETA(DisplayName = "Running"),
	Falling				UMETA(DisplayName = "Falling")
};
