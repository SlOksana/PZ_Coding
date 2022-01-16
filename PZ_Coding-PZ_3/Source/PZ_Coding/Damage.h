// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Damage.generated.h"

DECLARE_EVENT(ADamage, FDamage);
class UBoxComponent;

UCLASS()
class PZ_CODING_API ADamage: public AActor
{
	GENERATED_BODY()
	
public:
	ADamage();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* BoxCollision;
		
	UFUNCTION(BlueprintCallable)
	void HealthDamage();

	UFUNCTION(BlueprintCallable)
	void Health();

	UFUNCTION()
    void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
	FDamage Damage;
	FTimerHandle DamageTimer;
	bool bHealth;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
