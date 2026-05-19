// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChargePlayer.h"

#include "AIController.h"
#include "RECloneCharacter.h"

/*
EBTNodeResult::Type UBTT_ChargePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* OwningController = OwnerComp.GetAIOwner();

	
	if (OwningController == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,FString::Printf("No controller for enemy AI"));
		return EBTNodeResult::Failed;
	}
	else
	{
	
		if (PlayerCharacter == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,FString::Printf("No player character to chase"));
			return EBTNodeResult::Failed;
		}
		else
		{
			OwningController->MoveToActor(PlayerCharacter,5.f, true);
		}
	}
	return EBTNodeResult::Succeeded;
}*/ 
