#pragma once

#include "CoreMinimal.h"
#include "BallPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include "Ball.generated.h"

UCLASS()
class BALLMANIA_API ABall : public APawn
{
	GENERATED_BODY()

public:

	ABall();

protected:

	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body")
	USphereComponent* BallCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body")
	USkeletalMeshComponent* BallMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body")
	USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body")
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveForce;
	
protected:

	void Move(const FInputActionValue& Value);
	void Look();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
		
	UPROPERTY()
	ABallPlayerController* BallPlayerController;
};
