#include "FSMStateCover.h"
#include "Engine/Engine.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "UObject/ConstructorHelpers.h"
#include "MasterAiController.h"

UFSMStateCover::UFSMStateCover()
{
	ConstructorHelpers::FObjectFinder<UEnvQuery> QueryAsset(TEXT("EnvQuery'/Game/Path/To/Your/EQSQuery.EQSQuery'"));
	if (QueryAsset.Succeeded())
	{
		CoverQuery = QueryAsset.Object;
	}
}

void UFSMStateCover::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Entering Cover State"));

	MasterAiController = Cast<AMasterAiController>(GetOuter());
	if (MasterAiController)
	{
		RunEQS();
	}
}

void UFSMStateCover::Update(float DeltaTime)
{
	// Update state logic if necessary
}

void UFSMStateCover::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("Exiting Cover State"));
}

void UFSMStateCover::RunEQS()
{
	if (CoverQuery && MasterAiController)
	{
		FEnvQueryRequest QueryRequest(CoverQuery, MasterAiController);
		QueryRequest.Execute(EEnvQueryRunMode::SingleResult, this, &UFSMStateCover::OnQueryFinished);
	}
}

void UFSMStateCover::OnQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
	if (Result->IsSuccsessful() && Result->GetItemScore(0) > 0.0f)
	{
		FVector BestLocation = Result->GetItemAsLocation(0);
		UE_LOG(LogTemp, Warning, TEXT("Best cover location found at: %s"), *BestLocation.ToString());

		// Move to the best location or perform any other action
		MasterAiController->MoveToLocation(BestLocation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid cover location found"));
	}
}
