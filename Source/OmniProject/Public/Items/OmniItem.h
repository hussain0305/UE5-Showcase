#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OmniItem.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class OMNIPROJECT_API AOmniItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AOmniItem();

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

protected:

	virtual void BeginPlay() override;	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Item Presentation")
	float TransformedSin();

	UFUNCTION(BlueprintPure, Category = "Item Presentation")
	float TransformedCos();

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	float GameTime;
};
