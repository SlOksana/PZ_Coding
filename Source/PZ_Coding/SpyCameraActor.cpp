// Fill out your copyright notice in the Description page of Project Settings.


#include "SpyCameraActor.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "BasePawn.h"
#include "TimerManager.h"
#include "Math/Color.h"
int32 Color = 50;
struct FLinearColor;

ASpyCameraActor::ASpyCameraActor()
{
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetBoxExtent(FVector(500.0f));
	BoxComp->SetCollisionObjectType(ECC_WorldStatic);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComp->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

}

void ASpyCameraActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASpyCameraActor::BoxBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ASpyCameraActor::BoxEndOverlap);

	//OnChangeColor.AddUFunction(this, "ChangeColor");

}

void ASpyCameraActor::ChangeColor()
{

	Material = Mesh->GetMaterial(0);

	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	Mesh->SetMaterial(0, DynamicMaterial);
	DynamicMaterial->SetScalarParameterValue"Color",1.0f);
	//const FLinearColor InColor;
	//FLinearColor ReturnColor = InColor;
	//ReturnColor.A = 6.0f;
	//DynamicMaterial->SetScalarParameterValue(TEXT("Color"), ReturnColor.A=6.0f);

	
	//MeshComp->SetMaterial(0, DetectedMaterial);
//	OnChangeColor.Broadcast();
	
}

void ASpyCameraActor::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FFromSweep, const FHitResult& SweepResult)
{

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 2.0f;
	PC->SetViewTarget(this, TransitionParams);

	GetWorldTimerManager().SetTimer(ChangeColorTimer, this, &ASpyCameraActor::ChangeColor, 1.0f, false);
	
}


void ASpyCameraActor::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 2.0f;
	PC->SetViewTarget(PC-> GetPawn(), TransitionParams);
	if (GetWorldTimerManager().IsTimerActive(ChangeColorTimer))
	{
		GetWorldTimerManager().ClearTimer(ChangeColorTimer);
	}
	
}
