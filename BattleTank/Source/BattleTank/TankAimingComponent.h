// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reload, Aiming, Locked, OutOfAmmo
};

//Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;


// Hold barrel´s properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "setup")
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	UFUNCTION(BlueprintCallable)
	void fire();

	EFiringStatus GetFiringStatus()const;

	UFUNCTION(BlueprintCallable)
	int32 GetRoundsLeft() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "state")
	EFiringStatus FiringStatus = EFiringStatus::Reload;

	

private:

	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel * Barrel = nullptr;

	UTankTurret * Turret = nullptr;

	FVector AimDirection;

	void MoveBarrelTowards(FVector AimDirection);
	
	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Fireing")
	float  LaunchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = " Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Fireing")
	double ReloadTimeInSeconds = 3;

	bool IsBarrelMoving() const;

	int32 RoundsLeft = 3;
};
