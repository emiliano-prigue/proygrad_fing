
#include "BotonLuz.h"
#include "GuardarLuces.h"


AGuardarLuces::AGuardarLuces()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGuardarLuces::BeginPlay()
{
	Super::BeginPlay();
}

void AGuardarLuces::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AGuardarLuces::GuardarLucesArchivo()
{
	ofstream archivoLuces;
	archivoLuces.open("C:\\Users\\martinemr\\Documents\\Unreal Projects\\proygrad_fing\\archivoLucesGuardadas.txt");

	int tipoLuz;
	for (TActorIterator<ALuz> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ALuz* Luz = *ActorItr;
		if (Luz->IsA(ALuzPuntual::StaticClass()))
		{
			tipoLuz = 1;
		}
		else if (Luz->IsA(ALuzDireccional::StaticClass()))
		{
			tipoLuz = 2;
		}
		else if (Luz->IsA(ALuzFocal::StaticClass()))
		{
			tipoLuz = 3;
		}

		FVector posicionLuz = Luz->GetActorLocation();
		FRotator rotaciónLuz = Luz->GetActorRotation();
		FLinearColor colorLuz = Luz->getColor();

		string caracteristicasFocal = "\n";
		
		/*
		if (tipoLuz == 3)
		{
			ALuzFocal luzFocal = *Luz;
			
			float innerCone = luzFocal->innerCone;
			float outerCone = luzFocal->outerCone;
			caracteristicasFocal = "\n";
		}
		else
		{
			caracteristicasFocal = "\n";
		}
		*/
		
		archivoLuces << tipoLuz << ","
					<< posicionLuz.X << "," << posicionLuz.Y << "," << posicionLuz.Z 
					<< rotaciónLuz.Roll << "," << rotaciónLuz.Pitch << "," << rotaciónLuz.Yaw
					<< colorLuz.R << "," << colorLuz.G << "," << colorLuz.B
					<< Luz->getIntensidad() << caracteristicasFocal;
	}

	archivoLuces.close();
}