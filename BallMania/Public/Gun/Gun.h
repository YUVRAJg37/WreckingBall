// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallPlayerController.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class BALLMANIA_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	void Look();
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* GunCollisionLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* GunCollisionRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"))
	USphereComponent* PickUpCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* GunMesh;

	UPROPERTY()
	ABallPlayerController* BallPlayerController;

public:

	FORCEINLINE USceneComponent* GetRoot() const {return Root;}

};
