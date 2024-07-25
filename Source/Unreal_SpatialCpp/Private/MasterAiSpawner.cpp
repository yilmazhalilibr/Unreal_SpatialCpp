// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterAiSpawner.h"
#include "MasterAiShooter.h"
#include "MasterAiController.h"
#include <Kismet/GameplayStatics.h>



// Sets default values
AMasterAiSpawner::AMasterAiSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AMasterAiSpawner::BeginPlay()
{
	Super::BeginPlay();

	//Timer oluþtur Lambda ile 5 saniye de bir EQS çalýþtýr
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			ExecuteEQS("Attack");
			ExecuteEQS("Cover");
			//ExecuteEQS("Chase");

		}, 5.0f, true);



}


// Called every frame
void AMasterAiSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMasterAiSpawner::SpawnMasterAi(int _spawnCount)
{
	if (!BPMasterAiShooterClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Master AI Class Not Set"));
		return;
	}

	AMasterAiShooter* MasterAiShooter = BPMasterAiShooterClass.GetDefaultObject();

	for (int i = 0; i < _spawnCount; i++)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParams.Owner = this;

		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		//Spawn Master AI

		AMasterAiShooter* MasterAi = GetWorld()->SpawnActor<AMasterAiShooter>(BPMasterAiShooterClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (MasterAi)
		{
			UE_LOG(LogTemp, Warning, TEXT("Master AI Spawned"));
			MasterAiSpawnedList.Add(MasterAi);
			MasterAi->OnAiDead.AddUObject(this, &AMasterAiSpawner::DeadMasterAi);
			MasterAi->SetSpawner(this);

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Master AI Spawned Failed"));
		}

	}

}

FVector AMasterAiSpawner::GetAttackCordinate(AMasterAiShooter* _ai)
{
	if (AttackCordinates.Contains(_ai))
	{
		WarningPlayerDetected(true);

		return AttackCordinates.FindRef(_ai);

	}
	else
	{
		return FVector::ZeroVector;
	}
}

FVector AMasterAiSpawner::GetCoverCordinate(AMasterAiShooter* _ai)
{
	if (CoverCordinates.Contains(_ai))
	{
		return CoverCordinates.FindRef(_ai);
	}
	else
	{
		return FVector::ZeroVector;
	}
}

void AMasterAiSpawner::HandleAttackCordinateToCover(FName _eqsName)
{
	UEnvQuery* _eqs = QueryMap.FindRef(_eqsName);
	if (_eqs)
	{
		FEnvQueryRequest QueryRequest(_eqs, GetWorld()->GetFirstPlayerController()->GetPawn());
		QueryRequest.Execute(EEnvQueryRunMode::AllMatching, FQueryFinishedSignature::CreateLambda(
			[this, _eqsName](TSharedPtr<FEnvQueryResult> Result)
			{
				if (Result->IsSuccessful() && Result->Items.Num() > 0)
				{
					
					for (int32 i = 0; i < Result->Items.Num(); i++)
					{
						FVector CoverLocation = Result->GetItemAsLocation(i);
						FVector StartLocation = CoverLocation + FVector(0, 0, 150);
						FVector EndLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() + FVector(0,0,50);

						FHitResult HitResult;
						FCollisionQueryParams CollisionParamsForEQSCover;

						CollisionParamsForEQSCover.AddIgnoredActor(this);
						// Belirli bir sýnýfa ait tüm aktörleri göz ardý et
						TArray<AActor*> IgnoredActors;
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMasterAiShooter::StaticClass(), IgnoredActors);
						for (AActor* Actor : IgnoredActors)
						{
							CollisionParamsForEQSCover.AddIgnoredActor(Actor);
						}


						bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Pawn, CollisionParamsForEQSCover);

						// Draw Debug Line
						//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 10.0f, 0, 1.0f);

						if (bHit)
						{
							if (HitResult.GetActor())
							{
								//UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName());
								if (HitResult.GetActor()->Tags.Contains("Player"))
								{

									if (FVector::Dist(CoverLocation, EndLocation) < 500)
									{
										//AttackCordinates.Add(nullptr, CoverLocation);
										DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 10.0f, 0, 1.0f);
										AttackCordinates.Add(MasterAiSpawnedList[i % MasterAiSpawnedList.Num()], CoverLocation);

									}

								}
							}
							else
							{
								UE_LOG(LogTemp, Warning, TEXT("Hit but no actor found"));
							}
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("No hit detected"));
						}
					}
				}
			}
		));
	}
}

