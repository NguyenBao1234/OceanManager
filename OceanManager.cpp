// Fill out your copyright notice in the Description page of Project Settings.


#include "OceanManager.h"



AOceanManager::AOceanManager()
{
	Center = FVector(0, 0, 0);
	Size = 10000;
	WaveLength = 2500;
	Amplitude = 200;
	Direction = FVector2D(0, 1);
}

void AOceanManager::Initialize()
{
}

FVector AOceanManager::GetWaveHeight(FVector Location, float time)
{
	FVector sum = FVector(0, 0, 0);

	sum += CalculateGerstnerWaveCluster(WaveLength, Amplitude, FVector2D(Location.X, Location.Y), Direction, -0.015f, 0.5f, time, 0);
	sum += CalculateGerstnerWaveCluster(WaveLength * 0.6f, Amplitude * 0.6f, FVector2D(Location.X, Location.Y), Direction, 0.015f, 0.5f, time, 1.2f);

	return sum / 2;
}

FVector AOceanManager::CalculateGerstnerWave(float Wavelength, float amplitude, FVector2D position, FVector2D direction, float angle, float steepness, float time, float phase)
{
	float lambda = (2 * PI) / Wavelength;
	FVector Dir = FVector(direction.X, direction.Y, 0);
	Dir = Dir.RotateAngleAxis(angle * 360, FVector(0, 0, 1));
	FVector2D rotatedDirection = FVector2D(Dir.X, Dir.Y);
	rotatedDirection.Normalize();

	float wavePhase = lambda * FVector2D::DotProduct(rotatedDirection, position) + (time + phase);

	float c = FMath::Cos(wavePhase);
	float s = FMath::Sin(wavePhase);
	float QA = steepness * amplitude;

	return FVector(QA*rotatedDirection.X*c, QA*rotatedDirection.Y*c, amplitude*s);
}

FVector AOceanManager::CalculateGerstnerWaveCluster(float medianWavelength, float medianAmplitude, FVector2D position, FVector2D medianDirection, float medianAngle, float steepness, float time, float medianPhase)
{
	FVector sum = FVector(0, 0, 0);

	sum += CalculateGerstnerWave(medianWavelength, medianAmplitude, position, medianDirection, medianAngle , steepness, time, medianPhase);
	sum += CalculateGerstnerWave(medianWavelength * 0.5f, medianAmplitude * 0.5f, position, medianDirection, medianAngle - 0.058f, steepness, time, medianPhase + 1);
	sum += CalculateGerstnerWave(medianWavelength * 2.0f, medianAmplitude * 2.0f, position, medianDirection, medianAngle - 0.047f, steepness, time, medianPhase - 1.5f);
	sum += CalculateGerstnerWave(medianWavelength * 1.25f, medianAmplitude * 1.25f, position, medianDirection, medianAngle + 0.05f, steepness, time, medianPhase + 0.75f);
	sum += CalculateGerstnerWave(medianWavelength * 0.75f, medianAmplitude * 0.75f, position, medianDirection, medianAngle + 0.075f, steepness, time, medianPhase - 0.6f);
	sum += CalculateGerstnerWave(medianWavelength * 1.5f, medianAmplitude * 1.5f, position, medianDirection, medianAngle - 0.083f, steepness, time, medianPhase + 0.9f);
	sum += CalculateGerstnerWave(medianWavelength * 0.825f, medianAmplitude * 0.825f, position, medianDirection, medianAngle + 0.063f, steepness, time, medianPhase - 0.23f);
	sum += CalculateGerstnerWave(medianWavelength * 0.65f, medianAmplitude * 0.65f, position, medianDirection, medianAngle - 0.011f, steepness, time, medianPhase + 1.72f);

	return sum/8;
}
