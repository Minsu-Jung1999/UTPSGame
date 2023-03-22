// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// ���� �ð� �ֱ�
	//InitialLifeSpan = 2.0f;




	// 1. �浹ü ����ϱ�
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	// 2. �浹�������� ����
	collisionComp->SetCollisionProfileName(TEXT("BlackAll")); // BlackAll ��� ��ü��� �浹�� �̸�Ű���� ��
	// 3. �浹ü ũ�� ����
	collisionComp->SetSphereRadius(13);
	// 4. ��Ʈ�� ���
	RootComponent = collisionComp;
	// 5. �ܰ� ������Ʈ ����ϱ�
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	// 6. �θ� ������Ʈ ����
	bodyMeshComp->SetupAttachment(collisionComp);
	// 7. �浹 ��Ȱ��ȭ
	bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 8. �ܰ� ũ�� ����
	bodyMeshComp->SetRelativeScale3D(FVector(0.25f));

	// �߻�ü ������Ʈ
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	// movement ������Ʈ�� ���Ž�ų ������Ʈ ����
	movementComp->SetUpdatedComponent(collisionComp);

	// �ʱ�ӵ�
	movementComp->InitialSpeed = 5000;
	// �ִ� �ӵ�
	movementComp->MaxSpeed = 5000;
	// �ݵ� ����
	movementComp->bShouldBounce = true;
	// �ݵ� ��
	movementComp->Bounciness = 0.3f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle deathTimer;
	//GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ABullet::Die, 2.0f, false);

	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void
		{
			Destroy();
		}), 2.0f, false); // ���� ��
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::Die()
{
	Destroy();
}

void ABullet::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{

	// speed ���� �����Ǿ����� üũ
	if (PropertyChangedEvent.GetPropertyName() == TEXT("speed"))
	{
		// ������Ÿ�� �����Ʈ ������Ʈ�� speed �� ����
		movementComp->InitialSpeed = speed;
		movementComp->MaxSpeed = speed;
	}
}
