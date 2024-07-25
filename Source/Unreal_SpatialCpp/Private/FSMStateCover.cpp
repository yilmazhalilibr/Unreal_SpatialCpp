#include "FSMStateCover.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "MasterAiController.h"

UFSMStateCover::UFSMStateCover()
{
	if (!CoverQuery)
	{

		ConstructorHelpers::FObjectFinder<UEnvQuery> QueryAsset(TEXT("/Game/FSM/EQS_Cover"));
		if (QueryAsset.Succeeded())
		{
			CoverQuery = QueryAsset.Object;
			UE_LOG(LogTemp, Warning, TEXT("Cover Query loaded successfully"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cover Query loaded failed"));

		}
	}
}

void UFSMStateCover::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering Cover State"));

	MasterAiController = Cast<AMasterAiController>(GetOuter());
	if (MasterAiController)
	{
		//Set focus player 
		ExecuteEQS();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MasterAiController is not valid"));
	}
}

void UFSMStateCover::Update(float DeltaTime)
{
	// Update state logic if necessary

	UE_LOG(LogTemp, Warning, TEXT("Updating Cover State"));

}

void UFSMStateCover::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Cover State"));
	//MasterAiController->SetFocus(GetWorld()->GetFirstPlayerController()->GetPawn());
	//// Clear focus
	//MasterAiController->ClearFocus(EAIFocusPriority::Gameplay);

}

void UFSMStateCover::ExecuteEQS()
{
	if (CoverQuery && MasterAiController)
	{
		FEnvQueryRequest QueryRequest(CoverQuery, MasterAiController->GetPawn());
		QueryRequest.Execute(EEnvQueryRunMode::SingleResult, FQueryFinishedSignature::CreateLambda(
			[this](TSharedPtr<FEnvQueryResult> Result)
			{
				if (Result->IsSuccessful() && Result->GetItemScore(0) > 0.0f)
				{
					CoverLocation = Result->GetItemAsLocation(0);
					UE_LOG(LogTemp, Warning, TEXT("Best cover location found at: %s"), *CoverLocation.ToString());

					// Move to the best location or perform any other action
					if (MasterAiController)
					{
						if (MasterAiController->MoveToLocation(CoverLocation) && !CoverLocation.IsZero())
						{
							UE_LOG(LogTemp, Warning, TEXT("Moving to cover location"));
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("Failed to move to cover location"));
							 
						}
						CoverLocation = FVector().Zero();
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("No valid cover location found"));
				}
			}
		));
	}
}