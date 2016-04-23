// Fill out your copyright notice in the Description page of Project Settings.

#include "BotonLuz.h"
#include "Luz.h"


// Sets default values
ALuz::ALuz()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	flechaX = CreateDefaultSubobject<UArrowComponent>(TEXT("flechaX"));
	flechaY = CreateDefaultSubobject<UArrowComponent>(TEXT("flechaY"));
	flechaZ = CreateDefaultSubobject<UArrowComponent>(TEXT("flechaZ"));
	flechaX->ArrowColor = FColor::Red;
	flechaY->ArrowColor = FColor::Green;
	flechaZ->ArrowColor = FColor::Blue;
	// Para que las flechas puedan ser vistas en el juego
	flechaX->SetHiddenInGame(false);
	flechaY->SetHiddenInGame(false);
	flechaZ->SetHiddenInGame(false);
	// Para que por defecto esten ocultas
	flechaX->SetVisibility(false);
	flechaY->SetVisibility(false);
	flechaZ->SetVisibility(false);
	// Rotar flechas para que esten alineadas a los ejes
	flechaY->RelativeRotation = FRotator(0, 90, 0);
	flechaZ->RelativeRotation = FRotator(90, 0, 0);
	// Creo subobject. La malla le sera asignada en las subclases
	modeloLuz = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ModeloLuz"));
	// Attachear las flechas al modelo. Todo se mueve junto
	flechaX->AttachTo(modeloLuz);
	flechaY->AttachTo(modeloLuz);
	flechaZ->AttachTo(modeloLuz);

	// Colisiones
	colisionFlechaX = CreateDefaultSubobject<UBoxComponent>(TEXT("colisionFlechaX"));
	colisionFlechaX->SetBoxExtent(FVector(70, 10, 10));
	colisionFlechaX->AttachTo(modeloLuz);
	colisionFlechaX->RelativeLocation = FVector(35, 0, 0);
	colisionFlechaX->SetSimulatePhysics(false);
	colisionFlechaX->bGenerateOverlapEvents = false;
	colisionFlechaX->SetCollisionProfileName(TEXT("OverlapAll"));

	colisionFlechaY = CreateDefaultSubobject<UBoxComponent>(TEXT("colisionFlechaY"));
	colisionFlechaY->SetBoxExtent(FVector(10, 70, 10));
	colisionFlechaY->AttachTo(modeloLuz);
	colisionFlechaY->RelativeLocation = FVector(0, 35, 0);
	colisionFlechaY->SetSimulatePhysics(false);
	colisionFlechaY->bGenerateOverlapEvents = false;
	colisionFlechaY->SetCollisionProfileName(TEXT("OverlapAll"));

	colisionFlechaZ = CreateDefaultSubobject<UBoxComponent>(TEXT("colisionFlechaZ"));
	colisionFlechaZ->SetBoxExtent(FVector(10, 10, 70));
	colisionFlechaZ->AttachTo(modeloLuz);
	colisionFlechaZ->RelativeLocation = FVector(0, 0, 35);
	colisionFlechaZ->SetSimulatePhysics(false);
	colisionFlechaZ->bGenerateOverlapEvents = false;
	colisionFlechaZ->SetCollisionProfileName(TEXT("OverlapAll"));

	// Seleccion
	seleccionado = false;
	seleccionadoNuevo = false;
	ejeSeleccionado = ' ';
	faltaSeleccionarLista = false;
}

// Called when the game starts or when spawned
void ALuz::BeginPlay()
{
	//Super::BeginPlay();
	UWorld* World = GetWorld();
	World->GetFirstPlayerController()->bEnableMouseOverEvents = true;
	modeloLuz->OnBeginCursorOver.AddDynamic(this, &ALuz::onClickModelo);
	colisionFlechaX->OnBeginCursorOver.AddDynamic(this, &ALuz::onClickFlechaX);
	colisionFlechaY->OnBeginCursorOver.AddDynamic(this, &ALuz::onClickFlechaY);
	colisionFlechaZ->OnBeginCursorOver.AddDynamic(this, &ALuz::onClickFlechaZ);
	colisionFlechaX->OnEndCursorOver.AddDynamic(this, &ALuz::onReleasedFlecha);
	colisionFlechaY->OnEndCursorOver.AddDynamic(this, &ALuz::onReleasedFlecha);
	colisionFlechaZ->OnEndCursorOver.AddDynamic(this, &ALuz::onReleasedFlecha);
}

