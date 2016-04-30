// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include <list>
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
	FString tipoDeLuz;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
	float rotX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
	float rotY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atributos")
	float rotZ;

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
		float getIntensidad();

	UFUNCTION(BlueprintCallable, Category = "Iluminacion")
		void setIntensidad(float intensidad);

	UFUNCTION(BlueprintCallable, Category = "Iluminacion")
		FLinearColor getColor();

	UFUNCTION(BlueprintCallable, Category = "Iluminacion")
		void setColor(FLinearColor color);

	UFUNCTION(BlueprintCallable, Category = "Iluminacion")
		void setPosicion(FVector posicion);

	// Se rota solamente la luz, no el modelo ni las flechas
	// rx= roll
	// ry = pitch
	// rz = yaw
	UFUNCTION(BlueprintCallable, Category = "Iluminacion")
		void setRotacion(float rx, float ry, float rz);

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

	// Solo seleccionar luz con esta funcion en el caso de que se este
	// seleccionando desde el widget de la lista de luces en pantalla
	UFUNCTION(BlueprintCallable, Category = "Seleccion")
	void seleccionarDesdeLista();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		bool seleccionado;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		bool seleccionadoNuevo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		int32 ejeSeleccionado;

	// Este campo es para avisarle a la lista de luces en pantalla que debe
	// marcar la linea como seleccionada
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seleccion")
	bool faltaSeleccionarLista;


};
