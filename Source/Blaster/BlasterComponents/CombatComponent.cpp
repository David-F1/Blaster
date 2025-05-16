

#include "CombatComponent.h"
#include "Blaster/Weapons/Weapon.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"


UCombatComponent::UCombatComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	BaseWalkSpeed = 600.f;
	AimWalkSpeed = 450.f;
	
}



void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CharacterRef)
	{
		CharacterRef->GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	}
	
}



void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, EquippedWeapon);
	DOREPLIFETIME(UCombatComponent, bAiming);
}

void UCombatComponent::EquipWeapon(AWeapon* WeaponToEquip)
{
	if (CharacterRef == nullptr || WeaponToEquip == nullptr) return; 

	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetWeaponState(EWeaponstate::EWS_Equipped);
	const USkeletalMeshSocket* HandSocket = CharacterRef->GetMesh()->GetSocketByName(FName("RightHandSocket"));
	if (HandSocket)
	{
		HandSocket->AttachActor(EquippedWeapon, CharacterRef->GetMesh());
	}
	EquippedWeapon->SetOwner(CharacterRef);

	CharacterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
	CharacterRef->bUseControllerRotationYaw = true;
}

void UCombatComponent::OnRep_EquippedWeapon()
{
	if (EquippedWeapon && CharacterRef)
	{
		CharacterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		CharacterRef->bUseControllerRotationYaw = true;
	}

}


void UCombatComponent::SetAiming(bool bIsAiming)
{
	bAiming = bIsAiming;

	ServerSetAiming(bIsAiming);
	if (CharacterRef)
	{
		CharacterRef->GetCharacterMovement()->MaxWalkSpeed = bIsAiming ? AimWalkSpeed : BaseWalkSpeed;
	}
}


void UCombatComponent::ServerSetAiming_Implementation(bool bIsAiming)
{
	bAiming = bIsAiming;
	if (CharacterRef)
	{
		CharacterRef->GetCharacterMovement()->MaxWalkSpeed = bIsAiming ? AimWalkSpeed : BaseWalkSpeed;
	}
}
