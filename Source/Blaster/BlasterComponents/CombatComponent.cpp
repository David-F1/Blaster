

#include "CombatComponent.h"
#include "Blaster/Weapons/Weapon.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Engine/SkeletalMeshSocket.h"


UCombatComponent::UCombatComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	
}



void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}



void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


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
	EquippedWeapon->ShowPickupWidget(false);
}



