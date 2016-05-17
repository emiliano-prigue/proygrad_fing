
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
class BOTONLUZ_API UCreadorLuces : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:	
	
	UFUNCTION(BlueprintCallable, Category = "Parsing")
	static TArray <ALuz*> ParsearArchivoLuces(UObject* Context);
};
