// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "GameFramework/Actor.h"
#include "Luz.h"
#include "LuzPuntual.h"
#include "LuzDireccional.h"
#include "LuzFocal.h"
#include "UnrealEd.h"
#include "CreadorLuces.generated.h"

using namespace std;

UCLASS()
class BOTONLUZ_API ACreadorLuces : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACreadorLuces();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Parsing")
		TArray <ALuz*> ParsearArchivoLuces();
};
