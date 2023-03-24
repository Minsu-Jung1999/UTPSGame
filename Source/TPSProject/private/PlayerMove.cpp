// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"

void UPlayerMove::Turn(float value)
{
	me->AddControllerYawInput(value);

}

void UPlayerMove::LookUp(float value)
{
	me->AddControllerPitchInput(value);
}

void UPlayerMove::SetupInputBinding(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &UPlayerMove::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &UPlayerMove::LookUp);

	//�¿� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &UPlayerMove::InputHorizontal);
	//���� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &UPlayerMove::InputVertical);
	//���� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &UPlayerMove::InputJump);
	// �޸��� �Է� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &UPlayerMove::InputRun);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &UPlayerMove::InputRun);

}


void UPlayerMove::InputHorizontal(float value)
{
	direction.Y = value;
}

void UPlayerMove::InputVertical(float value)
{
	direction.X = value;
}

void UPlayerMove::InputJump()
{
	me->Jump();
}

void UPlayerMove::Move()
{
	// �÷��̾� �̵� ó��
	// ��� �
	// P(��� ��ġ) = PO(���� ��ġ)+ v(�ӵ�) x t(�ð�)
	direction = FTransform(me->GetControlRotation()).TransformVector(direction);
	/*FVector PO = GetActorLocation();
	FVector vt = direction * walkSpeed * DeltaTime;
	FVector P = PO + vt;
	SetActorLocation(P);*/
	me->AddMovementInput(direction);
	direction = FVector::ZeroVector;
}

UPlayerMove::UPlayerMove()
{
	// Tick �Լ��� ȣ��ǵ��� ó��
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	// �ʱ� �ӵ��� �ȱ�� ����
	moveComp->MaxWalkSpeed = walkSpeed;

}

void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Move();


}

void UPlayerMove::InputRun()
{
	auto movement = moveComp;
	// ���� �޸��� �����
	if (movement->MaxWalkSpeed > walkSpeed)
	{
		// �ȱ� �ӵ��� ��ȯ
		movement->MaxWalkSpeed = walkSpeed;
	}
	else
	{
		movement->MaxWalkSpeed = runSpeed;
	}
}

