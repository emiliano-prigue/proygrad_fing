// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Luz.generated.h"

using namespace std;

UCLASS()
class BOTONLUZ_API ALuz : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALuz();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// -----------
	// Componentes
	// Nota: Se agregan las UBoxComponent porque las flechas de UE no tienen colisiones
	// -----------

	UPROPERTY(Category = StaticMeshActor, VisibleAnywhere, BlueprintReadOnly, Meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh", AllowPrivateAccess = "true"))
		UStaticMeshComponent * modeloLuz;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULightComponent* luz;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UArrowComponent* flechaX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UArrowComponent* flechaY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UArrowComponent* flechaZ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* colisionFlechaX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* colisionFlechaY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* colisionFlechaZ;

	// ----------------------------------------
	// Funciones para editar propiedades de luz
	// ----------------------------------------

	UFUNCTION(BlueprintCallable, Category = "Iluminacion")
		void setIntensidad(float intensidad);

	UFUNCTION(BlueprintCallable, Category = "Iluminacion")
		void setColor(FLinearColor color);

	UFUNCTION(BlueprintCallable, Category = "Iluminacion")
		void setPosicion(FVector posicion);

	//----------------------------------------
	// Funciones para manejar eventos de click
	// ---------------------------------------

	UFUNCTION(BlueprintCallable, Category = "Seleccion")
		// Evento de click en el modelo
		void onClickModelo(UPrimitiveComponent* pComponent);

	UFUNCTION(BlueprintCallable, Category = "Seleccion")
		// Evento de click en una flecha
		void onClickFlechaX(UPrimitiveComponent* pComponent);

	UFUNCTION(BlueprintCallable, Category = "Seleccion")
		// Evento de click en una flecha
		void onClickFlechaY(UPrimitiveComponent* pComponent);

	UFUNCTION(BlueprintCallable, Category = "Seleccion")
		// Evento de click en una flecha
		void onClickFlechaZ(UPrimitiveComponent* pComponent);

	UFUNCTION(BlueprintCallable, Category = "Seleccion")
		// Evento soltar click en una flecha
		void onReleasedFlecha(UPrimitiveComponent* pComponent);

	// -----------------------------------------------------------------------------
	// Funciones y variables para setear propiedades al seleccionar/deseleccionar luz
	// ------------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, Category = "Seleccion")
		void seleccionarActor();

	UFUNCTION(BlueprintCallable, Category = "Seleccion")
		void deseleccionarActor();

	UFUNCTION(BlueprintCallable, Category = "Seleccion")
		bool estaSeleccionada();

	UFUNCTION(BlueprintCallable, Category = "Seleccion")
		void aceptarSeleccion();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		bool seleccionado;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		bool seleccionadoNuevo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		int32 ejeSeleccionado;
};
