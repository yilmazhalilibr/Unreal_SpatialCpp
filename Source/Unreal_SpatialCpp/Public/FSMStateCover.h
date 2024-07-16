#pragma once

#include "CoreMinimal.h"
#include "FSMBase.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "FSMStateCover.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SPATIALCPP_API UFSMStateCover : public UFSMBase
{
	GENERATED_BODY()

public:
	UFSMStateCover();

	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
	virtual void Exit() override;

private:
	void RunEQS();

	UPROPERTY()
	UEnvQuery* MyQuery; // set the query in editor
	FEnvQueryRequest* MyQueryRequest;

	UFUNCTION()
	void OnQueryFinished(TSharedPtr<FEnvQueryResult> Result);

	class AMasterAiController* MasterAiController;

	UPROPERTY()
	UEnvQuery* CoverQuery;
};