void AMasterAiSpawner::ExecuteEQS(FName _eqsName)
{
	if (QueryMap.Contains(_eqsName))
	{
		UEnvQuery* _eqs = QueryMap.FindRef(_eqsName);
		if (_eqs)
		{
			FEnvQueryRequest QueryRequest(_eqs, GetWorld()->GetFirstPlayerController()->GetPawn());
			QueryRequest.Execute(EEnvQueryRunMode::AllMatching, FQueryFinishedSignature::CreateLambda(
				[this, _eqsName](TSharedPtr<FEnvQueryResult> Result)
				{
					if (Result->IsSuccessful() && Result->Items.Num() > 0)
					{
						int32 ItemIndex = 0;
						int32 NumItems = Result->Items.Num();
						int32 HalfNumItems = NumItems / 2;

						if (_eqsName == "Attack")
						{
							AttackCordinates.Empty();

							HandleAttackCordinateToCover("Cover");

							for (AMasterAiShooter* Ai : MasterAiSpawnedList)
							{
								if (Ai && ItemIndex < NumItems)
								{
									FVector Location;

									if (ItemIndex % 2 == 0)
									{
										// Çift sayý ise baþtan ekle
										Location = Result->GetItemAsLocation(ItemIndex / 2);
									}
									else
									{
										// Tek sayý ise ortadan sona doðru ekle
										Location = Result->GetItemAsLocation(HalfNumItems + (ItemIndex / 2));
									}

									AttackCordinates.Add(Ai, Location);
									ItemIndex++;
								}
							}
						}
						else if (_eqsName == "Cover")
						{
							CoverCordinates.Empty();

							for (AMasterAiShooter* Ai : MasterAiSpawnedList)
							{
								if (Ai && ItemIndex < NumItems)
								{
									FVector Location;

									if (ItemIndex % 2 == 0)
									{
										// Çift sayý ise baþtan ekle
										Location = Result->GetItemAsLocation(ItemIndex / 2);
									}
									else
									{
										// Tek sayý ise ortadan sona doðru ekle
										Location = Result->GetItemAsLocation(HalfNumItems + (ItemIndex / 2));
									}

									CoverCordinates.Add(Ai, Location);
									ItemIndex++;
								}
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
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EQS Not Found"));
	}
}


void AMasterAiSpawner::DeadMasterAi(AMasterAiShooter* _deadAi, bool _dead)
{
	if (MasterAiSpawnedList.Contains(_deadAi) && _dead)
	{
		MasterAiSpawnedList.Remove(_deadAi);
	}
}


//Warn all AI's that player is detected -> All AI's will be in War Mode
void AMasterAiSpawner::WarningPlayerDetected(bool _isDetected)
{
	if (_isDetected)
	{

		for (AMasterAiShooter* Ai : MasterAiSpawnedList)
		{
			if (Ai)
			{
				//MasterAiController cast to Ai Controller
				AMasterAiController* _aiController = Cast<AMasterAiController>(Ai->GetController());
				if (_aiController)
				{
					_aiController->SetOnWarMode(true);

				}
			}
		}
	}
	else
	{
		for (AMasterAiShooter* Ai : MasterAiSpawnedList)
		{
			if (Ai)
			{
				//MasterAiController cast to Ai Controller
				AMasterAiController* _aiController = Cast<AMasterAiController>(Ai->GetController());
				if (_aiController)
				{
					_aiController->SetOnWarMode(false);
				}
			}
		}
	}

}


