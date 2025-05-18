// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlasterCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ABlasterCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;


protected:
	
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EquipedButtonPressed();
	void CrouchButtonPressed();
	void AimButtonPressed();
	void AimButtonReleased();
	void AimOffset(float Deltatime);

private:
	 UPROPERTY(VisibleAnywhere, Category = "Camera")
	 USpringArmComponent* CameraBoom;
	 UPROPERTY(VisibleAnywhere,  Category = "Camera")
	 UCameraComponent* FollowCamera;
	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	 class UWidgetComponent* OverheadWidget;

#pragma region Input Variables
	 UPROPERTY(EditAnywhere, Category = "Input")
	 UInputMappingContext* DefaultMappingContext;
	 UPROPERTY(EditAnywhere, Category = "Input")
	 UInputAction* MoveAction;
	 UPROPERTY(EditAnywhere, Category = "Input")
	 UInputAction* LookAction;
	 UPROPERTY(EditAnywhere, Category = "Input")
	 UInputAction* JumpAction;
	 UPROPERTY(EditAnywhere, Category = "Input")
	 UInputAction* EquipAction;
	 UPROPERTY(EditAnywhere, Category = "Input")
	 UInputAction* CrouchAction;
	 UPROPERTY(EditAnywhere, Category = "Input")
	 UInputAction* AimAction;
#pragma endregion

	 UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	 class AWeapon* OverlappingWeapon;

	 UFUNCTION()
	 void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	 UPROPERTY(VisibleAnywhere)
	 class UCombatComponent* CombatComponent;

	 UFUNCTION(Server, Reliable)
	 void ServerEquipButtonPressed();

	 float AO_Yaw;
	 float AO_Pitch;
	 FRotator StartingAimRotation;

public:
	void SetOverlappingWeapons(AWeapon* Weapon);

	bool IsWeaponEquipped();
	bool IsAiming();

	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
};
