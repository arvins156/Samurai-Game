// Fill out your copyright notice in the Description page of Project Settings.

#include "SamuraiCharacter.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Katana.h"
#include "Components/CapsuleComponent.h"
#include "SamuraiGameGameMode.h"

// Sets default values
ASamuraiCharacter::ASamuraiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASamuraiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	//Katana = GetWorld()->SpawnActor<AKatana>(KatanaClass);
	//GetMesh()->HideBoneByName(TEXT(""), EPhysBodyOp::PBO_None);
	//Katana->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightHand"));
	//Katana->SetOwner(this);
}

bool ASamuraiCharacter::IsDead() const
{
	return Health <= 0;
}

float ASamuraiCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void ASamuraiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASamuraiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Call the parent version
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	// Get the local player enhanced input subsystem
	auto EISubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	// Clear out existing mapping, add our mapping
	EISubSystem->ClearAllMappings();
	// Add the input mapping context
	EISubSystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PlayerEIComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (PlayerEIComponent != nullptr) {

	// Bind the actions
	//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
	//ETriggerEvent is an enum, where Triggered means "button is held down"

		UE_LOG(LogTemp, Warning, TEXT("PEI WORKED."));
		PlayerEIComponent->BindAction(InputMove, ETriggerEvent::Triggered, this, &ASamuraiCharacter::Move);
		PlayerEIComponent->BindAction(InputLook, ETriggerEvent::Triggered, this, &ASamuraiCharacter::Look);
		PlayerEIComponent->BindAction(InputJump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		PlayerEIComponent->BindAction(InputShoot, ETriggerEvent::Started, this, &ASamuraiCharacter::Attack);
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("PEI FAILED."));
	}
}

float ASamuraiCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead()) {

		ASamuraiGameGameMode* GameMode = GetWorld()->GetAuthGameMode<ASamuraiGameGameMode>();
		if (GameMode != nullptr) {

			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

void ASamuraiCharacter::Move(const FInputActionValue& Value) {

	UE_LOG(LogTemp, Warning, TEXT("Moved"));

	// Directional movement

	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);

	// Previous movement implementation:

	// const FVector2D MovementVector = Value.Get<FVector2D>();
	// const FVector Forward = GetActorForwardVector();
	// const FVector Right = GetActorRightVector();

	// AddMovementInput(Forward, MovementVector.Y);
	// AddMovementInput(Right, MovementVector.X);
}

void ASamuraiCharacter::Look(const FInputActionValue& Value) {
	
	UE_LOG(LogTemp, Warning, TEXT("Looked"));	

	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void ASamuraiCharacter::Attack()
{
	Katana->PullTrigger();
}

