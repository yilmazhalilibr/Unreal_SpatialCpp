#include "FSMStateCover.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "MasterAiController.h"

UFSMStateCover::UFSMStateCover()
{
	ConstructorHelpers::FObjectFinder<UEnvQuery> QueryAsset(TEXT("/Game/FSM/EQS_Cover"));
	if (QueryAsset.Succeeded())
	{
		CoverQuery = QueryAsset.Object;
		UE_LOG(LogTemp, Warning, TEXT("Cover Query loaded successfully"));
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
				if (Result->IsSuccsessful() && Result->GetItemScore(0) > 0.0f)
				{
					FVector BestLocation = Result->GetItemAsLocation(0);
					UE_LOG(LogTemp, Warning, TEXT("Best cover location found at: %s"), *BestLocation.ToString());

					// Move to the best location or perform any other action
					if (MasterAiController)
					{
						if (MasterAiController->MoveToLocation(BestLocation))
						{
							UE_LOG(LogTemp, Warning, TEXT("Moving to cover location"));
						}
						else
						{

							UE_LOG(LogTemp, Warning, TEXT("Failed to move to cover location"));

						}


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