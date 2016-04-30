#pragma once

#include "GameFramework/Actor.h"
#include <iostream>
#include <fstream>
#include "Luz.h"
#include "LuzPuntual.h"
#include "LuzDireccional.h"
#include "LuzFocal.h"
#include "GuardarLuces.generated.h"

using namespace std;

UCLASS()
class BOTONLUZ_API AGuardarLuces : public AActor
{
	GENERATED_BODY()
	
public:	
	AGuardarLuces();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Parsing")
		void GuardarLucesArchivo();
};
