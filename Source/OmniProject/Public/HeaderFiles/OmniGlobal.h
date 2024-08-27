#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OmniGlobal.generated.h"

class UOmniAttack;
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

UENUM(BlueprintType)
enum class ECharacterActionState : uint8
{
	Idle				UMETA(DisplayName = "Idle"),
	Attacking			UMETA(DisplayName = "Attacking"),
	PreppingAttack		UMETA(DisplayName = "Prepping Attack"),
	AttackPrepped		UMETA(DisplayName = "Attack Prepped"),
	OtherAction			UMETA(DisplayName = "Other Action")
};

UENUM(BlueprintType)
enum class EItemState : uint8
{
	Pickup				UMETA(DisplayName = "Pickup"),
	Equipped			UMETA(DisplayName = "Equipped"),
	Sheathed			UMETA(DisplayName = "Sheathed"),
	Thrown				UMETA(DisplayName = "Thrown")
};

UENUM(BlueprintType)
enum class EOmniCharacterClass : uint8
{
	None				UMETA(DisplayName = "None"),
	Modern				UMETA(DisplayName = "Modern"),
	Medieval			UMETA(DisplayName = "Medieval")
};

UENUM(BlueprintType)
enum class ECharacterLocomotionState : uint8
{
	Undetermined		UMETA(DisplayName = "Undetermined"),
	Stationary			UMETA(DisplayName = "Stationary"),
	Walking				UMETA(DisplayName = "Walking"),
	Running				UMETA(DisplayName = "Running"),
	Falling				UMETA(DisplayName = "Falling")
};

UENUM(BlueprintType)
enum class EWeaponAction : uint8
{
	PrimaryAttack		UMETA(DisplayName = "Primary Attack"),
	SecondaryAttack		UMETA(DisplayName = "Secondary Attack"),
	CallThrownWeapon	UMETA(DisplayName = "Call Thrown Weapon")
};

UENUM(BlueprintType)
enum class EAnimationBodyPart : uint8
{
	FullBody			UMETA(DisplayName = "Full Body"),
	UpperBody			UMETA(DisplayName = "Upper Body"),
	LowerBody			UMETA(DisplayName = "Lower Body"),
};

UENUM(BlueprintType)
enum class EAttackSelection : uint8
{
	Randomized			UMETA(DisplayName = "Randomized"),
	Combo				UMETA(DisplayName = "Combo"),
	StateBased			UMETA(DisplayName = "StateBased")
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	NotApplicable		UMETA(DisplayName = "NotApplicable"),
	RegularAttack		UMETA(DisplayName = "RegularAttack"),
	Aimed				UMETA(DisplayName = "Aimed")
};

UENUM(BlueprintType)
enum class EAttackPhase : uint8
{
	Ready				UMETA(DisplayName = "Ready"),
	Ongoing				UMETA(DisplayName = "Ongoing"),
	Cooldown			UMETA(DisplayName = "Cooldown")
};

USTRUCT(BlueprintType)
struct FAttackConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Config")
	TSubclassOf<UOmniAttack> AttackClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Config")
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Config")
	float Range = 0;

	UPROPERTY(Transient)
	UOmniAttack* Attack;
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

USTRUCT(BlueprintType)
struct FAnimationDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AnimationMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAnimationBodyPart BodyPart;
};

USTRUCT(BlueprintType)
struct FInventoryState
{
	GENERATED_USTRUCT_BODY()
	
public:
	TObjectPtr<AOmniWeapon> OneHandedWeapon;
	TObjectPtr<AOmniWeapon> TwoHandedWeapon;
};
