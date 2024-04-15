// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OceanManager.generated.h"

UCLASS()
class TPSGAMECPP_API AOceanManager : public AActor
{
	GENERATED_BODY()
	
public:
	AOceanManager();

	UPROPERTY(BlueprintReadWrite, Category = "General", EditAnywhere)
		FVector Center;
	UPROPERTY(BlueprintReadWrite, Category = "General", EditAnywhere)
		float Size;
	UPROPERTY(BlueprintReadWrite, Category = "General", EditAnywhere)
		float MaxHeight;

//Ocean
	UPROPERTY(BlueprintReadWrite, Category = "Ocean", EditAnywhere)
		float WaveLength;
	UPROPERTY(BlueprintReadWrite, Category = "Ocean", EditAnywhere)
		float Amplitude;
	UPROPERTY(BlueprintReadWrite, Category = "Ocean", EditAnywhere)
		FVector2D Direction;
	
	UFUNCTION(BlueprintCallable, Category = "Ocean")
		void Initialize();
	UFUNCTION(BlueprintCallable, Category = "Ocean")
		FVector GetWaveHeight(FVector Location, float time);

private:
	FVector CalculateGerstnerWave(float Wavelength, float amplitude, FVector2D position, FVector2D direction, float angle, float steepness, float time, float phase);
	FVector CalculateGerstnerWaveCluster(float medianWavelength, float medianAmplitude, FVector2D position, FVector2D medianDirection, float medianAngle, float steepness, float time, float medianPhase);
};