// Called every frame
void ALuz::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Setear intensidad de la luz
void ALuz::setIntensidad(float intensidad){
	luz->SetIntensity(intensidad);
}

// Setear color de la luz
void ALuz::setColor(FLinearColor color){
	luz->SetLightColor(color);
}

// Setear posicion del actor
void ALuz::setPosicion(FVector posicion){
	modeloLuz->SetWorldLocation(posicion);
}

void ALuz::seleccionarActor(){
	// Deseleccionar el resto de las luces
	for (TActorIterator<ALuz> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ALuz* luz = *ActorItr;
		luz->deseleccionarActor();
	}
	// Selecciono esta
	flechaX->SetHiddenInGame(false);
	flechaY->SetHiddenInGame(false);
	flechaZ->SetHiddenInGame(false);
	flechaX->SetVisibility(true);
	flechaY->SetVisibility(true);
	flechaZ->SetVisibility(true);
	colisionFlechaX->SetCollisionProfileName(TEXT("BlockAll"));
	colisionFlechaY->SetCollisionProfileName(TEXT("BlockAll"));
	colisionFlechaZ->SetCollisionProfileName(TEXT("BlockAll"));
	seleccionado = true;
	seleccionadoNuevo = false;

}

void ALuz::aceptarSeleccion(){
	seleccionadoNuevo = false;
}

void ALuz::deseleccionarActor(){
	flechaX->SetVisibility(false);
	flechaY->SetVisibility(false);
	flechaZ->SetVisibility(false);
	flechaX->SetArrowColor_New(FLinearColor::Red);
	flechaY->SetArrowColor_New(FLinearColor::Green);
	flechaZ->SetArrowColor_New(FLinearColor::Blue);
	colisionFlechaX->SetCollisionProfileName(TEXT("OverlapAll"));
	colisionFlechaY->SetCollisionProfileName(TEXT("OverlapAll"));
	colisionFlechaZ->SetCollisionProfileName(TEXT("OverlapAll"));
	seleccionado = false;
	ejeSeleccionado = 0;
	
}

void ALuz::onClickModelo(UPrimitiveComponent* pComponent){
	//FString s = "Selecciona";
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s);
	seleccionarActor();
	faltaSeleccionarLista = true;
}

void ALuz::seleccionarDesdeLista(){
	seleccionarActor();
	false;
}

void ALuz::onClickFlechaX(UPrimitiveComponent* pComponent){
	//FString s = "Click flecha";
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s);
	flechaX->SetArrowColor_New(FLinearColor::Yellow);
	flechaY->SetArrowColor_New(FLinearColor::Green);
	flechaZ->SetArrowColor_New(FLinearColor::Blue);
	ejeSeleccionado = 1;
}

void ALuz::onClickFlechaY(UPrimitiveComponent* pComponent){
	//FString s = "Click flecha";
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s);
	flechaX->SetArrowColor_New(FLinearColor::Red);
	flechaY->SetArrowColor_New(FLinearColor::Yellow);
	flechaZ->SetArrowColor_New(FLinearColor::Blue);
	ejeSeleccionado = 2;
}

void ALuz::onClickFlechaZ(UPrimitiveComponent* pComponent){
	//FString s = "Click flecha";
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s);
	flechaX->SetArrowColor_New(FLinearColor::Red);
	flechaY->SetArrowColor_New(FLinearColor::Green);
	flechaZ->SetArrowColor_New(FLinearColor::Yellow);
	ejeSeleccionado = 3;
}

void ALuz::onReleasedFlecha(UPrimitiveComponent* pComponent){
	//FString s = "Suelta flecha";
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s);
}

bool ALuz::estaSeleccionada(){
	return seleccionado;
}
