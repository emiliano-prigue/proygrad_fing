// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Luz.h"
#include "LuzFocal.generated.h"

/**
 * 
 */
UCLASS()
class BOTONLUZ_API ALuzFocal : public ALuz
{
	GENERATED_BODY()
public:
	ALuzFocal();

	float getAnguloConoInterior();

	UFUNCTION(BlueprintCallable, Category = "LuzFocal")
	void setAnguloConoInterior(float parAngulo);

	float getAnguloConoExterior();

	UFUNCTION(BlueprintCallable, Category = "LuzFocal")
	void setAnguloConoExterior(float parAngulo);
};
