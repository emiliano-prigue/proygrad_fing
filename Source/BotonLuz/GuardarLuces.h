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
class BOTONLUZ_API UGuardarLuces : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:	
	
	UFUNCTION(BlueprintCallable, Category = "Parsing")
	static void GuardarLucesArchivo(UObject* Context);
};
