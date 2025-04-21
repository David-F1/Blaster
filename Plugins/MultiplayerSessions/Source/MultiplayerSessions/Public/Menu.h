// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/onlineSessionInterface.h"

#include "Menu.generated.h"

/**
 * 
 */

UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumOfPublicConnection = 4, FString TypeOfMatch = FString(TEXT("Free forAll")), FString LobbyPath = FString(TEXT("/Game/ThirdPerson/Maps/Lobby?listen")));

protected:

	virtual bool Initialize() override; 
	virtual void NativeDestruct() override;

#pragma region  Callbacks for the delegates on the MultiplayerSessionSubsystem
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);


#pragma endregion
	
	
private:
	UPROPERTY(meta = (BindWidget))
	class  UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();

	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;
	

	int32 NumPublicConnections{4};
	FString MatchType{ TEXT("Free For All") };
	FString PathToLobby{ TEXT("") };

};
