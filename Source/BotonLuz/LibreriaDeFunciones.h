// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "LibreriaDeFunciones.generated.h"

/**
 * 
 */
UCLASS()
class BOTONLUZ_API ULibreriaDeFunciones : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:	
		// Se genera esta funcion porque desde el blueprint no se puede acceder
		// a la intensidad de una luz
		UFUNCTION(BlueprintCallable, Category = "Funciones Auxiliares")
		static float obtenerIntensidadLuz(ALight* luz);

		UFUNCTION(BlueprintCallable, Category = "Funciones Auxiliares")
		static float redondear(float aRedondear);

		UFUNCTION(BlueprintCallable, Category = "Funciones Auxiliares")
		static FRotator obtenerRotacionDeComponente(ULightComponent* luz);

	
};
