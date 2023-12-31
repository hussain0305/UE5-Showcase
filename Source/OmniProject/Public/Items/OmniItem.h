#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OmniGlobal.h"
#include "OmniItem.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class OMNIPROJECT_API AOmniItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AOmniItem();

//==============================
//Pointers, Variables and Fields
//==============================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Item Component")
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Item Component")
		USphereComponent* SphereComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Item Presentation")
		float MovementRate = 50.f;
	UPROPERTY(EditDefaultsOnly, Category = "Item Presentation")
		float RotationRate = 60.f;
	UPROPERTY(EditDefaultsOnly, Category = "Item Presentation")
		float Amplitude = 0.25f;
	UPROPERTY(EditDefaultsOnly, Category = "Item Presentation")
		float TimeConstant = 5.f;


//=========
//Functions
//=========

	UFUNCTION(BlueprintCallable)
		virtual void ItemEquipped();
	UFUNCTION(BlueprintCallable)
		void SetItemState(const EItemState NewState);

//==================================
//Setters, Getters, Inline Functions
//==================================

	UFUNCTION(BlueprintCallable)
		FORCEINLINE EItemState GetItemState() const { return ItemState; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsPickup() const { return ItemState == EItemState::Pickup; }

protected:

	virtual void BeginPlay() override;	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintPure, Category = "Item Presentation")
		float TransformedSin();
	UFUNCTION(BlueprintPure, Category = "Item Presentation")
		float TransformedCos();
	UFUNCTION()
		virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		virtual void RoutineAsAPickup();

private:

	EItemState ItemState = EItemState::Pickup;
	float GameTime;
};
