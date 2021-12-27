#include "Cube.h"
#include "MovieSceneFwd.h"
#include "Components/BoxComponent.h"

ACube::ACube()
{
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>("Cube");
	Cube->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Geometry/Meshes/1M_Cube_Chamfer"));

	if (Mesh.Succeeded())
	{
		Cube->SetStaticMesh(Mesh.Object);
	}
}

void ACube::BeginPlay()
{
	Super::BeginPlay();
  status = Status::Moving;
	GetWorldTimerManager().SetTimer(StatusTimer,this,&ThisClass::Status,2.0f,true,-1);
}

void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACube::Status()
{
	if(status == Status::Moving)
	{
		status = Status::Stopped;
		//GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Black,TEXT("Stopped"));
	}
	else
	{
		status = Status::Moving;
		//GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,TEXT("Moving"));
	}
}


